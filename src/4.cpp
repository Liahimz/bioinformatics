#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <utility>
#include <algorithm> 


class genome {
    private:
        std::string kmer;
        int count;
    public:
        genome(std::string name, int k) {
            kmer = name;
            count = k;
        }
        genome(std::string name) {
            kmer = name;
            count = 1;
        }

        int get_count() {
            return count;
        }

        std::string get_kmer() {
            return kmer;
        } 

        void print_genome() {
            std::cout << kmer << std::endl;
        }

        int kmer_exist(std::string &tmp) {
            return kmer.compare(tmp) == 0 ? 1 : 0;
        }

        void set_count(int a) {
            count = a;
        }

        void add(int a) {
            count += a;
        }


        
        bool operator<(const genome&) const;
        bool operator>(const genome&) const;
};

bool genome::operator< (const genome& c) const
{ 
    return this->count < c.count;
}

bool genome::operator> (const genome& c) const
{ 
    return this->count > c.count;
}

char set[] = {'A', 'T', 'G', 'C'};

void generator(std::vector<genome>& mas, char set[], std::string prefix, int k)
{
     
   
    if (k == 0)
    {
        //std::cout << (prefix) << std::endl;
        mas.push_back(prefix);
        return;
    }
   
    for (int i = 0; i < 4; i++)
    {
        std::string newPrefix;
         
        newPrefix = prefix + set[i];
         
        generator(mas, set, newPrefix, k - 1);
    }
}


int find_pattern(std::vector<genome> &a, std::string &b) {
    for (int i = 0; i < a.size(); ++i) {
        if (a[i].kmer_exist(b))
            return i;
    }
    return 0;
}


void print_vecor(std::vector<genome>& m) {
    for (int i = 0; i < m.size(); ++i)
        if (m[i].get_count() == m[0].get_count())
            m[i].print_genome();
}


int HammingDist(const std::string &str1, const std::string &str2)
{
    int count = 0;
    for (int i = 0; i < str1.length(); ++i) {
        if (str1[i] != str2[i])
            count ++;
    }
    return count;
}

int main() {
    std::string str;
    std::cin >> str;
    int k, d;
    std::cin >> k >> d;

    std::vector<genome> store;
    generator(store, set, "", k);
    //print_vecor(test);
    

    // std::unordered_map<std::string, int> storage;
    // std::vector<genome> store;
    // for (int i = 0; i < str.length() - k; ++i) {
    //     std::string pattern = str.substr(i, k);

        
    //     int tmp = find_pattern(store, pattern);
    //     if (tmp)
    //         store[tmp].add(1);
    //     else 
    //         store.push_back(genome(pattern, 1));
    // } 




    // std::vector<genome> new_store;
    // for(int i = 0; i < store.size(); ++i) {

    //     int count = 0;
    //     for(int j = 0; j < store.size(); ++j) {
    //         if (HammingDist(store[i].get_kmer(), store[j].get_kmer()) <= d)
    //             count += store[j].get_count();
    //     }

    //     std::string pattern = store[i].get_kmer();
    //     int tmp = find_pattern(new_store, pattern);
    //     if (tmp)
    //         new_store[tmp].set_count(count);
    //     else 
    //         new_store.push_back(genome(pattern, count));
    // }



    std::vector<genome> new_store;
    for(int i = 0; i < store.size(); ++i) {

        int count = 0;
        for(int j = 0; j < str.length() - k; ++j) {
            std::string pattern = str.substr(j, k);
            if (HammingDist(store[i].get_kmer(), pattern) <= d)
                count += store[i].get_count();
        }

        std::string pattern = store[i].get_kmer();
        int tmp = find_pattern(new_store, pattern);
        if (tmp)
            new_store[tmp].set_count(count);
        else 
            new_store.push_back(genome(pattern, count));
    }





    std::sort(new_store.begin(), new_store.end(), std::greater<>());
    print_vecor(new_store);
        
    return 0;
}