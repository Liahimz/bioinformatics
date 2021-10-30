#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <utility>
#include <algorithm> 
#include <random>
#include <chrono>


int HammingDist(const std::string &str1, const std::string &str2)
{
    int count = 0;
    for (int i = 0; i < str1.length(); ++i) {
        if (str1[i] != str2[i])
            count ++;
    }
    return count;
}

int DistanceBetweenPatternAndStrings(std::string patern, std::vector<std::string> dna) {
    int k = patern.size();
    int dist = 0;
    for (int j = 0; j < dna.size(); ++j) {
        int ham_dist = INT32_MAX;
        for(int i = 0; i < dna[j].length() + 1 - k; ++i) {
            std::string kmer = dna[j].substr(i, k);
            int new_dist = HammingDist(patern, kmer);
            if (new_dist < ham_dist)
                ham_dist = new_dist;
        }
        dist += ham_dist;
    }
    return dist;
}

int main() {
    std::string pattern;
    std::cin >> pattern;
    std::string str;

    std::vector<std::string> dna;
    while (getline(std::cin, str, ' ')) {
        if (!str.empty())
            dna.push_back(str);
    }

    std::cout << DistanceBetweenPatternAndStrings(pattern, dna) << std::endl;
}