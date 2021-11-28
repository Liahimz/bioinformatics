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
#include <iterator>
#include <sstream>

void print_vector(std::vector<int32_t>& m) {
    for (int32_t i = 0; i < m.size(); ++i)
       std::cout << m[i] << " ";
    std::cout << std::endl;
}

void print_vector(std::vector<std::pair<int, int>>& m) {
    for (int32_t i = 0; i < m.size(); ++i)
       std::cout << m[i].first << " " << m[i].second << std::endl; 
}

template <class T>
void print_vector(T& m) {
    for (int32_t i = 0; i < m.size(); ++i)
       std::cout << m[i] << std::endl; 
}

int DPChange(int money, std::vector<int> &coins) {
    std::vector<int> num_coins(money + 1); 
    num_coins[0] = 0;
    for (int i = 1; i < money + 1; ++i) {
        num_coins[i] = INT32_MAX;
        for (int j = 0; j < coins.size(); ++j) {
            if (i >= coins[j])
                if (num_coins[i - coins[j]] + 1 < num_coins[i])
                    num_coins[i] = num_coins[i - coins[j]] + 1;
        }
    }

    //print_vector(num_coins);
    return num_coins[money];
}


int main() {
    int money;
    std::cin >> money;
    std::vector<int> coins;
    
    std::string delimiter = ",";
    std::string pattern;

    while (getline(std::cin, pattern)) {
        while (!pattern.empty()) {
            auto f = pattern.find(delimiter);
            if (f != std::string::npos) {
                coins.push_back(std::stoi(pattern.substr(0, f)));
                pattern.erase(0, f + 1);
            } 
            else {
                coins.push_back(std::stoi(pattern));
                break;
            }
               
        }
    }

    // while (std::cin >> tmp)
    //     coins.push_back(tmp);

    //print_vector(coins);
        
    std::cout << DPChange(money, coins) << std::endl;
    return 0;
}