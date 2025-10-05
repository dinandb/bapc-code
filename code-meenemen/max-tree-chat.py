from collections import defaultdict, deque

# kahns algorithm for topological sort

def input_test():
    amount_test = int(input())
    test_cases = []
    for _ in range(amount_test):
        n = int(input())
        edges = []
        for _ in range(n-1):
            u, v, x, y = map(int, input().split())
            edges.append((u, v, x, y))
        test_cases.append({"n": n, "edges": edges})
    return test_cases

def get_perm(test_case):
    n = test_case['n']
    edges = test_case['edges']

    graph = defaultdict(list)
    indegree = [0] * (n + 1)

    # Build directed graph
    for u, v, x, y in edges:
        if x > y:
            # u after v
            graph[v].append(u)
            indegree[u] += 1
        else:
            # u before v
            graph[u].append(v)
            indegree[v] += 1

    # Kahn's algorithm for topological sort
    q = deque([i for i in range(1, n+1) if indegree[i] == 0])
    order = []
    while q:
        node = q.popleft()
        order.append(node)
        for nei in graph[node]:
            indegree[nei] -= 1
            if indegree[nei] == 0:
                q.append(nei)

    return order

def last_update(lijst):
    permutatie = [0] * len(lijst)
    for i, elt in enumerate(lijst):
        permutatie[elt-1] = i+1
    return permutatie

def pprint(lijst):
    print(" ".join(map(str, lijst)))

def main():
    test_cases = input_test()
    for test_case in test_cases:
        pprint(last_update(get_perm(test_case)))

main()
