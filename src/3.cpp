#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <utility>
#include <algorithm> 


int HammingDist(std::string &str1, std::string &str2)
{
    int count = 0;
    for (int i = 0; i < str1.length(); ++i) {
        if (str1[i] != str2[i])
            count ++;
    }
    return count;
}

int main() {
    std::string pattern;
    std::cin >> pattern;
    std::string str;
    std::cin >> str;
    int d;
    std::cin >> d;

    int k = pattern.length();

    for (int i = 0; i < str.length() - k; ++i) {
        std::string new_pattern = str.substr(i, k);
        if (HammingDist(pattern, new_pattern) <= d)
            std::cout << i << std::endl;
    }
    
        
    return 0;
}