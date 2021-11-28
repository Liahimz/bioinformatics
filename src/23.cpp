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
#include <iterator>
#include <sstream>
#include <fstream>

void print_vector(std::vector<int32_t>& m) {
    for (int32_t i = 0; i < m.size(); ++i)
       std::cout << m[i] << " ";
    std::cout << std::endl;
}

void print_vector(std::vector<std::pair<int, int>>& m) {
    for (int32_t i = 0; i < m.size(); ++i)
       std::cout << m[i].first << " " << m[i].second << std::endl; 
}

template <class T>
void print_vector(T& m) {
    for (int32_t i = 0; i < m.size(); ++i)
       std::cout << m[i] << std::endl; 
}

void print_map(std::map<std::string, int>& m)
{
    for(std::map<std::string, int>::iterator it = m.begin(); it != m.end(); ++it) 
        std::cout << it->first << " = " << it->second << "; ";
    std::cout << std::endl;
}


void print_map(std::map<std::string, std::map<std::string, int>>& m)
{
    for(std::map<std::string, std::map<std::string, int>>::iterator it = m.begin(); it != m.end(); ++it) {
        std::cout << it->first << " : ";
        print_map(it->second);
    }
}

void print_2d_vector(std::vector<std::vector<int>>& m) {
    for (int32_t i = 0; i < m.size(); ++i)
       print_vector(m[i]);
}

int sigma = -5;

void ManhattanTourist(int n, int m, 
                    std::vector<std::vector<int>> &grid,
                    std::vector<std::vector<int>> &back_track,
                    std::string pattern_1,
                    std::string pattern_2,
                    std::map<char, std::map<char, int>> &blosum) 
{
    for (int i = 1; i <= n; ++i) {
        grid[i][0] = grid[i - 1][0] + sigma;
        back_track[i][0] = 3;
    }
    for (int i = 1; i <= m; ++i) {
        grid[0][i] = grid[0][i - 1] + sigma;
        back_track[0][i] = 1;
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1;  j <= m; ++j) {
            char t = pattern_1[i - 1];
            char t2 = pattern_2[j - 1];
            auto tmp = blosum[t][t2];
            grid[i][j] = std::max( grid[i - 1][j - 1] + tmp, std::max(grid[i - 1][j] + sigma, grid[i][j - 1] + sigma));

            if (grid[i][j] == grid[i - 1][j - 1] + tmp)
                back_track[i][j] = 2;
            if (grid[i][j] == grid[i - 1][j] + sigma)
                back_track[i][j] = 3;
            if (grid[i][j] == grid[i][j - 1] + sigma)
                back_track[i][j] = 1;
        }
    }
}


void output_backtrack(std::vector<std::vector<int>> &back_track, std::string pattern_1, std::string pattern_2) {
    int i = pattern_1.size();
    int j = pattern_2.size();
    std::string ans_1 = "";
    std::string ans_2 = "";
    while (i != 0 || j != 0) {
        int dir = back_track[i][j];
        if (dir == 3) {
            ans_1 += pattern_1[i - 1];
            ans_2 += "-";
            --i;
        }
        else if (dir == 1) {
            ans_1 += "-";
            ans_2 += pattern_2[j - 1];
            --j;
        }
        else {
            ans_1 += pattern_1[i - 1];
            ans_2 += pattern_2[j - 1];
            --i;
            --j;
        }
    }

    std::reverse(ans_1.begin(), ans_1.end());
    std::reverse(ans_2.begin(), ans_2.end());

    std::cout << ans_1 << std::endl;
    std::cout << ans_2 << std::endl;
   
}



int main() {
    std::string filename("BLOSUM62.txt");

    std::ifstream input_file(filename);
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '"
             << filename << "'" << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<char> idx = {'A', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S', 'T', 'V', 'W', 'Y'};
    std::map<char, std::map<char, int>> blosum;
    int tmp;

    for (int i = 0; i < idx.size(); ++i) {
        for (int j = 0; j < idx.size(); ++j) {
            input_file >> tmp;
            blosum[idx[i]][idx[j]] = tmp;
        }
    }

    

    std::string pattern_1;
    std::string pattern_2;
    std::cin >> pattern_1;
    std::cin >> pattern_2;

    int n = pattern_1.size();
    int m = pattern_2.size();

    std::vector<std::vector<int>> grid;
    grid.resize(n + 1, std::vector<int>(m + 1, 0));

    std::vector<std::vector<int>> back_track;
    back_track.resize(n + 1, std::vector<int>(m + 1, 0));

    ManhattanTourist(n, m, grid, back_track, pattern_1, pattern_2, blosum);


    // print_2d_vector(grid);

    // std::cout << "-----------------" << std::endl;

    //print_2d_vector(back_track);

    std::cout << grid[n][m] << std::endl;

    //std::cout << "-----------------" << std::endl;

    output_backtrack(back_track, pattern_1, pattern_2);
        
    return 0;
}