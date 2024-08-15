#include <iostream> 
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <chrono>
#include <unordered_map>
#include <bitset>

#define WORDLEN 5
//std::cout << std::bitset<32>(c)<<std::endl;

uint32_t bin_rep(const std::string& word) {
    uint32_t temp = 0b00000000000000000000000000000000;

    for (size_t i = 0; i < word.size(); ++i) {
            switch (word[i]) {
                case 'e':
                    temp |= 0b00000000000000000000000000000001;
                    break;
                case 'a':
                    temp |= 0b00000000000000000000000000000010;
                    break;
                case 'r':
                    temp |= 0b00000000000000000000000000000100;
                    break;
                case 'i':
                    temp |= 0b00000010000000000000000000000000;
                    break;
                case 'o':
                    temp |= 0b00000000000000000000000000001000;
                    break;
                case 't':
                    temp |= 0b00000000000000000000000000010000;
                    break;
                case 'n':
                    temp |= 0b00000000000000000000000000100000;
                    break;
                case 's':
                    temp |= 0b00000000000000000000000001000000;
                    break;
                case 'l':
                    temp |= 0b00000000000000000000000010000000;
                    break;
                case 'c':
                    temp |= 0b00000000000000000000000100000000;
                    break;
                case 'u':
                    temp |= 0b00000000000000000000001000000000;
                    break;
                case 'd':
                    temp |= 0b00000000000000000000010000000000;
                    break;
                case 'p':
                    temp |= 0b00000000000000000000100000000000;
                    break;
                case 'm':
                    temp |= 0b00000000000000000001000000000000;
                    break;
                case 'h':
                    temp |= 0b00000000000000000010000000000000;
                    break;
                case 'g':
                    temp |= 0b00000000000000000100000000000000;
                    break;
                case 'b':
                    temp |= 0b00000000000000001000000000000000;
                    break;
                case 'f':
                    temp |= 0b00000000000000010000000000000000;
                    break;
                case 'y':
                    temp |= 0b00000000000000100000000000000000;
                    break;
                case 'w':
                    temp |= 0b00000000000001000000000000000000;
                    break;
                case 'k':
                    temp |= 0b00000000000010000000000000000000;
                    break;
                case 'v':
                    temp |= 0b00000000000100000000000000000000;
                    break;
                case 'x':
                    temp |= 0b00000000001000000000000000000000;
                    break;
                case 'z':
                    temp |= 0b00000000010000000000000000000000;
                    break;
                case 'j':
                    temp |= 0b00000000100000000000000000000000;
                    break;
                case 'q':
                    temp |= 0b00000001000000000000000000000000;
                    break;

                
            }
    }
    
    return temp;
}

unsigned int h_m(unsigned int x) {  
    return __builtin_popcount(x);  
} 

int main(){
    
    auto begin = std::chrono::high_resolution_clock::now();

    std::fstream words;
    //words.open("list.txt");
    words.open("words_beta_five.txt");

    std::vector<std::string> word_list;
    std::vector<std::string> temp_list;
    std::vector<std::string> result_list;
    std::string line;

    uint32_t big;
    uint32_t little;
    uint32_t temp;
    int word_count=0;

    //reading file and copying into the vector
    while(getline(words,line)){
        word_list.push_back(line);
    }
    words.close();


    //operation on vector itself
    for(auto& it: word_list){

        big = bin_rep(it);
        word_count = 0;

        for(int i =0; i< word_list.size(); i++){
            little = bin_rep(word_list[i]);
            temp = big | little;

            if(h_m(temp) == 5*(word_count+1)){
                big = temp;
                temp_list.push_back(word_list[i]);
                word_count++;
            }
        }
        temp_list.push_back(std::to_string(word_count));
        temp_list.push_back("");

        
        if(word_count<4){
            temp_list.clear();
        }
        else{
            for(int j=0; j<temp_list.size(); j++){
                result_list.push_back(temp_list[j]);
            }
            result_list.push_back("");
        }
    }

    //saving vector into the file
    std::ofstream result("results.txt");

    for(auto& it: result_list){
        //std::cout<<it<<std::endl;
        result<<it<<std::endl;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout<<"Czas wykonywania "<< elapsed.count()<<"µs"<<std::endl;
    return 0;
}