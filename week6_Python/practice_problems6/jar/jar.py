class Jar:
    def __init__(self, capacity=12):
        if not isinstance(capacity, int) or capacity < 0:
            raise ValueError("Capacity must be a non-negative integer")
        else:
            self.__size = 0
            self.__capacity = capacity

    def __str__(self):
        return ("🍪" * self.__size)

    def deposit(self, n):
        if not isinstance(n, int) or n < 0:
            raise ValueError("Deposit amount must be a non-negative integer")
        if self.__size + n > self.__capacity:
            raise ValueError("Deposit exceeds jar capacity")
        self.__size += n

    def withdraw(self, n):
        if not isinstance(n, int) or n < 0:
            raise ValueError("Withdrawal amount must be a non-negative integer")
        if n > self.__size:
            raise ValueError("Withdrawal exceeds the number of cookies in the jar")
        self.__size -= n

    @property
    def capacity(self):
        return self.__capacity

    @property
    def size(self):
        return self.__size


def main():
    jar = Jar()

    print(f"Jar Capacity: {jar.capacity}")
    print(f"Jar Contents: {str(jar)}")

    jar.deposit(2)
    print(f"Jar Contents after depositing 2 cookies: {str(jar)}")

    jar.withdraw(1)
    print(f"Jar Contents after withdrawing 1 cookie: {str(jar)}")

    try:
        jar.deposit(15)  # This should raise a ValueError
    except ValueError as e:
        print(f"Error: {e}")

    try:
        jar.withdraw(3)  # This should raise a ValueError
    except ValueError as e:
        print(f"Error: {e}")

if __name__ == "__main__":
    main()
