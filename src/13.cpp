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

int main() {
    std::vector<std::pair<std::string, std::string>> k_mers;
    int k, d;
    std::cin >> k;
    std::cin >> d;
    std::string delimiter = "|";
    std::string pattern;

    while (getline(std::cin, pattern)) {
        if (!pattern.empty()) {
            k_mers.push_back(std::make_pair(pattern.substr(0, pattern.find(delimiter)), pattern.substr(pattern.find(delimiter) + 1, pattern.size())));
        }
    }

    // for (int i = 0; i < k_mers.size(); ++i) {
    //     std::cout << k_mers[i].first << " " << k_mers[i].second << std::endl;
    // }

    // std::cout << "------------" << std::endl;

    while (k_mers.size() > 1) {
        for (int i = 0; i < k_mers.size(); ++i) {
            std::string suffiks_0 = k_mers[i].first.substr(k_mers[i].first.size() - k + 1, k_mers[i].first.size());
            std::string suffiks_1 = k_mers[i].second.substr(k_mers[i].second.size() - k + 1, k_mers[i].second.size());
            for (int j = 0; j < k_mers.size(); ++j) {
                std::string prefix_0 = k_mers[j].first.substr(0,k - 1);
                std::string prefix_1 = k_mers[j].second.substr(0,k - 1);
                if (suffiks_0.compare(prefix_0) == 0 && suffiks_1.compare(prefix_1) == 0) {
                    k_mers[i].first += k_mers[j].first.substr(k - 1, k_mers[j].first.size());
                    k_mers[i].second += k_mers[j].second.substr(k - 1, k_mers[j].second.size());
                    k_mers.erase(k_mers.begin() + j);
                    break;
                }
            }
        }
    }
    // std::cout << "------------" << std::endl;
    // for (int i = 0; i < k_mers.size(); ++i) {
    //     std::cout << k_mers[i].first << " " << k_mers[i].second << std::endl;
    // }

    std::cout << k_mers[0].first + k_mers[0].second.substr(k_mers[0].second.size() - k - d, k_mers[0].second.size()) << std::endl;
}