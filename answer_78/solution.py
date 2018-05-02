def kth_pentagonal(k):
    return k*(3*k - 1) // 2

def generalized_pentagonal_numbers(n):
    for k in range(1, n):
        yield kth_pentagonal(k)
        yield kth_pentagonal(-k)

def until_size(gen, size):
    n = 0
    while n < size:
        n = next(gen)
        yield n

if __name__ == "__main__":
    pe_MOD = 10**6
    MOD = pe_MOD
    # MOD = 10**9+7
    N = 6*10**4 + 1
    pentagonals = list(until_size(generalized_pentagonal_numbers(N), N))
    p = [0] * N
    p[0] = 1
    for k in range(1, N):
        s = 1
        t = 0
        for f in pentagonals:
            if f > k:
                break
            if t == 2:
                s *= -1
                t = 0
            p[k] = (p[k] + s*p[k - f]) % MOD
            t += 1
    # project euler +
    # for _ in range(int(input())):
    #     n = int(input())
    #     print(p[n])

    # project euler
    for i in range(N):
        if p[i] == 0:
            print(i)
