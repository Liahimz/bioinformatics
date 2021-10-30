#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <string>

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

        void print_genome() {
            std::cout << kmer << std::endl;
        }

        int kmer_exist(std::string &tmp) {
            return kmer.compare(tmp) == 0 ? 1 : 0;
        }
};


// void print_map(std::unordered_map<std::string, int>& m)
// {
//     for(std::unordered_map<std::string, int>::iterator it = m.begin(); it != m.end(); ++it) 
//         std::cout << it->first << " = " << it->second << ";" << std::endl;
// }


int main() {
    std::string str;
    std::cin >> str;
    int k, l, t;
    std::cin >> k >> l >> t;

    std::vector<genome> mas;
    //std::unordered_map<std::string, int> vac;

    for (int i = 0; i < str.length() - k; ++i) {
        
        int count = 1;
        std::string pattern = str.substr(i, k);
        int pos = i;
        while ((pos = str.find(pattern, pos + k)) && pos != std::string::npos) {
            
            count ++;
            //std::cout << pos << std::endl;
           
        }
            
        if (count >= t) {
            //vac[pattern] = count;
            int r = 0;
            for (int j = 0; j < mas.size(); ++j)
                r += mas[j].kmer_exist(pattern);
            if (!r)
                mas.push_back(genome(pattern, count));
        }
            

        //std::cout << "i=" << i << " pattern = " << pattern << std::endl;
    }

    for (int i = 0; i < mas.size(); ++i)
        mas[i].print_genome();

    // std::cout << "--------------------------------" << std::endl;

    // print_map(vac);

        
    return 0;
}