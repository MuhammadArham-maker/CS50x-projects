from cs50 import get_int

while True:
    h = get_int("Height: ")
    if 1 <= h <= 8:
        break

for row in range(h):

    for space in range(h-(row+1)):
        print(" ", end='')

    for bricks in range(row+1):
        print("#", end='')

    print("  ", end='')

    for bricks in range(row+1):
        print("#", end='')
    print()
