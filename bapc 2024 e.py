n = int(input())

print("? 1")

lower_value = int(input())

print(f"? {n}")

upper_value = int(input())

lower_index=1
upper_index=n
look_for_value = (lower_value + upper_value) / 2
for i in range(48):
    mid_indx = (lower_index + upper_index) // 2
    print(f"? {mid_indx}")
    middle_value = int(input())

    if middle_value > look_for_value:
        upper_index = mid_indx
    else:
        lower_index = mid_indx

print(f"! 1 mid_indx {n}")
