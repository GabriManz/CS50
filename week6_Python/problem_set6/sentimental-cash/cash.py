from cs50 import get_float

while True:
    try:
        change = get_float("Change: ")
        if change > 0:
            break
        else:
            print("Invalid input")
    except ValueError:
        print("Invalid input")

change = round(change * 100)

coins = 0

while change > 0:
    if change >= 25:
        change = change - 25
        coins = coins + 1
    elif change >= 10:
        change = change - 10
        coins = coins + 1
    elif change >= 5:
        change = change - 5
        coins = coins + 1
    elif change >= 1:
        change = change - 1
        coins = coins + 1

print(coins)
