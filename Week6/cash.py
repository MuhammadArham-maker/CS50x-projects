from cs50 import get_float

# get change from user
while True:
    change = get_float("Change: ")
    if change > 0:
        break

# Converting dollar to cents
change = round(change * 100)

# List to store coin values
coins = [25, 10, 5, 1]
# variable to store coin count
count = 0

for coin in coins:
    count += change // coin
    change %= coin

print(count)
