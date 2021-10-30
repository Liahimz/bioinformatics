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

        // print_vector(elems);
        // std::cout << elems.size() / 2 << std::endl;

        for (int i = 1; i < (elems.size() / 2); ++i) {
            for (int j = 0; j < (elems.size() / 2); ++j) {
                spectrum.push_back(vec_sum(elems, j, j + i));
            }
        }

        spectrum.push_back(vec_sum(elems, 0, elems.size() / 2));
        
        std::sort(spectrum.begin(), spectrum.end());

        spectrum.erase(std::unique( spectrum.begin(), spectrum.end() ), spectrum.end() );
    }
    
    return spectrum;
}




int Score(std::string Peptide, std::vector<int> Spectr) {
    std::vector<int> PeptideSpectr = CycloSpectrum(Peptide);

    int score = 0;
    for (int i = 0; i < PeptideSpectr.size(); ++i) {
        if (std::find(Spectr.begin(), Spectr.end(), PeptideSpectr[i]) != Spectr.end())
            score++;
    }

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


int main() {
    std::vector<int> mas = {57, 71, 87, 97, 99, 101, 103, 113, 114, 115, 128, 129, 131, 137, 147, 156, 163, 186};
    int n;
    std::cin >> n;

    int x;
    std::vector<int> spectr;
    std::vector<int> small_mas;
    while(std::cin >> x) {
        spectr.push_back(x);
        if (x > 0 && x < 186)
            small_mas.push_back(x);
    }
    

    std::cout << LeaderBoardCycloPeptideSequencing(spectr, n, mas) << std::endl;
    
    
    return 0;
}