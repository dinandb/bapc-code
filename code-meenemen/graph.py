# n = number of vertices
n = 5
adj = [[] for _ in range(n)]  # each entry: list of (neighbor, weight)

def add_edge_weighted(u, v, w):
    adj[u].append((v, w))       # directed edge with weight w

def add_edge(u,v):
    add_edge_weighted(u,v,1)

def add_bi_edge_weighted(u, v, w):
    adj[u].append((v, w))
    adj[v].append((u, w))       # undirected edge

def add_bi_edge(u, v):
    add_bi_edge_weighted(u, v, 1)

def has_edge(u, v):
    return any(nei == v for nei, w in adj[u])  # O(deg(u))

def get_weight(u, v):
    for nei, w in adj[u]:
        if nei == v:
            return w
    return None   # or raise error if no edge
import heapq

def dijkstra(adj, start):
    """
    adj: adjacency list where adj[u] = [(v, w), ...]
    start: starting vertex index
    Returns: list of shortest distances from start to each vertex
             (float('inf') if not reachable)
    """
    n = len(adj)
    dist = [float('inf')] * n
    dist[start] = 0
    visited = [False] * n

    heap = [(0, start)]  # (distance, vertex)

    while heap:
        d, u = heapq.heappop(heap)
        if visited[u]:
            continue
        visited[u] = True

        for v, w in adj[u]:
            if not visited[v] and dist[u] + w < dist[v]:
                dist[v] = dist[u] + w
                heapq.heappush(heap, (dist[v], v))

    return dist




def test():
    add_bi_edge(0,1)
    print(has_edge(1,0))



adj = [
    [(1, 4), (2, 3)],           # 0
    [(2, 1), (3, 2)],            # 1
    [(3, 4), (4, 6)],            # 2
    [(4, 1), (5, 3)],            # 3
    [(5, 2), (6, 1)],            # 4
    [(6, 5), (7, 2)],            # 5
    [(7, 1)],                     # 6
    []                            # 7
]

start = 0
distances = dijkstra(adj, start)
# print("Shortest distances from vertex 0:", distances)




def prim_mst(adj, start=0):
    """
    adj: adjacency list where adj[u] = [(v, weight), ...]
    start: starting vertex index
    Returns: list of edges in the MST [(u, v, weight), ...] and total weight
    """
    n = len(adj)
    visited = [False] * n
    mst_edges = []
    total_weight = 0

    heap = [(0, start, -1)]  # (weight, current_vertex, parent_vertex)

    while heap:
        w, u, parent = heapq.heappop(heap)
        if visited[u]:
            continue
        visited[u] = True
        if parent != -1:
            mst_edges.append((parent, u, w))
            total_weight += w

        for v, weight in adj[u]:
            if not visited[v]:
                heapq.heappush(heap, (weight, v, u))

    # check if all vertices are connected
    if not all(visited):
        raise ValueError("Graph is not connected, MST does not exist")

    return mst_edges, total_weight


adj = [
    [(1, 2), (3, 6)],       # 0
    [(0, 2), (2, 3), (3, 8), (4, 5)],  # 1
    [(1, 3), (4, 7)],       # 2
    [(0, 6), (1, 8), (4, 9)],  # 3
    [(1, 5), (2, 7), (3, 9)]  # 4
]

mst_edges, total_weight = prim_mst(adj)
print("MST edges:", mst_edges)
print("Total weight:", total_weight)
