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

class element {
private:
    int value;
    int sign;
public:
    element() {
        value = 0;
        sign = 1;
    }

    element(int value_) {
        sign = value_ >= 0 ? 1 : -1;
        value = std::abs(value_);
    }

    element(int value_, int sign_) {
        value = value_;
        sign = sign_;
    }

    int GetValue() {return value;}
    int GetSign() {return sign;}
    void Reverse() {sign *= -1;}
    int IsAdjacency(element& other) {
        if (*this < other) {
            if (sign == 1)
                return (value + 1 == other.value) ? 1 : 0;
            else 
                return (value == other.value + 1) ? 1 : 0;
        }
        return 0;
    }

    element& operator=(const element& other) {
        if (this == &other)
            return *this;
        
        value = other.value;
        sign = other.sign;

        return *this;
    }

    friend bool operator< (const element& lhs, const element& rhs);
    friend bool operator> (const element& lhs, const element& rhs);  
    friend bool operator== (const element& lhs, const element& rhs);
    friend bool operator!= (const element& lhs, const element& rhs);  
    friend std::ostream& operator<<(std::ostream& os, const element& dt);
};

bool operator< (const element& lhs, const element& rhs){ return lhs.sign * lhs.value < rhs.sign * rhs.value;}
bool operator> (const element& lhs, const element& rhs){ return rhs < lhs; }
bool operator== (const element& lhs, const element& rhs){ return ((lhs.sign == rhs.sign) && (lhs.value == rhs.value));}
bool operator!= (const element& lhs, const element& rhs){ return !(lhs == rhs);}
std::ostream& operator<<(std::ostream& os, const element& dt){os << (dt.sign == -1 ? "-" : "+") << dt.value; return os;}


void print_vector(std::vector<element>& m) {
    std::cout << "(";
    for (size_t i = 0; i < m.size(); ++i) {
        if (i < m.size() - 1)
            std::cout << m[i] << " ";
        else
            std::cout << m[i];
    }
       
    std::cout << ")";
}

void print_vector(std::vector<std::vector<element>>& m) {
    for (size_t i = 0; i < m.size(); ++i) {
        print_vector(m[i]);
    }
    std::cout << std::endl;   
}

void print_vector(std::vector<int>& m) {
    for (size_t i = 0; i < m.size(); ++i) {
        if (i < m.size() - 1)
            std::cout << m[i] << " ";
        else
            std::cout << m[i];
    }
    std::cout << std::endl;
}

void print_vector(std::vector<std::pair<int, int>> &m) {
    for (size_t i = 0; i < m.size(); ++i) {
        if (i < m.size() - 1)
            std::cout << m[i].first << ", " << m[i].second << std::endl;
        else
            std::cout << m[i].first << ", " << m[i].second << std::endl;
    }
    // std::cout << std::endl;
}

void swapper(size_t first, size_t last, std::vector<element> &P) {
    auto vec_iter = P.begin();

    std::reverse(vec_iter + first, vec_iter + last);
    for (int i = first; i < last; ++i) 
        P[i].Reverse();
    return;
}

int count_brealpoints(std::vector<element> &P) {
    int count = 0;
    for (int i = 0; i < P.size() - 1; ++i) {
        if (! P[i].IsAdjacency(P[i + 1])) {
            // std::cout << P[i] << " " << P[i + 1] << std::endl;
            ++count;
        }
    }
    return count;
}


void get_sequence (std::vector<std::vector<element>> &long_sequence) {
    std::string delimiter_in = " ";
    std::string delimiter_out_0 = "(";
    std::string delimiter_out_1 = ")";
    std::string line;
    
    getline(std::cin, line);
    while (!line.empty()) {
        std::vector<element> sequence;
        auto out_0 = line.find(delimiter_out_0);
        auto out_1 = line.find(delimiter_out_1);
        std::string pattern = line.substr(out_0 + 1, out_1 - 1);
        // std::cout << pattern << std::endl;
        // pattern = pattern.substr(1, pattern.size() - 2);
        while (!pattern.empty()) {
            auto f = pattern.find(delimiter_in);
            if (f != std::string::npos) {
                sequence.push_back(element(std::stoi(pattern.substr(0, f))));
                pattern.erase(0, f + 1);
            } 
            else {
                sequence.push_back(element(std::stoi(pattern)));
                break;
            }
                
        }
        long_sequence.push_back(sequence);
        line.erase(out_0, out_1 + 1);
    }
}

void chromosome_to_cycle(std::vector<element> &sequence, std::vector<int> &nodes) {
    for (size_t i = 0; i < sequence.size(); ++i) {
        if (sequence[i].GetSign() == 1) {
            nodes.push_back(2 * sequence[i].GetValue() - 1);
            nodes.push_back(2 * sequence[i].GetValue());
        }
        else {
            nodes.push_back(2 * sequence[i].GetValue());
            nodes.push_back(2 * sequence[i].GetValue() - 1);
        }
        
    }
}

void color_edges(std::vector<std::vector<element>>& m, std::vector<std::pair<int, int>> &edges) {
    for (size_t i = 0; i < m.size(); ++i) {
        std::vector<int> nodes;
        chromosome_to_cycle(m[i], nodes);
        // print_vector(nodes);
        for (size_t j = 0; j < nodes.size() / 2; ++j) {
            int heads = 2 * j + 1;
            int tails = (2 * j + 2) % nodes.size();
            edges.push_back(std::make_pair(nodes[heads], nodes[tails]));
        }
    }
}

int count_cycles(std::vector<std::pair<int, int>> &left, std::vector<std::pair<int, int>> &right) {
    int cycles = 0;
    int size = left.size() + right.size();

    std::vector<std::pair<int, int>> adj_list;
    adj_list.resize(size + 1);
    int visited[size + 1] = {0};

    for (auto t : left) {
        adj_list[t.first].first = t.second;
        adj_list[t.second].first = t.first;
    }
    for (auto t : right) {
        adj_list[t.first].second = t.second;
        adj_list[t.second].second = t.first;
    }

    // print_vector(adj_list);

    for (int i = 1; i <= size ; ++i) {
        if (visited[i] == 0) {
            visited[i] = 1;
            int node = i;
            int color = 0;
            for (;;) {
                if (color == 1)
                    node = adj_list[node].second;
                else
                    node = adj_list[node].first;

                if (node == i) {
                    cycles += 1;
                    break;
                }
                visited[node] = 1;
                color = (color+1) % 2;
            }
        }
    }
    return cycles;
}

int main() {
    std::vector<element> sequence;
    std::vector<std::vector<element>> P;
    std::vector<std::vector<element>> Q;

    
    get_sequence(P);
    // print_vector(P);

    get_sequence(Q);
    // print_vector(Q);
    // sequence.push_back(element(sequence.size()));
    std::vector<std::pair<int, int>> edges_p;
    std::vector<std::pair<int, int>> edges_q;
    color_edges(P, edges_p);
    color_edges(Q, edges_q);

    print_vector(edges_p);
    print_vector(edges_q);

    int cycles = count_cycles(edges_p, edges_q);

    // std::cout << cycles << std::endl;

    std::cout << (edges_p.size() + edges_q.size()) / 2 - cycles << std::endl;
    // print_vector(sequence);
    // std::cout << count_brealpoints(sequence) << std::endl;
    return 0;
}