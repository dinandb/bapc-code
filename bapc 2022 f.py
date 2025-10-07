X, Y = input().split()

angles = {"N" : 0, "E" : 90, "S" : 180, "W" : 270}

def circular_mean(a, b):
    if abs(a-b) >= 180:
       # return (360 - a - b) / 2
        return (360 + abs(a-b)) / 2
    else:
        return (a + b) / 2

def get_angle(s):
    angle = angles[s[-1]]
    for i in range(len(s) - 2, -1, -1):
        angle = circular_mean(angle, angles[s[i]])
    return angle

ang_X = get_angle(X)
ang_Y = get_angle(Y)
print(min((ang_X - ang_Y) % 360, (ang_Y - ang_X) % 360))