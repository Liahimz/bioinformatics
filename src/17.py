def main():
    n = int(input())
    mas = [57, 71, 87, 97, 99, 101, 103, 113, 114, 115, 128, 129, 131, 137, 147, 156, 163, 186]
    comb = [0] * (n + 1)
    comb[0] = 1

    for i in range(n + 1):
        _sum = 0
        for j in mas:
            if i - j >= 0:
                _sum += comb[i - j]
        comb[i] += _sum

    print(comb[n]) 


if __name__ == "__main__":
    main()