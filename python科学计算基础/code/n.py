def printans(a, b):
    for i in range(a, b + 1, 2):
        print(i, end = ' ')
n = int(input("输入皇后个数："))
x = n % 6
if x != 2 and x != 3:
    if n % 2 == 1:
        printans(2, n - 1)
        printans(1, n)
    else:
        printans(2, n)
        printans(1, n - 1)
else:
    half = int(n / 2)
    if n % 2 == 1:
        if half % 2 == 1:
            printans(half, n - 2)
            printans(1, half - 2)
            printans(half + 3, n - 1)
            printans(2, half + 1)
            printans(n, n)
        else:
            printans(half, n - 1)
            printans(2, half - 2)
            printans(half + 3, n - 2)
            printans(1, half + 1)
            printans(n, n)
    else:
        if half % 2 == 1:
            printans(half, n - 1)
            printans(1, half - 2)
            printans(half + 3, n)
            printans(2, half + 1)
        else:
            printans(half, n)
            printans(2, half - 2)
            printans(half + 3, n - 1)
            printans(1, half + 1)