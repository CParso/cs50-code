# TODO
while True:
    try:
        height = int(input("Height: "))
        if height > 0 and height < 9:
            break
        else:
            continue
    except:
        NameError

space = " "
hash = "#"
for i in range(height):
    print(space * (height - (i + 1)), end="")
    print(hash * (i + 1), end="")
    print(space * 2, end="")
    print(hash * (i + 1), end="")
    print()