from math import ceil


def is_prime(num: int) -> bool:
    """Returns whether num is prime"""
    return all(num % i != 0 for i in range(2, num))


def next_prime(num: int) -> int:
    """Returns the prime just larger than num"""
    while not is_prime(num):
        num += 1

    return num


if __name__ == "__main__":
    expected_number_of_items = int(input("Expected number of items: "))
    minimum_table_size = ceil(1.3 * expected_number_of_items)
    print(f"Table size: {next_prime(minimum_table_size)}")
