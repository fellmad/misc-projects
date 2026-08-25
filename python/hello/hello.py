import datetime
a = 1
b = "hello"
c = 0.0
try:
    print(b)
    print(a / c)
except ZeroDivisionError as ex:
    print("exception caught:", ex)
    print("divide by zero expected...")
currentDT = datetime.datetime.now()
print("date and time:", str(currentDT))