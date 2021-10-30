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


void print_map(std::map<std::string,std::string>& m)
{
    for(std::map<std::string,std::string>::iterator it = m.begin(); it != m.end(); ++it) {
        std::cout << it->first << " " << it->second << std::endl;
    }   
        
}

void print_vecor(std::vector<std::string>& m) {
    for (int i = 0; i < m.size(); ++i)
       std::cout << m[i] << std::endl;
}


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

void generator(std::map<std::string, std::string> &dict) {
    std::string pattern = "ACGU";
    std::string ans = "KNKNTTTTRSRSIIMIQHQHPPPPRRRRLLLLEDEDAAAAGGGGVVVV*Y*YSSSS*CWCLFLF";
    for (int i = 0; i < pattern.size(); ++i) {
        for (int k = 0; k < pattern.size(); ++k) {
            for (int j = 0; j < pattern.size(); ++j) {
                std::string out = pattern.substr(i, 1) +  pattern.substr(k, 1) + pattern.substr(j, 1);
                //std::cout << out << " " << ans.substr(i * pattern.size() * pattern.size() + k * pattern.size() + j, 1)<< std::endl;
                dict[out] = ans.substr(i * pattern.size() * pattern.size() + k * pattern.size() + j, 1);
            }
        }
    }
}


bool checker(std::string pattern, std::string amino_acid, std::map<std::string, std::string> &dict) {
    int count = 0;
    std::string reverse = reverse_comp(pattern);
    for (int i = 0; i < amino_acid.size(); ++i) {
        std::string acid = amino_acid.substr(i, 1);

        std::string tmp1 = pattern.substr(3 * i, 3);
        std::replace(tmp1.begin(), tmp1.end(), 'T', 'U');
        
        std::string tmp2 = reverse.substr(3 * i, 3);
        std::replace(tmp2.begin(), tmp2.end(), 'T', 'U');

        if ((acid.compare(dict[tmp1]) == 0) || (acid.compare(dict[tmp2]) == 0)) { 
            count ++;
            //std::cout << acid << " " << dict[pattern.substr(3 * i, 3)] << " " << dict[reverse.substr(3 * i, 3)] << std::endl;
        }
        // std::cout << "-------------" << std::endl;
        // std::cout << pattern.substr(3 * i, 3) << " " << reverse.substr(3 * i, 3) << std::endl;
        // std::cout << acid << " " << dict[pattern.substr(3 * i, 3)] << " " << dict[reverse.substr(3 * i, 3)] << std::endl;
        // std::cout << count << std::endl;
        // std::cout << "-------------" << std::endl;
    }
    if (count == amino_acid.size())
        return true;
    return false;
}


int main() {
    std::string pattern;
    std::cin >> pattern;

    std::string amino_acid;
    std::cin >> amino_acid;
    std::map<std::string, std::string> dict;
    generator(dict);
    
    int k = amino_acid.size() * 3;
    std::vector<std::string> ans;

    for (int i = 0; i < pattern.size() - k; ++i)
        if (checker(pattern.substr(i, k), amino_acid, dict))
            ans.push_back(pattern.substr(i, k));

    print_vecor(ans);

}