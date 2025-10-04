

def input_test():
    amount_test = int(input())
    test_cases = []
    for test in range(amount_test):
        n = int(input())
        edges = []
        for i in range(n-1):
            u,v,x,y = map(int, input().split())
            edges.append([u,v,x,y])
        test_case = {"n": n, "edges": edges}
        test_cases.append(test_case)

    return test_cases

def result(test_case):
    pass

def main():
    test_cases = input_test()

    for test_case in test_cases:
        print(result(test_case))
        