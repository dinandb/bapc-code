def input_instance():
    n,m,r = map(int, input().split())
    scores = []
    total_ps = 0
    for i in range(n):
        score = input()
        amount_ps = score.count("P")
        total_ps += amount_ps
        scores.append(list(score))
    print(f"total ps = {total_ps}")
    scores[r-1] += "q"
    scores.reverse()
    
    exclamations = []
    for j in range(total_ps):
        exclamation = input()
        if exclamation[-1] == "!":
            exclamations.append(exclamation.count('y')-3)
        else:
            exclamations.append(0)
    
    return n,m,r, scores, exclamations
def find(list, elt):
    
def find_first_p(scores, tofind):
    for i, score in enumerate(scores):
        index = score.find(tofind)
        if index > -1:
            return i, index
    return None, None

def update_scoreboard(increase, i,j, scores):
    print(scores[i][j])
    scores[i][j] = "."
    to_move = scores[i]
    del scores[i]
    scores.insert(increase+i, to_move)
    

def main():
    n,m,r,scores,exclamations = input_instance()
    
    for increase in exclamations:
        i,j = find_first_p(scores, 'P')
        if i is None:
            print( "AHAHAHAHAHH")
            return
        update_scoreboard(increase, i, j, scores)

    onze_final_rank = find_first_p(scores, 'q')
    print(onze_final_rank)

    
main()

