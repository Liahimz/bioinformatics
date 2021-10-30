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

    std::string pattern;
    std::cin >> pattern;
    

    int k = pattern.length();

    int pos = 0;
    while (pos != std::string::npos) {
        pos = str.find(pattern, pos + 1);
        if (pos != std::string::npos)
            std::cout << pos + 1 << std::endl;
    }
        
    return 0;
}