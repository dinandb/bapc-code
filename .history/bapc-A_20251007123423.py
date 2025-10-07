

import math

def input_test():
    n = int(input())
    points = []
    for i in range(n):
        x,y = map(int, input().split())
        points.append((x,y))
    return points

def cross(o, a, b):
    """Cross product of OA and OB vectors (returns positive for counter-clockwise turn)."""
    return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0])

def convex_hull(points):
    """Computes the convex hull of sorted 2D points (left to right)."""
    if len(points) <= 1:
        return points

    # Build lower hull
    lower = []
    for p in points:
        while len(lower) >= 2 and cross(lower[-2], lower[-1], p) <= 0:
            lower.pop()
        lower.append(p)

    # Build upper hull
    upper = []
    for p in reversed(points):
        while len(upper) >= 2 and cross(upper[-2], upper[-1], p) <= 0:
            upper.pop()
        upper.append(p)

    # Concatenate lower and upper hulls (omit duplicate endpoints)
    return lower[:-1] + upper[:-1]


# print(convex_hull(input_test()))

def largest_abs_angle(convex_points):
    largest_angle = 0

    for i, point in enumerate(convex_points):
        if i > 0:
            x1, y1 = 
            x2, y2 = point[0], point[1]
            cur_angle = math.abs(math.arctan())
        
