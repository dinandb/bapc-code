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
    
    return n,m,r, scores, exclamations

def find_first_p(scores):
    for i, score in enumerate(scores):
        index = score.find('p')
        if index > -1:
            return i, index
    return None, None

def update_scoreboard(i,j, scores):
    scores[i][j] = "&"

def main():
    n,m,r,scores,exclamations = input_instance()
    
    for increase in exclamations:
        i,j = find_first_p(scores)
        if i is None:
            return "AHAHAHAHAHH"
        update_scoreboard(i, j, scores)


