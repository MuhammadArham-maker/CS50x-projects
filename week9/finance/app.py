import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, get_cash

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session["user_id"]

    # Query for user's holdings
    rows = db.execute(
        "SELECT symbol, SUM(shares) AS total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0", user_id
    )

    holdings = []
    grand_total = 0

    # Build a list of holdings with current data
    for row in rows:
        stock = lookup(row["symbol"])
        if stock:
            shares = row["total_shares"]
            price = stock["price"]
            total = shares * price
            grand_total += total
            holdings.append({
                "symbol": stock["symbol"],
                "shares": shares,
                "price": price,
                "total": total
            })

    # Get user's current cash balance
    cash = get_cash(user_id)
    grand_total += cash

    return render_template("index.html", holdings=holdings, current_cash=cash, grandtotal=grand_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares_str = request.form.get("shares")

        # Validate input
        if not symbol:
            return apology("must provide symbol", 400)
        stock = lookup(symbol)
        if not stock:
            return apology("invalid symbol", 400)

        if not shares_str or not shares_str.isdigit() or int(shares_str) <= 0:
            return apology("shares must be a positive integer", 400)
        shares = int(shares_str)

        # Calculate cost and check affordability
        user_id = session["user_id"]
        cost = shares * stock["price"]
        cash = get_cash(user_id)

        if cash < cost:
            return apology("can't afford", 400)

        # Update database
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", cost, user_id)
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
            user_id, stock["symbol"], shares, stock["price"]
        )

        flash(f"Bought {shares} shares of {stock['symbol']} for {usd(cost)}!", "success")
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions = db.execute(
        "SELECT symbol, shares, price, transacted FROM transactions WHERE user_id = ? ORDER BY transacted DESC", user_id
    )
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""
    session.clear()
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 400)
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        session["user_id"] = rows[0]["id"]
        return redirect("/")
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""
    session.clear()
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("must provide symbol", 400)
        stock = lookup(symbol)
        if not stock:
            return apology("invalid symbol", 400)
        return render_template("quoted.html", stock=stock)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        if not username:
            return apology("must provide username", 400)
        if not password:
            return apology("must provide password", 400)
        if password != confirmation:
            return apology("passwords do not match", 400)

        try:
            hashed_password = generate_password_hash(password)
            new_user_id = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hashed_password)
            session["user_id"] = new_user_id
            return redirect("/")
        except ValueError:
            return apology("username already exists", 400)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares_to_sell_str = request.form.get("shares")

        if not symbol:
            return apology("must provide symbol", 400)

        if not shares_to_sell_str or not shares_to_sell_str.isdigit() or int(shares_to_sell_str) <= 0:
            return apology("shares must be a positive integer", 400)
        shares_to_sell = int(shares_to_sell_str)

        rows = db.execute(
            "SELECT SUM(shares) as total_shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol", user_id, symbol
        )
        if not rows or rows[0]["total_shares"] < shares_to_sell:
            return apology("not enough shares", 400)

        stock = lookup(symbol)
        if not stock:
            return apology("invalid symbol", 400)

        # Update database
        revenue = shares_to_sell * stock["price"]
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", revenue, user_id)
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
            user_id, stock["symbol"], -shares_to_sell, stock["price"]
        )

        flash(f"Sold {shares_to_sell} shares of {stock['symbol']} for {usd(revenue)}!", "success")
        return redirect("/")
    else:
        stocks = db.execute(
            "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING total_shares > 0", user_id
        )
        return render_template("sell.html", stocks=stocks)

