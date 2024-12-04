#include "parser.h"
#include<iostream>

bool check_line(const std::vector<int> line){
    // Brute force. Check line first, if it works, fine.
    // If not, try remove each index (sequentially) and see if any of them works 
    std::vector<int> cidx;
    bool is_increasing = line[0] < line[1];
    auto cond = [&](int l, int r){
        int diff = r - l;
        if(is_increasing){
            if(diff < 1 || diff > 3) return false;
        }
        else{
            if(diff > -1 || diff < -3) return false;
        }
        return true; 
    };
    bool worked=true;
    for(int i=1; i<line.size(); i++){
        if(!cond(line[i-1], line[i])) worked=false;
    }
    if(worked) return true;
    for(int j=0; j<line.size(); j++){
        worked=true;
        std::vector<int> copy_line = line;
        copy_line.erase(copy_line.begin() + j);
        is_increasing = copy_line[0] < copy_line[1];
        for(int i=1; i<copy_line.size(); i++){
            if(!cond(copy_line[i-1], copy_line[i])) worked=false;
        }
        if(worked) return true;
    }
    return false;
}

int main(int argc, char **argv){
    if(argc < 2){
        std::cout << "Filename not speficied!" << std::endl;
        return -1;
    }
    std::vector<std::vector<int>> data = input_parser(argv[1]);
    int sum = 0;
    for(int i=0; i< data.size(); i++){
        bool correct = check_line(data[i]);
        if(correct){
            sum++;
        }
    }
    std::cout << "now with tolerance..." << std::endl;
    std::cout << sum << std::endl;
    return 0;
}