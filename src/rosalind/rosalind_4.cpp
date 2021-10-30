#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <utility>
#include <algorithm> 


class FASTA {
    private:
        std::string name;
        std::string data;
        float gc_cont;
    public:
        FASTA(std::string a, std::string b, float c) {
            name = a.substr(1, a.size() - 1);
            data = b;
            gc_cont = c;
        }
        FASTA(std::string a, std::string b) {
            name = a.substr(1, a.size() - 1);
            data = b;
            gc_cont = 0.;
        }
        void set_count(float a) {
            gc_cont = a;
        };

        void print() {
            std::cout << name <<  std::endl;
            //std::cout << data <<  std::endl;
            std::cout << gc_cont <<  std::endl;
        };

        bool operator<(const FASTA&) const;
        bool operator>(const FASTA&) const;
};

bool FASTA::operator< (const FASTA& c) const
{ 
    return this->gc_cont < c.gc_cont;
}

bool FASTA::operator> (const FASTA& c) const
{ 
    return this->gc_cont > c.gc_cont;
}

float get_gc(std::string tmp) {
    int gc = 0;
    int all = 0;
    for (int i = 0; i < tmp.size(); ++i) {
        if (tmp.c_str()[i] == 'C' || tmp.c_str()[i] == 'G')
            gc += 1;
        all += 1;
    }
    return (gc / static_cast<float>(all)) * 100;
}

int main() {
    
    std::string name;
    std::string pattern;

    std::vector<FASTA> store;
    
    std::string str;
    int count = 0;
    while (getline(std::cin, str)) {
        if (str.c_str()[0] == '>' && count) {
            store.push_back(FASTA(name, pattern, get_gc(pattern)));
            name = str;
            pattern = "";
        }
        else if (str.c_str()[0] == '>') {
            name = str;
            count += 1;
        }
        else 
            pattern.append(str);
    }
    store.push_back(FASTA(name, pattern, get_gc(pattern)));

    std::sort(store.begin(), store.end(), std::greater<>());

    //for (int i = 0; i < store.size(); ++i)
    store[0].print();
        
    return 0;
}