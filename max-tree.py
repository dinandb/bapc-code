


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

def find_number_in_all_perms(number, perms):
    for i, subperm in enumerate(perms):
        if number in subperm:
            return i
    return None

def get_perm(test_case):
    n = test_case['n']
    edges = test_case['edges']

    all_perms = []



    for edge in edges:
        u,v,x,y = edge[0], edge[1],edge[2],edge[3]
        if x > y: # want to add p[u] > p[v]
            i = find_number_in_all_perms(u, all_perms)
            j = find_number_in_all_perms(v, all_perms)
            # i, j mergen en die van i moet na j
            if i and j:
                merged = all_perms[j] + all_perms[i] # change order if y >= x
                all_perms = [merged] + [sub for k, sub in enumerate(all_perms) if k not in (i, j)]

            elif i: # add v before u
                all_perms[i].insert(v,0)
            elif j: # add u after v
                all_perms[j].append(u)

            else: #add new perm: v, u
                all_perms.append([v,u])

        else:
            i = find_number_in_all_perms(u, all_perms)
            j = find_number_in_all_perms(v, all_perms)
            # i, j mergen en die van i moet na j
            if i and j:
                merged = all_perms[i] + all_perms[j] # change order if y >= x
                all_perms = [merged] + [sub for k, sub in enumerate(all_perms) if k not in (i, j)]

            elif i: # add v after u
                all_perms[i].append(v)
            elif j: # add u before v
                all_perms[j].insert(u, 0)
                
            else: #add new perm: v, u
                all_perms.append([v,u])
        print(all_perms)
    return all_perms[0]
                
            
        

def main():
    test_cases = input_test()

    for test_case in test_cases:
        print(get_perm(test_case))
        
main()
