def fizzbuzz(n):
    if n % 5 == 0 and n % 7 == 0:
        print("FizzBuzz")
    elif n % 5 == 0:
        print("Fizz")
    elif n % 7 == 0:
        print("Buzz")

    else:
        print(n)

def main():
    for i in range(1, 100):
        fizzbuzz(i)

main()