#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <utility>
#include <algorithm> 

int main() {
    std::string str;
    std::cin >> str;
    
    std::vector<std::pair<int, int>> mas;
    mas.push_back(std::make_pair(0, 0));
    int count = 0;
    for (int i = 0; i < str.length(); ++i) {
        if (str.c_str()[i] == 'C' || str.c_str()[i] == 'c')
            mas.push_back(std::make_pair(--count, i+1));
        if (str.c_str()[i] == 'G' || str.c_str()[i] == 'g')
            mas.push_back(std::make_pair(++count, i+1));
    }

    std::sort (mas.begin(), mas.end());

    for (int i = 0; i < mas.size(); ++i) {
        if (mas[i].first == mas[0].first)
            std::cout << mas[i].second << std::endl;
        //std::cout << mas[i].first << " " << mas[i].second << std::endl;
    }
        
    return 0;
}