import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        if not name or not month or not day:
            return "All fields are required!", 400

        try:
            month = int(month)
            day = int(day)
        except ValueError:
            return "Month and Day must be numbers!", 400

        if month < 1 or month > 12 or day < 1 or day > 31:
            return "Invalid date!", 400

        # TODO: Add the user's entry into the database
        db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)

        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        birthdays = db.execute("SELECT * FROM birthdays")

        return render_template("index.html", birthdays=birthdays)


@app.route("/delete", methods=["POST"])
def delete():
    # get id of the user
    bday_id = request.form.get("id")

    if bday_id:
        db.execute("DELETE FROM birthdays WHERE id=?", bday_id)

    return redirect("/")


@app.route("/edit/<int:birthday_id>", methods=["GET", "POST"])
def edit(birthday_id):
    # Get request shows the current value in the form
    if request.method == "GET":
        birthday = db.execute("SELECT * FROM birthdays WHERE id = ?", birthday_id)
        if not birthday:
            return "Birthday not found!", 404
        return render_template("edit.html", birthday=birthday[0])

    # Post request: update the database
    else:
        name = request.form.get("name")
        month = request.form.get("month")
        day = request.form.get("day")

        if not name or not month or not day:
            return "All fields are recquired!", 400

        try:
            month = int(month)
            day = int(day)
        except ValueError:
            return "Month and Day must be numbers!", 400

        if month < 1 or month > 12 or day < 1 or day > 31:
            return "Invalid date!", 400

        db.execute("UPDATE birthdays SET name = ?, month = ?, day = ? WHERE id = ?",
                   name, month, day, birthday_id)

        return redirect("/")
