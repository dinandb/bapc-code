n               = int(input())
original_prices = list(map(float, input().split()))

total  = 0
Threes = []
Fours  = []

prices = [int(round(p * 100)) % 5 for p in original_prices]
for index, price in enumerate(prices):
    if price == 0 or price == 5:
        total += original_prices[index]

    elif price == 1 or price == 2:
        total += original_prices[index] - (price / 100)

    elif price == 3:
        Threes.append(original_prices[index])

    else:
        Fours.append(original_prices[index])

while Threes != [] and Fours != []:
    item1 = Threes.pop()
    item2 = Fours.pop()

    total += item1 + item2 - 0.02

while len(Threes) >= 2:
    item1 = Threes.pop()
    item2 = Threes.pop()

    total += item1 + item2 - 0.01

while len(Fours) >= 3:
    item1 = Fours.pop()
    item2 = Fours.pop()
    item3 = Fours.pop()

    total += item1 + item2 + item3 - 0.02

for item in Threes:
    total += item

for item in Fours:
    total += item

print(f"{total:.2f}")