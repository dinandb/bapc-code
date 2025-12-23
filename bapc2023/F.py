n, c = list(map(int, input().split()))

show_ups = list(map(int, input().split()))
from math import floor
DP = [(show_ups[0], int(floor(show_ups[0]/c)))]
for i in range(1,n):
    rest = max(DP[i-1][0]-c, 0)
    DP.append((rest+show_ups[i], int(floor((rest+show_ups[i])/c))))
# assert (len(DP)==n)
# print(DP)
smallest_wait = 2*n
best_moment_to_start = -1
for i in range(n):
    cur_wait = DP[i][1]
    if cur_wait < smallest_wait and cur_wait + i < n:
        # print("new best time =", cur_wait)
        smallest_wait = cur_wait
        best_moment_to_start = i

if best_moment_to_start == -1:
    print("impossible")
    
    exit(0)
print(best_moment_to_start)