def askHeight():
    height = 0

    while True:
        try:
            height = int(input("Height: "))
            if 1 <= height <= 8:
                break
            else:
                print("Invalid height. Please enter a number between 1 and 8.")
        except ValueError:
            print("Invalid input. Please enter a valid number.")

    return height


def printOuterWhitespace(n):
    for i in range(n):
        print(" ", end="")


def printBlockAndInnerWhitespace(n):
    print("#" * n, end="")
    print("  ", end="")
    print("#" * n)


height = askHeight()

for i in range(height):
    printOuterWhitespace(height - i - 1)
    printBlockAndInnerWhitespace(i + 1)
