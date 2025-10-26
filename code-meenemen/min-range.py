


def min_range(min, max, *args):
    assert min <= max
    func = args[0]
    minimal = func(min)
    arg = min
    for k in range(min, max+1):
        if func(k) < minimal:
            minimal = func(k)
            arg = k

    return minimal, arg
        
