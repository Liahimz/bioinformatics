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


void print_deque(std::deque<std::string>& m) {
    for (int i = 0; i < m.size(); ++i)
       std::cout << m[i] << std::endl;
}

void print_vector(std::vector<int>& m) {
    for (int i = 0; i < m.size(); ++i)
       std::cout << m[i] << " ";
}

void print_deque(std::deque<int>& m) {
    for (int i = 0; i < m.size(); ++i)
       std::cout << m[i] << " ";
}

void print_map(std::map<int, std::deque<int>>& m)
{
    for(std::map<int, std::deque<int>>::iterator it = m.begin(); it != m.end(); ++it) {
        std::cout << it->first << " = ";
        print_deque(it->second);
        std::cout << ";" << std::endl;
    }   
        
}

int rec(std::map<int, std::deque<int>> dict, int cur, std::string ans, std::vector<std::string> &k_mers, int k, std::vector<std::string> &ans_v) {
    if (dict.find(cur) == dict.end()) {
        ans.append(k_mers[cur].substr(k-1, k));
        // std::cout << ans.size() << " " << (k + (k_mers.size()-1)) << std::endl;
        // if (ans.size() == (k + (k_mers.size()-1)))
        //     std::cout << "ans " << ans << std::endl;
        ans_v.push_back(ans);
        return 0;
    }
    else {
        for (int i = 0; i < dict[cur].size(); ++i) {
            //std::cout << cur << std::endl;
            //std::cout << cur << " " << ans << std::endl;
            ans.append(k_mers[cur].substr(k-1, k));
            int x = dict[cur][i];
            if (dict.find(cur) != dict.end())
                dict[cur].erase(dict[cur].begin() + i);
            rec(dict, x, ans, k_mers, k, ans_v);
            ans = ans.substr(0, ans.size() - 1);
        }
    }
    return 0;
} 

int main() {
    std::vector<std::string> k_mers;
    int k;
    std::cin >> k;
    std::deque<std::string> begins;
    std::deque<std::string> ends;
    std::string pattern;

    while (getline(std::cin, pattern)) {
        if (!pattern.empty()) {
            k_mers.push_back(pattern);
            begins.push_back(pattern.substr(0, k-1));
            ends.push_back(pattern.substr(1, k-1));
        }
    }

    std::map<int, std::deque<int>> dict;

    int start = 0;
    for (int i = 0; i < begins.size(); ++i) {
        int c = 0;
        for (int j = 0; j < ends.size(); ++j) {
            if (begins[i].compare(ends[j]) == 0) {
                dict[j].push_back(i);
            }
            else {
                c ++;
            }
        }
        if (c == begins.size())
            start = i;
           
    }

    print_map(dict);
    std::cout << start << std::endl;
    // int cur = start;
    // 
    // while (dict.find(cur) != dict.end()) {
    //     ans.push_back(cur);
    //     int vec_len = dict[cur].size();
    //     //std::cout << cur << " " << vec_len << std::endl;
    //     cur = dict[cur][vec_len - 1];
        
    //     // if (dict.find(cur) != dict.end())
    //     //     dict[cur].pop_back();
        
    // }

    std::string ans_s;
    ans_s.append(k_mers[start].substr(0, k-1));
    std::vector<std::string> ans;
    rec(dict, start, ans_s, k_mers, k, ans);
    std::cout << "size " << k_mers.size() << std::endl;
    std::cout << "len " << (k + (k_mers.size()-1)) << std::endl;
    int max_i, max_len = 0;
    for (int i = 0; i < ans.size(); ++i) {
        if (ans[i].size() == (k + (k_mers.size()-1)))
            std::cout << ans[i] << std::endl;
    }
    // std::cout << k_mers[cur].substr(k-1, k);
    // std::cout << std::endl;

    
}