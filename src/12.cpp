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
#include <bitset>

void print_vector(std::vector<std::string>& m) {
    for (int i = 0; i < m.size(); ++i)
       std::cout << m[i] << std::endl;
}

void cut(std::vector<std::string>& m, int k) {
    for (int i = 0; i < m.size(); ++i)
       m[i] = m[i].substr(m[i].size() - k, m[i].size());
}

void print_deque(std::deque<std::string>& m) {
    for (int i = 0; i < m.size(); ++i)
       std::cout << m[i] << " ";
}

void print_map(std::map<std::string, std::deque<std::string>>& m)
{
    for(std::map<std::string, std::deque<std::string>>::iterator it = m.begin(); it != m.end(); ++it) {
        std::cout << it->first << " = ";
        print_deque(it->second);
        std::cout << ";" << std::endl;
    }   
        
}

int main() {
    int k;
    std::cin >> k;
    std::vector<std::string> bin_vec;
    std::deque<std::string> begins;
    std::deque<std::string> ends;

    int pow = 1 << k;
    for (int i = 0; i < pow; ++i) {
        bin_vec.push_back(std::bitset<32>(i).to_string());   
    }
    cut(bin_vec, k);
    // print_vector(bin_vec);

    std::string start = bin_vec[0];
    std::string end = bin_vec[1 << (k - 1)];
    // std::cout << start << " " << end << std::endl;

    std::map<std::string, std::deque<std::string>> dict;

    for (int i = 0; i < pow; ++i) {
        if ((bin_vec[i].compare(start) != 0) && (bin_vec[i].compare(end) != 0)) {
            dict[bin_vec[i].substr(0, k - 1)].push_back(bin_vec[i].substr(1, k));
            dict[bin_vec[i].substr(1, k)].push_back(bin_vec[i].substr(0, k - 1));
        } 
    }

    print_map(dict);

    std::string cur = bin_vec[0].substr(0, k - 1);
    std::string ans = "00";

    while(dict[cur].size() > 0) {
        std::string next = cur.substr(1, cur.size());
        ans += next.substr(0, 1);
        next += (std::find(dict[cur].begin(), dict[cur].end(), next + "1") == dict[cur].end()) ? "0" : "1";
        dict[cur].erase(std::find(dict[cur].begin(), dict[cur].end(), next));
        dict[next].erase(std::find(dict[next].begin(), dict[next].end(), cur));
        cur = next;
    }

    

    std::cout << ans << std::endl;


    // print_map(dict);

}