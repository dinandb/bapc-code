def input_instance():
    n,m,r = map(int, input().split())
    scores = []
    total_ps = 0
    for i in range(n):
        score = input()
        amount_ps = score.count("p")
        total_ps += amount_ps
        scores.append(score)
    scores.reverse()
    exclamations = []
    for j in range(total_ps):
        exclamation = input()
        if exclamations[-1] == "!":
            exclamations.append(exclamation.count('y')-3)
        else:
            exclamations.append(-1)
    return n,m,r, 

