def kth_pentagonal(k):
    return 3*k*(k - 1) // 2

def pentagonal_numbers(n):
    for k in range(1, n):
        yield kth_pentagonal(k)

def generalized_pentagonal_numbers(n):
    for k in range(1, n):
        yield kth_pentagonal(k)
        yield kth_pentagonal(-k)
