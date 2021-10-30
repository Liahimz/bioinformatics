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

class CycloPeptide {
private:
    std::string Peptide;
    int Mass;
    int Score;
public:
    CycloPeptide() {
        Peptide = "";
        Mass = 0;
        Score = 0;
    }
    CycloPeptide(std::string peptide, int mass, int score) {
        Peptide = peptide;
        Mass = mass;
        Score = score;
    }

    std::string GetPeptide() {return Peptide;}
    int GetMass() {return Mass;}
    int GetScore() {return Score;}

    friend bool operator< (const CycloPeptide& lhs, const CycloPeptide& rhs);
    friend bool operator> (const CycloPeptide& lhs, const CycloPeptide& rhs);  
    friend bool operator== (const CycloPeptide& lhs, const CycloPeptide& rhs);
    friend bool operator!= (const CycloPeptide& lhs, const CycloPeptide& rhs);  
    friend std::ostream& operator<<(std::ostream& os, const CycloPeptide& dt);
};

bool operator< (const CycloPeptide& lhs, const CycloPeptide& rhs){ return lhs.Score < rhs.Score;}
bool operator> (const CycloPeptide& lhs, const CycloPeptide& rhs){ return rhs < lhs; }
bool operator== (const CycloPeptide& lhs, const CycloPeptide& rhs){ return ((lhs.Score == rhs.Score) && (lhs.Mass == rhs.Mass) && (lhs.Peptide == rhs.Peptide));}
bool operator!= (const CycloPeptide& lhs, const CycloPeptide& rhs){ return !(lhs == rhs);}
std::ostream& operator<<(std::ostream& os, const CycloPeptide& dt){ os << "Peptide: " << dt.Peptide << " Score: " << dt.Score; return os;}


int vec_sum(std::vector<int> vec, int start, int end) {
    int sum = 0;
    for (int i = start; i < end; ++i) {
        sum += vec[i];
    }
    return sum;
}

std::vector<int> CycloSpectrum(std::string peptide) {
    std::vector<int> spectrum = {0};
    if (!peptide.empty()) {
        std::string pep2 = peptide + "-" + peptide;
        std::string delimiter = "-";
        std::string token;
        int pos = 0;
        std::vector<int> elems;

        while ((pos = pep2.find(delimiter)) != std::string::npos) {
            token = pep2.substr(0, pos);
            elems.push_back(std::stoi(token));
            pep2.erase(0, pos + delimiter.length());
        }

        elems.push_back(std::stoi(pep2));

        for (int i = 1; i < (elems.size() / 2); ++i) {
            for (int j = 0; j < (elems.size() / 2); ++j) {
                spectrum.push_back(vec_sum(elems, j, j + i));
            }
        }

        spectrum.push_back(vec_sum(elems, 0, elems.size() / 2));
        
        std::sort(spectrum.begin(), spectrum.end());

    }
    
    return spectrum;
}



int Score(std::string Peptide, std::vector<int> Spectr) {
    std::vector<int> PeptideSpectr = CycloSpectrum(Peptide);
    int score = 0;
    for (int i = 0; i < PeptideSpectr.size(); ++i) {
        auto it = std::find(Spectr.begin(), Spectr.end(), PeptideSpectr[i]);
        if (it != Spectr.end()) {
            score++;
            Spectr.erase(it);
        }
    }

    std::map<int, int> dict;


    return score;
}


int Expand(std::vector<CycloPeptide> &LeaderBoard, std::vector<int> &Masses, std::vector<int> &Spectr) {
    int size = LeaderBoard.size();
    std::vector<CycloPeptide> nLeaderBoard;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < Masses.size(); ++j) {
            CycloPeptide Peptide = LeaderBoard[i];
            int mass = Masses[j];

            std::string new_peptide = Peptide.GetPeptide().empty() ? std::to_string(mass) : (Peptide.GetPeptide() + "-" + std::to_string(mass));
            int new_mass = Peptide.GetMass() + mass;
            int new_score = Score(new_peptide, Spectr);

            nLeaderBoard.push_back(CycloPeptide(new_peptide, new_mass, new_score));
        }
    }
    LeaderBoard = nLeaderBoard;
    return 0;
}


int Cut(std::vector<CycloPeptide> &LeaderBoard, int N) {
    if (!LeaderBoard.empty()) {
        std::sort(LeaderBoard.begin(), LeaderBoard.end(), std::greater<CycloPeptide>());
        std::vector<CycloPeptide> nLeaderBoard;
        int n_max_score = LeaderBoard.back().GetScore();

        if (N < LeaderBoard.size())
            n_max_score = LeaderBoard[N].GetScore();

        for (int i = 0; i < LeaderBoard.size(); ++i) {
            CycloPeptide Peptide = LeaderBoard[i];
            if (Peptide.GetScore() >= n_max_score) {
                nLeaderBoard.push_back(Peptide);
            }
        }

        LeaderBoard = nLeaderBoard;
    }
    return 0;
}


std::string LeaderBoardCycloPeptideSequencing(std::vector<int> Spectr, int N, std::vector<int> &Masses) {
    std::vector<CycloPeptide> LeaderBoard = {CycloPeptide()};
    CycloPeptide LeaderPeptide;
    
    std::vector<CycloPeptide> LeaderPeptides;
    
    int ParentMass = Spectr[Spectr.size() - 1];
    std::cout << "ParentMass " << ParentMass << std::endl;
    while (!LeaderBoard.empty())
    {   
        
        Expand(LeaderBoard, Masses, Spectr);
        std::vector<CycloPeptide> nLeaderBoard;
        
        for (int i = 0; i < LeaderBoard.size(); ++i) {
           
            if (LeaderBoard[i].GetMass() == ParentMass) {
                
                if (LeaderBoard[i].GetScore() > LeaderPeptide.GetScore()) {
                    LeaderPeptide = LeaderBoard[i];
                }

                if (LeaderBoard[i].GetScore() >= LeaderPeptide.GetScore()) {
                    LeaderPeptides.push_back(LeaderBoard[i]);
                }
                    
                
                nLeaderBoard.push_back(LeaderBoard[i]);
            }
            else if (LeaderBoard[i].GetMass() < ParentMass)
                nLeaderBoard.push_back(LeaderBoard[i]);
        }
        
        Cut(nLeaderBoard, N);
        
        LeaderBoard = nLeaderBoard;
    }
    
    return LeaderPeptide.GetPeptide();
}


std::vector<int> conv(std::vector<int> &spectrum, int m) {
    spectrum.push_back(0);
    std::sort(spectrum.begin(), spectrum.end());

    std::map<int, int> new_spectrum = {};

    for (auto elem_i : spectrum) {
        for (auto elem_j : spectrum) {
            int diff = elem_j - elem_i;
            if (diff >= 57 && diff <= 200)
                new_spectrum[diff]++;
        }
    }

    std::vector<std::pair<int, int>> new_spectrum_vector;

    for (auto i = new_spectrum.begin(); i != new_spectrum.end(); i++) {
        new_spectrum_vector.push_back(std::make_pair(i->second, i->first));
    }

    std::sort(new_spectrum_vector.begin(), new_spectrum_vector.end(), std::greater<std::pair<int, int>>());

    int ties = new_spectrum_vector[m].first;

    std::vector<int> convolution;

    for (auto elem : new_spectrum_vector)
        if (elem.first >= ties)
            convolution.push_back(elem.second);

    std::sort(convolution.begin(), convolution.end());

    return convolution;
}


int main() {
    std::vector<int> mas = {57, 71, 87, 97, 99, 101, 103, 113, 114, 115, 128, 129, 131, 137, 147, 156, 163, 186};

    int m;
    std::cin >> m;

    int n;
    std::cin >> n;

    int x;
    std::vector<int> spectr;
    while(std::cin >> x) {
        spectr.push_back(x);
    }
    
    std::vector<int> new_mas = conv(spectr, m);

    std::cout << LeaderBoardCycloPeptideSequencing(spectr, n, new_mas) << std::endl;
    
    return 0;
}