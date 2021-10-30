#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <utility>
#include <algorithm> 


int HammingDist(const std::string &str1, const std::string &str2)
{
    int count = 0;
    for (int i = 0; i < str1.length(); ++i) {
        if (str1[i] != str2[i])
            count ++;
    }
    return count;
}

std::string get_compl(std::string &in) {
    std::string out;
    for (int i = 0; i < in.length(); ++i) {
        if (in.c_str()[i] == 'A')
            out.append(1, 'T');
        if (in.c_str()[i] == 'T')
            out.append(1, 'A');
        if (in.c_str()[i] == 'G')
            out.append(1, 'C');
        if (in.c_str()[i] == 'C')
            out.append(1, 'G');
    }
    return out;
}

std::string reverse_comp(std::string in) {
    std::string out = in;
    std::reverse(out.begin(), out.end());
    return get_compl(out);
}

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

        int kmer_compl(std::string &tmp) {
            std::string ntmp = get_compl(tmp);
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

char comp_set[] = {'T', 'A', 'C', 'G'};

void generator(std::vector<genome>& mas, std::vector<genome>& comp_mas, char set[], char comp_set[], std::string prefix, std::string comp_prefix, int k)
{
     
   
    if (k == 0)
    {
        mas.push_back(prefix);
        comp_mas.push_back(comp_prefix);
        return;
    }
   
    for (int i = 0; i < 4; i++)
    {
        std::string newPrefix, new_compPrefix;
         
        newPrefix = prefix + set[i];
        new_compPrefix = comp_prefix + comp_set[i];
        generator(mas, comp_mas, set, comp_set, newPrefix, new_compPrefix, k - 1);
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




int main() {
    std::string str;
    std::cin >> str;
    int k, d;
    std::cin >> k >> d;

    std::vector<genome> store;
    std::vector<genome> comp_store;
    generator(store, comp_store, set, comp_set,"", "", k);


    std::vector<genome> new_store;
    for(int i = 0; i < store.size(); ++i) {

        int count = 0;
        for(int j = 0; j < str.length() - k; ++j) {
            std::string pattern = str.substr(j, k);
            if (HammingDist(store[i].get_kmer(), pattern) <= d)
                count += 1; //store[i].get_count();

            if (HammingDist(reverse_comp(store[i].get_kmer()), pattern) <= d)
                count += 1; //store[i].get_count();
            // if (HammingDist(store[i].get_kmer(), get_compl(pattern)) <= d)
            //     count += store[i].get_count();
            // if (HammingDist(comp_store[i].get_kmer(), pattern) <= d)
            //     count += store[i].get_count();
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