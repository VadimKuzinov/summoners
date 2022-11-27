w, h = map(int, input().split())


res = []
for y in range(h):
    s = input()
    for x in range(w):
        if s[x] == '#':
            res.append((x, h - y - 1, "nonmoving", "obstacle"))
        elif s[x] == 's':
            res.append((x, h - y - 1, "summonable", "summoner"))

print(w, h)
print(len(res))
for el in res:
    print(*el)
