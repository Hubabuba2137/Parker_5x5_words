#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <map>
#include <bitset>

#define WORDLEN 5

//todo posortować litery z alfabetu w taki sposób aby te które pojawiają się najczęściej w języku polskim, były jak najwyżej
//std::cout << std::bitset<32>(c)<<std::endl;

uint32_t bin_rep(const std::string& word) {
    uint32_t temp = 0b00000000000000000000000000000000;

    for (size_t i = 0; i < word.length(); i++) {
        uint32_t mask = 0;
        switch (word[i]) {
                case 'e':
                    mask |= 0b00000000000000000000000000000001;
                    break;
                case 'a':
                    mask |= 0b00000000000000000000000000000010;
                    break;
                case 'r':
                    mask |= 0b00000000000000000000000000000100;
                    break;
                case 'i':
                    mask |= 0b00000010000000000000000000000000;
                    break;
                case 'o':
                    mask |= 0b00000000000000000000000000001000;
                    break;
                case 't':
                    mask |= 0b00000000000000000000000000010000;
                    break;
                case 'n':
                    mask |= 0b00000000000000000000000000100000;
                    break;
                case 's':
                    mask |= 0b00000000000000000000000001000000;
                    break;
                case 'l':
                    mask |= 0b00000000000000000000000010000000;
                    break;
                case 'c':
                    mask |= 0b00000000000000000000000100000000;
                    break;
                case 'u':
                    mask |= 0b00000000000000000000001000000000;
                    break;
                case 'd':
                    mask |= 0b00000000000000000000010000000000;
                    break;
                case 'p':
                    mask |= 0b00000000000000000000100000000000;
                    break;
                case 'm':
                    mask |= 0b00000000000000000001000000000000;
                    break;
                case 'h':
                    mask |= 0b00000000000000000010000000000000;
                    break;
                case 'g':
                    mask |= 0b00000000000000000100000000000000;
                    break;
                case 'b':
                    mask |= 0b00000000000000001000000000000000;
                    break;
                case 'f':
                    mask |= 0b00000000000000010000000000000000;
                    break;
                case 'y':
                    mask |= 0b00000000000000100000000000000000;
                    break;
                case 'w':
                    mask |= 0b00000000000001000000000000000000;
                    break;
                case 'k':
                    mask |= 0b00000000000010000000000000000000;
                    break;
                case 'v':
                    mask |= 0b00000000000100000000000000000000;
                    break;
                case 'x':
                    mask |= 0b00000000001000000000000000000000;
                    break;
                case 'z':
                    mask |= 0b00000000010000000000000000000000;
                    break;
                case 'j':
                    mask |= 0b00000000100000000000000000000000;
                    break;
                case 'q':
                    mask |= 0b00000001000000000000000000000000;
                    break;
        }

        if (temp & mask) {
            return 0;
        }

        temp |= mask;
    }

    return temp;
}

//Hamming weight
unsigned int h_m(unsigned int x) {  
    return __builtin_popcount(x);  
}

int main(){
    auto begin = std::chrono::high_resolution_clock::now();

    std::fstream plik;
    uint16_t word_list_size;

    plik.open("words_alpha.txt", std::ios::in);

    std::ofstream list("words_beta_five.txt");

    if (!list) {
        std::cerr << "Nie można otworzyć pliku do zapisu!" << std::endl;
        return 1;
    }

    std::string line;
    std::vector<std::string> word_list;

    uint32_t temp = 0b00000000000000000000000000000000;
    
    while(getline(plik, line)){
        temp = bin_rep(line);
        if(h_m(temp)==WORDLEN){
            list << line<< std::endl;
        }
    }

    plik.close();
    list.close();

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    std::cout<<"Czas działania "<< elapsed.count()<<"ms"<<std::endl; 
    return 0;
}