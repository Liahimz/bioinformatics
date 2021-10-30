#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <utility>
#include <algorithm> 
#include <random>
#include <chrono>
#include <deque>

void print_vecor(std::vector<uint64_t>& m) {
    for (uint64_t i = 0; i < m.size(); ++i)
       std::cout << m[i] << std::endl;
}


int main() {
    int64_t k;
    std::cin >> k;
    std::vector<int64_t> mas = {57, 71, 87, 97, 99, 101, 103, 113, 114, 115, 128, 129, 131, 137, 147, 156, 163, 186};
    std::vector<int64_t> comb;
    
    for (int64_t j = 0; j < k + 1; ++j) {
       comb.push_back(0);
    }

    comb[0] = 1;

    for (int64_t i = 0; i < k + 1; ++i) {
        int64_t sum = 0;
        for (int64_t j = 0; j < mas.size(); ++j) {
            if ((i - mas[j]) >= 0)
                sum += comb[i - mas[j]];
        }
        comb[i] += sum;
    }

    
    std::cout << comb[k] << std::endl;
    return 0;
}