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
    
    std::string str;
    std::cin >> str;

    std::string pattern;
    std::cin >> pattern;
    

    std::cout << HammingDist(str, pattern);
        
    return 0;
}