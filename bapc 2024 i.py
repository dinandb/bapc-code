n, k = map(int, input().split())
traveldays = []
travelfares = []
passes = [] #valid of days, number of travel days
passcost = []
for _ in range(n):
    t, f = map(int, input().split())
    traveldays.append(t)
    travelfares.append(f)
for _ in range(k):
    p, d, c = map(int, input().split())
    passes.append((p,d))
    passcost.append(c)

def is_day_feasible(passvalid, day_to_check, current_day):
    if current_day - day_to_check >= passvalid:
        return True
    else:
        return False

def find_previous_feasible_pass_day(passdays, passvalid, dp, currentIndex):
    for (p_valid_days, d_travel_days) in passes:
        if is_day_feasible(p_valid_days, ):

dp = [0] * n
dp[0] = min(travelfares[0], min(passcost))
for travel_index in range(1, n):
