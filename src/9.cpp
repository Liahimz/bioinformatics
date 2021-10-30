#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <utility>
#include <algorithm> 
#include <random>
#include <chrono>


int SUPER_SCORE;

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

std::map<char, float>* get_profile (std::string* motifs, int motifs_count, int motif_len, int skip_id = -1) {
    std::map<char, float> *profile = new std::map<char, float> [motif_len];
    
    for (int i = 0; i < motif_len; ++i) {
        profile[i]['A'] += 1;
        profile[i]['C'] += 1;
        profile[i]['G'] += 1;
        profile[i]['T'] += 1;
    }

    for (int i = 0; i < motif_len; ++i) {
        for (int j = 0; j < motifs_count; ++j) {
            if (skip_id != -1 && j == skip_id)
                continue;
            profile[i][motifs[j].c_str()[i]] += 1;
        }
    } 

    int count = motifs_count;
    if (skip_id != -1)
        count -= 1;

    for (int i = 0; i < motif_len; ++i) {
        profile[i]['A'] /= (static_cast<float>(motifs_count + count));
        profile[i]['C'] /= (static_cast<float>(motifs_count + count));
        profile[i]['G'] /= (static_cast<float>(motifs_count + count));
        profile[i]['T'] /= (static_cast<float>(motifs_count + count));
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


std::string get_profile_random(std::string str, int k, std::map<char, float>* profile) {
    std::vector<float> distribution;
    
    for(int i = 0; i < str.length() + 1 - k; ++i) {
        std::string pattern = str.substr(i, k);
        float probability = 1;
        for (int j = 0; j < k; ++j) {
            probability *= profile[j][pattern.c_str()[j]];
        }
        distribution.push_back(probability);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::discrete_distribution<> d(distribution.begin(), distribution.end());
    
    std::string pattern = str.substr(d(gen), k); 
    return pattern;
}
 


std::string* GibbsSampler(std::string* matrix, int k, int t, int n, std::string* best_motifs, std::string* motifs) {
    //std::random_device rd;  
    std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distrib(0, matrix[0].length() - k);
    std::uniform_int_distribution<int> t_dist(0, t - 1);
     
    for (int i = 0; i < t; ++i){
        int dist = distrib(gen);
        best_motifs[i] = matrix[i].substr(dist, k);
        motifs[i] = matrix[i].substr(dist, k);
    }
     
    for (int i = 0; i < n; ++i) {

        int rand_index = t_dist(gen);
        
        std::map<char, float>* profile = get_profile(motifs, t, k, rand_index);
        motifs[rand_index] = get_profile_random(matrix[rand_index], k, profile);
        //std::cout << get_score(motifs, t, k) << " " << SUPER_SCORE << std::endl;
        if (get_score(motifs, t, k) < get_score(best_motifs, t, k)) { 
            for (int j = 0; j < t; ++j)
                best_motifs[j] = motifs[j];
        }
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
    int k, t, n;
    std::cin >> k >> t >> n;
    std::string matrix[t];
   
    for (int i = 0; i < t; ++i)
        std::cin >> matrix[i];
    
    std::string* max = new std::string[t];
    int max_score = 1500;


    std::string* best_motifs = new std::string [t];
    std::string* motifs = new std::string [t];
    
    for (int i = 0; i < 20; ++i) {
        std::string* cur = GibbsSampler(matrix, k, t, n, best_motifs, motifs);
        int cur_score = get_score(cur, t, k);
        

        if (cur_score < max_score) { 
            for (int j = 0; j < t; ++j)
                max[j] = cur[j];
            max_score = cur_score;
        }
    }

    for (int j = 0; j < t; ++j)
        std::cout << max[j] << std::endl;

     std::cout << max_score << std::endl;

        
    return 0;
}