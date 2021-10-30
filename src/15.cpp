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

class paired_kmer {
    private:
        std::pair<std::string, std::string> paired;
    public:
};

int main() {
    std::vector<std::pair<std::string, std::string>> k_mers;
    int k, d;
    std::cin >> k;
    std::cin >> d;
    std::string delimiter = "|";
    std::string pattern;

    while (getline(std::cin, pattern)) {
        if (!pattern.empty()) 
            k_mers.push_back(std::make_pair(pattern.substr(0, pattern.find(delimiter)), pattern.substr(pattern.find(delimiter) + 1, pattern.size())));
    }

    char ans[k_mers.size() + k + d + k]{};
    for (int i = 0; i < k_mers.size(); ++i) { 
        k_mers[i].first.copy(ans + i, k, 0);
        k_mers[i].second.copy(ans + i + k + d, k, 0);
    }

    for (int i = 0; i < k_mers.size() + k + d + k; ++i)
        std::cout << ans[i];
    std::cout << std::endl;
}