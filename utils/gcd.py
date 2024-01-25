def gcd(n: int, m: int) -> int:
    if m == 0:
        return n
    if m > n:
        return gcd(m, n)
    return gcd(m, n % m)

if __name__ == "__main__":
    n, m = map(int, input().strip().split())
    print(gcd(n, m))
