#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <utility>
#include <algorithm>

void print_map(std::map<char, int>& m)
{
    for(std::map<char, int>::iterator it = m.begin(); it != m.end(); ++it) 
        std::cout << it->second << std::endl;
}

int main() {
	std::string str;
	std::cin >> str;
	std::replace( str.begin(), str.end(), 'T', 'U');
    std::cout << str << std::endl;
	return 0;
}