#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <utility>
#include <algorithm> 


int get_score (std::string* motifs, int motifs_count, int motif_len) {
    int score = 0;
    for (int i = 0; i < motif_len; ++i) {
        std::map<char, int> tmp;
        int max = 0;
        for (int j = 0; j < motifs_count; ++j) {
            tmp[motifs[j].c_str()[i]] += 1;
            if (tmp[motifs[j].c_str()[i]] > max) {
                max = tmp[motifs[j].c_str()[i]];
            }
        }
        score += motifs_count - max;
    } 
    return score;
}

std::map<char, float>* get_profile (std::string* motifs, int motifs_count, int motif_len) {
    std::map<char, float> *profile = new std::map<char, float> [motif_len];
    for (int i = 0; i < motif_len; ++i) {
        profile[i]['A'] += 1;
        profile[i]['C'] += 1;
        profile[i]['G'] += 1;
        profile[i]['T'] += 1;
    }

    for (int i = 0; i < motif_len; ++i) {
        for (int j = 0; j < motifs_count; ++j) {
            profile[i][motifs[j].c_str()[i]] += (1 / (static_cast<float>(motifs_count) * 2));
        }
    } 
    return profile;
}

std::string get_probable (std::string str, int k, std::map<char, float>* profile) {

    std::string probable;
    float max_probability = -1.;
    for(int i = 0; i < str.length() + 1 - k; ++i) {
        std::string pattern = str.substr(i, k);
        float probability = 1;
        for (int j = 0; j < k; ++j) {
            probability *= profile[j][pattern.c_str()[j]];
        }
        //std::cout << pattern << " " << probability << std::endl;
        if (probability > max_probability) {
            max_probability = probability;
            probable = pattern;
        }
    }
    return probable;
}

std::string* greedy_search(std::string* matrix, int k, int t) {
    std::string* best_motifs = new std::string [t];
    for (int i = 0; i < t; ++i)
        best_motifs[i] = matrix[i].substr(0, k);
    
    for (int i = 0; i < matrix[0].length() + 1 - k; ++i) {
        std::string motif =  matrix[0].substr(i, k);
        std::string cur_motifs[t];
        cur_motifs[0] = motif;
        for (int j = 1; j < t; ++j) {
            cur_motifs[j] = get_probable(matrix[j], k, get_profile(cur_motifs, j, k));
        }
        if (get_score(cur_motifs, t, k) < get_score(best_motifs, t, k))
            for (int j = 0; j < t; ++j)
                best_motifs[j] = cur_motifs[j];
    }

    return best_motifs;
}

void print_map(std::map<char, float>& m)
{   
    std::cout << "---------------" << std::endl;
    for(std::map<char, float>::iterator it = m.begin(); it != m.end(); ++it) 
        std::cout << it->first << " = " << it->second << ";" << std::endl;
    std::cout << "---------------" << std::endl;
}

int main() {
    int k, t;
    std::cin >> k >> t;
    std::string matrix[t];

    for (int i = 0; i < t; ++i)
        std::cin >> matrix[i];
    
    std::string* best = greedy_search(matrix, k, t);
    for (int j = 0; j < t; ++j)
                std::cout << best[j] << std::endl;

    std::cout << get_score(best, t, k) << std::endl;
    
        
    return 0;
}