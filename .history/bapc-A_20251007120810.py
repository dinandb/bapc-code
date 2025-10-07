

import math

def input_test():
    n = int(input())
    points = []
    for i in range(n):
        x,y = map(int, input().split())
        points.append((x,y))
    return points

def convex_hull(points):
    
    sorted_points = sorted(points, key=lambda p: (p[0], p[1]))
    convex_hull = []
    cur_angle = 360
    for i, point in enumerate(sorted_points):
        if i == 0:
            convex_hull.append(point)
        if i > 0:
            previous = sorted_points[i-1]
            x1, y1 = previous[0], previous[1]
            x2, y2 = point[0], point[1]
            angle = math.arctan((y2-y1))
            



