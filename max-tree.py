


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

    perms_dict = {}

    for edge in edges:
        u,v,x,y = edge[0], edge[1],edge[2],edge[3]
        if x > y: # want to add p[u] > p[v]
            # i = find_number_in_all_perms(u, all_perms)
            i = perms_dict[u] if u in perms_dict else None

            # j = find_number_in_all_perms(v, all_perms)
            j = perms_dict[v] if v in perms_dict else None
            # i, j mergen en die van i moet na j
            # print(f"v, u, j {v, u, i, j}")
            if i is not None and j is not None:
                merged = all_perms[j] + all_perms[i] # change order if y >= x
                all_perms = [merged] + [sub for k, sub in enumerate(all_perms) if k not in (i, j)]
                for i, elt in enumerate(all_perms):
                    for number in elt:
                        perms_dict[number] = i

            elif i is not None : # add v before u
                all_perms[i].insert(0,v)
                perms_dict[v] = perms_dict[u]
            elif j is not None : # add u after v
                all_perms[j].append(u)
                perms_dict[u] = perms_dict[v]
            else: #add new perm: v, u
                all_perms.append([v,u])
                perms_dict[u] = len(all_perms)-1
                perms_dict[v] = len(all_perms)-1          

        else:
            # i = find_number_in_all_perms(u, all_perms)
            i = perms_dict[u] if u in perms_dict else None

            # j = find_number_in_all_perms(v, all_perms)
            j = perms_dict[v] if v in perms_dict else None
            # print(f"u, v, i, j {u, v, i, j}")
            # i, j mergen en die van i moet na j
            if i is not None and j is not None:
                merged = all_perms[i] + all_perms[j]
                all_perms = [merged] + [sub for k, sub in enumerate(all_perms) if k not in (i, j)]
                for i, elt in enumerate(all_perms):
                    for number in elt:
                        perms_dict[number] = i
                    

                    
                        


            elif i is not None: # add v after u
                all_perms[i].append(v)
                perms_dict[v] = perms_dict[u]
            elif j is not None : # add u before v
                all_perms[j].insert(0,u)
                perms_dict[u] = perms_dict[v]
                
            else: #add new perm: v, u
                all_perms.append([u,v])
                perms_dict[u] = len(all_perms)-1
                perms_dict[v] = len(all_perms)-1
        # print(all_perms)
    return all_perms[0]

def up(lijst):
    return [x + 1 for x in lijst]
            
def pprint(lijst):
    res = ""
    for elt in lijst:
        res += str(elt)
        res += " "
    print (res)

def last_update(lijst):
    permutatie = [0] * len(lijst)
    for i, elt in enumerate(lijst):
        permutatie[elt-1] = i+1
    return permutatie
    

def main():
    test_cases = input_test()

    for test_case in test_cases:
        (pprint((last_update(get_perm(test_case))))) #  +1 erbij
        
main()
