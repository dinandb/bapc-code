#stink windmolens
n, w = map(int, input().split())

WM = []
for i in range(n):
    p,t = map(int, input().split())
    WM.append({'rate': p, 'time': t})

WM.sort(key=lambda x: x['time'])

DP=[(w/WM[0]['rate'] + 2*WM[0]['time'], WM[0]['rate'] )]

for i in range(1, n):
    werktijd = DP[i-1][0] - 2*WM[i]['time']
    if werktijd < 0:
        break
    total_rate = WM[i]['rate'] + DP[i-1][1]
    T_bespaar = (werktijd*WM[i]['rate'])/total_rate
    DP.append((DP[i-1][0]-T_bespaar, total_rate))
print(DP[-1][0])