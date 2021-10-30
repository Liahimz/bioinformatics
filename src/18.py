import numpy as np
import sys

def expand(peptides_pattern, mas):
    new_patterns = []
    for i in mas:
        for j in peptides_pattern:
            new_patterns.append((j[0]+'-'+str(i), j[1]+i))

    peptides_pattern = new_patterns
    return new_patterns


def main():
    mas = [57, 71, 87, 97, 99, 101, 103, 113, 114, 115, 128, 129, 131, 137, 147, 156, 163, 186]
    spectrum = []
    for line in sys.stdin:
        spectrum = [int(x) for x in line.split(' ')]


    print(spectrum)
    peptides_pattern = []


    new_mas = []
    for i in spectrum:
        if i in mas:
            peptides_pattern.append((str(i), int(i)))
            new_mas.append(int(i))


    max_sum = int(spectrum[len(spectrum) - 1])
    print(max_sum)
    print(new_mas)
    ans = []
    i = 0
    while peptides_pattern and i < 2:
        pattern = expand(peptides_pattern, new_mas)
        print(pattern)
        

        for peptide in pattern:
            print(peptide[0], peptide[1])
            if peptide[1] == max_sum:
                ans.append(peptide[0])
                print("removed ", peptide)
                pattern.remove(peptide)

            elif peptide[1] not in spectrum:
                print("removed ", peptide)
                pattern.remove(peptide)

        peptides_pattern = pattern
            
        print(peptides_pattern)
        i += 1


    #print(peptides_pattern)
    #print(ans)

if __name__ == "__main__":
    main()