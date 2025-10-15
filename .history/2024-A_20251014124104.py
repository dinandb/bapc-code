def input_instance():
    n,m,r = map(int, input().split())
    scores = []
    for i in range(n):
        scores.append(input())
    scores.reverse()
    