

n = int(input())
print(f"? 1")
laag = int(input())
print(f"? {n}")
hoog = int(input())

low_i, high_i = 1, n
target = (laag + hoog) / 2.0

while high_i - low_i > 1:
    mid = (low_i + high_i) // 2
    print("? ",end="")
    print(mid, flush=True)
    val = int(input())
    if val <= target:
        low_i = mid
        laag = val
    else:
        high_i = mid
        hoog = val

if abs(laag - target) <= abs(hoog - target):
    # print(f"index of value closest to mean = {low_i}")
    print(f"! {1} {low_i} {n}")
else:
    # print(f"index of value closest to mean = {high_i}")
    print(f"! {1} {high_i} {n}")


