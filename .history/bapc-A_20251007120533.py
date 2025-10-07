

def input_test():
    n = int(input())
    points = []
    for i in range(n):
        x,y = map(int, input().split())
        points.append((x,y))
    return points

def convex_hull(points):
    
    sorted_points = sorted(points, key=lambda p: (p[0], p[1]))
    cur_angle = 360
    for i, point in enumerate(sorted_points):
        if i > 0:
            previous = sorted_points[i-1]
            



