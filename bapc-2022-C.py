


def input_test():
    c, t, r = map(int, input().split())
    p = float(input())

    return c,t,r,p

# def T_func(x, r, p):
#     return ((r+1)/p)*((1-p)**(-x) -1)

def init_T(c, r, p):
    T = [0]
    for x in range(1, c+1):
        T.append( (T[-1]+1+p*r)/(1-p) )
    return T




def min_range(min, max, *args):
    assert min <= max
    func = args[0]
    minimal = func(min)
    arg = min
    for k in range(min, max+1):
        # print(k)
        if func(k) < minimal:
            minimal = func(k)
            arg = k

    return minimal, arg
        



def dp(T, c, t, r, p):
    dp = [0] # cost om 0 chars te typen is 0
    for x in range(1, c+1): # als i = 0, dan eerste elemnt dus hebben we x = 1
        a = T[x]
        func  = lambda k: dp[k] + t + T[x-k]
        b = min_range(0, x-1, func)
        dp.append(min(a,b[0]))

    # print(dp)
    return dp[-1]+t



def main():
    c,t,r,p = input_test()
    T = init_T(c, r,p)
    # print(T)
    print(dp(T,c,t,r,p))

main()