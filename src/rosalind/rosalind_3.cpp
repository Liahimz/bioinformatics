#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <utility>
#include <algorithm>

std::string get_compl(std::string &in) {
    std::string out;
    for (int i = 0; i < in.length(); ++i) {
        if (in.c_str()[i] == 'A')
            out.append(1, 'T');
        if (in.c_str()[i] == 'T')
            out.append(1, 'A');
        if (in.c_str()[i] == 'G')
            out.append(1, 'C');
        if (in.c_str()[i] == 'C')
            out.append(1, 'G');
    }
    return out;
}

std::string reverse_comp(std::string in) {
    std::string out = in;
    std::reverse(out.begin(), out.end());
    return get_compl(out);
}
int main() {
	std::string str;
	std::cin >> str;
    std::cout << reverse_comp(str) << std::endl;
	return 0;
}