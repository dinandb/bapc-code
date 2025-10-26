

def input_test():
    n,k = map(int, input().split())
    days = [0]
    individual_fares = [0]
    for i in range(n):
        day, individual_fare = map(int, input().split())
        days.append(day)
        individual_fares.append(individual_fare)
    pass_prices = []
    pass_days = []
    for j in range(k):
        
        pass_valid, pass_travel_days, pass_price = map(int, input().split())
        pass_prices.append(pass_price)
        pass_days.append([pass_valid, pass_travel_days])

    return n, k, days, individual_fares, pass_prices, pass_days
import time
def create_tk_array(index, days, pass_days):
    terugkijk_array = []
    # for pass_day in pass_days:
    #     terugkijk = index
    #     while abs(days[index-terugkijk] - days[index]) + 1 > pass_day[0]:
    #         terugkijk -= 1
    #     terugkijk_array.append(min(terugkijk+1, pass_day[1]))
    

    for pass_day in pass_days:
        terugkijk = min(index, pass_day[1])
        low = 1
        high = terugkijk
        # find max terugkijk st
        # days[index-terugkijk] - days[index] + 1 <= pass_day[0]
        while not (days[index]-days[index-terugkijk]+1 <= pass_day[0] and (days[index-terugkijk-1] - days[index]+1 > pass_day[0] or index-terugkijk == 0)):
            terugkijk = (low + high)//2
            print(f" nieuw terugkijk {terugkijk}")
            time.sleep(0.5)
            
            if not days[index-terugkijk] - days[index]+1 <= pass_day[0]:
                # we kijken te ver terug, terugkijk moet lager
                high = terugkijk
                print(f" updated high to {high}")
            else:
                # we kijken te dichtbij, terugkijk moet hoger
                low = terugkijk
                print(f" updated low to {low}")
            if terugkijk == 1:
                break
        print(f'added terugkijk {terugkijk}')
        terugkijk_array.append(terugkijk)

    print(f"terugkijk_array voor index = {index}: {terugkijk_array}")

    return terugkijk_array

def dp(n, k, days, individual_fares, pass_prices, pass_days):
    dp = [0]
    for i in range(1, n+1):
        terugkijk_array = create_tk_array(i, days, pass_days)
        min_added_cost = dp[i-1] + individual_fares[i]
        for j in range(k):
            min_added_cost = min(min_added_cost, dp[i-terugkijk_array[j]] + pass_prices[j])
        dp.append(min_added_cost)
    # print(f"dp = {dp}")
    print(dp[-1])

def main():
    n, k, days, individual_fares, pass_prices, pass_days = input_test()
    dp(n, k, days, individual_fares, pass_prices, pass_days)
main()