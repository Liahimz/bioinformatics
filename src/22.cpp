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


void print_2d_vector(std::vector<std::vector<int>>& m) {
    for (int32_t i = 0; i < m.size(); ++i)
       print_vector(m[i]);
}



void ManhattanTourist(int n, int m, 
                    std::vector<std::vector<int>> &down, 
                    std::vector<std::vector<int>> &right, 
                    std::vector<std::vector<int>> &grid) 
{
    for (int i = 1; i <= n; ++i) {
        grid[i][0] = grid[i - 1][0] + down[i - 1][0];
    }
    for (int i = 1; i <= m; ++i) {
        grid[0][i] = grid[0][i - 1] + right[0][i - 1];
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1;  j <= m; ++j) {
            grid[i][j] = std::max(grid[i - 1][j] + down[i - 1][j], grid[i][j - 1] + right[i][j - 1]);
        }
    }
}


int main() {
    int n;
    std::cin >> n;

    int m;
    std::cin >> m;

    std::vector<std::vector<int>> grid;
    grid.resize(n + 1, std::vector<int>(m + 1, 0));

    std::vector<std::vector<int>> down;
    down.resize(n, std::vector<int>(m + 1, 0));

    std::vector<std::vector<int>> right;
    right.resize(n + 1, std::vector<int>(m, 0));


    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m + 1; ++j) {
            std::cin >> down[i][j];
        }
    }

    std::string del;
    std::cin >> del;

    for (int i = 0; i < n + 1; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cin >> right[i][j];
        }
    }

    // print_2d_vector(grid);
    // std::cout << "-----------------" << std::endl;

    // print_2d_vector(down);
    // std::cout << "-----------------" << std::endl;
    // print_2d_vector(right);
    // std::cout << "-----------------" << std::endl;
    ManhattanTourist(n, m, down, right, grid);


    // print_2d_vector(grid);

    std::cout << grid[n][m] << std::endl;
        
    return 0;
}