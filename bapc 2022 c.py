c, t, r = map(int, input().split())
p       = float(input())

T = [0] * c
for x in range(c):
    T[x] = (T[x - 1] + 1 + p * r) / (1 - p)
# T = [((r + 1) / p) * ((1 - p) ** (-x) - 1) for x in range(1, c + 1)]

DP = [0] * (c + 1)
for x in range(1, c + 1):
    minimal_sub_expression = DP[0] + t + T[x - 1]
    for k in range(1,x + 1):
        minimal_sub_expression = min(minimal_sub_expression, DP[k] + t + T[x - k - 1])
    DP[x] = min(T[x-1], minimal_sub_expression)

print(DP[-1] + t)