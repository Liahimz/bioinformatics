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
    std::vector<std::string> k_mers;
    std::string pattern;

    while (getline(std::cin, pattern)) {
        if (!pattern.empty()) {
            k_mers.push_back(pattern);
        }
    }

    int k = k_mers[0].size();
    std::vector<std::string> non_branch;
    std::vector<std::string> ans;

    for (int i = 0; i < k_mers.size(); ++i) {
        int in = 0;
        int out = 0;
        for (int j = 0; j < k_mers.size();  ++j) {
            if (k_mers[i].substr(0, k - 1).compare(k_mers[j].substr(0, k - 1)) == 0)
                in++;
            if (k_mers[i].substr(0, k - 1).compare(k_mers[j].substr(1, k)) == 0)
                out++;
        }
        // std::cout << in << " " << out << std::endl;
        if (in == 1 && out == 1)
            non_branch.push_back(k_mers[i]);
        else 
            ans.push_back(k_mers[i]);
    }

    // for (int i = 0; i < non_branch.size(); ++i) {
    //     std::cout << non_branch[i]  << std::endl;
    // }
    // std::cout << "------------" << std::endl;
    while (non_branch.size() > 0) {
        for (int i = 0; i < non_branch.size(); ++i) {
            for (int j = 0; j < ans.size(); ++j) {
                if (ans[j].find(non_branch[i].substr(0, k - 1)) != std::string::npos) {
                    ans[j] += non_branch[i].substr(k - 1, non_branch[i].size());
                    non_branch.erase(non_branch.begin() + i);
                    break;
                }
            }
        }
    }
    
    std::sort(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); ++i) {
        std::cout << ans[i]  << std::endl;
    }
    
    
}