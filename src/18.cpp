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

void print_vecor(std::vector<int32_t>& m) {
    for (int32_t i = 0; i < m.size(); ++i)
       std::cout << m[i] << std::endl;
}

void print_vecor(std::vector<std::string>& m) {
    for (int32_t i = 0; i < m.size(); ++i)
       std::cout << m[i] << std::endl;
}


void print_vecor(std::vector<std::pair<std::string, int32_t>>& m) {
    for (int32_t i = 0; i < m.size(); ++i)
       std::cout << m[i].first << " | " << m[i].second << std::endl;
}

template <class T>
bool find_element(int elem, T container) {
    return (std::find(container.begin(), container.end(), elem) != container.end()) ?  true :  false;
}

void extend(std::vector<std::pair<std::string, int32_t>>& m, std::vector<int32_t> mas) {
    std::vector<std::pair<std::string, int32_t>> new_m;
    for (int i = 0; i < m.size(); ++i) {
        for (int j = 0; j < mas.size(); ++j) {
            new_m.push_back(std::make_pair(m[i].first + "-" + std::to_string(mas[j]), m[i].second + mas[j]));
        }
    }

    m = new_m;
}

int vec_sum(std::vector<int> vec, int start, int end) {
    int sum = 0;
    for (int i = start; i < end; ++i) {
        sum += vec[i];
    }
    return sum;
}

std::vector<int> cyclospectrum(std::string peptide) {
    std::vector<int> spectrum = {0};
    std::string pep2 = peptide + "-" + peptide;
    std::string delimiter = "-";
    std::string token;
    int pos = 0;

    std::vector<int> elems;

    while ((pos = pep2.find(delimiter)) != std::string::npos) {
        token = pep2.substr(0, pos);
        //std::cout << token << std::endl;
        elems.push_back(std::stoi(token));
        pep2.erase(0, pos + delimiter.length());
    }

    elems.push_back(std::stoi(pep2));
   
    for (int i = 1; i < elems.size() / 2; ++i) {
        for (int j = 0; j < elems.size() / 2; ++j) {
            spectrum.push_back(vec_sum(elems, j, j + i));
        }
    }

    spectrum.push_back(vec_sum(elems, 0, elems.size() / 2));

    std::sort(spectrum.begin(), spectrum.end());

    return spectrum;
}



int main() {
    std::vector<int32_t> mas = {57, 71, 87, 97, 99, 101, 103, 113, 114, 115, 128, 129, 131, 137, 147, 156, 163, 186};

    int32_t x;
    std::vector<int32_t> spectr;
    while(std::cin >> x)
        spectr.push_back(x);

    std::vector<std::pair<std::string, int32_t>> peptides_pattern;
    std::vector<int32_t> new_mas;
    for (int i = 0; i < mas.size(); ++i) {
        if (find_element<std::vector<int32_t>>(mas[i], spectr))  {
            peptides_pattern.push_back(std::make_pair(std::to_string(mas[i]), mas[i]));
            new_mas.push_back(mas[i]);
        }
    }

    int max_sum = spectr[spectr.size() - 1];
    std::vector<std::string> ans;

    int i = 0; 

    while (!peptides_pattern.empty()) {
        extend(peptides_pattern, new_mas);
        // print_vecor(peptides_pattern);
        // std::cout << "-----------------" << std::endl;
        std::vector<std::pair<std::string, int32_t>> pattern;
        for (int i = 0; i < peptides_pattern.size(); ++i) {
            if (peptides_pattern[i].second == max_sum) {
                std::vector<int> some = cyclospectrum(peptides_pattern[i].first);
                if (std::equal(some.begin(), some.end(), spectr.begin()))
                    ans.push_back(peptides_pattern[i].first);
                //peptides_pattern.erase(peptides_pattern.begin() + i);
                continue;
            }
            else if (!(find_element<std::vector<int32_t>>(peptides_pattern[i].second, spectr))) {
                //peptides_pattern.erase(peptides_pattern.begin() + i);
                continue;
            } 
            else {
                pattern.push_back(peptides_pattern[i]);
            }
        }
        peptides_pattern = pattern;
        //print_vecor(peptides_pattern);
        //++i;
    }

    // std::vector<int> some = cyclospectrum(ans[0]);
    // std::cout << std::equal(some.begin(), some.end(), spectr.begin()) << std::endl;
    // print_vecor(peptides_pattern);
    //print_vecor(some);
    print_vecor(ans);
    return 0;
}