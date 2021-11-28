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
       
    std::cout << ")" << std::endl;
}

void swapper(size_t first, size_t last, std::vector<element> &P) {
    auto vec_iter = P.begin();

    std::reverse(vec_iter + first, vec_iter + last);
    for (int i = first; i < last; ++i) 
        P[i].Reverse();
    return;
}

int GreedySorting(std::vector<element> &P) {
    for (int i = 0; i < P.size(); ++i) {
        if (P[i] != element(i + 1)) {
            size_t index = 0;
            for (int j = i; j < P.size(); ++j) {
                //std::cout << "P[j] = " << P[j].GetValue() << " j = " << j << std::endl;
                if (P[j].GetValue() == i + 1) {
                    index = j + 1;
                }
                    
            }
                
            //std::cout << "i = " << i << " index = " << index << std::endl;
            if (index)
                swapper(i, index, P);
            print_vector(P);

            if (P[i].GetSign() == -1) {
                P[i].Reverse();
                print_vector(P);
            }
        }
    }
    return 0;
}


int main() {
    int x;
    std::vector<element> sequence;

    std::string delimiter = " ";
    std::string pattern;

    while (getline(std::cin, pattern)) {
        pattern = pattern.substr(1, pattern.size() - 2);
        while (!pattern.empty()) {
            auto f = pattern.find(delimiter);
            if (f != std::string::npos) {
                sequence.push_back(element(std::stoi(pattern.substr(0, f))));
                pattern.erase(0, f + 1);
            } 
            else {
                sequence.push_back(element(std::stoi(pattern)));
                break;
            }
               
        }
    }

    GreedySorting(sequence);
     
    return 0;
}