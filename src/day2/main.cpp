#include "parser.h"
#include<iostream>


inline bool check_line(std::vector<int> line){
    //essentially  moving window of size 2
    int prev = line[0];
    bool increasing = line[1] > prev;
    for(int i=1; i<line.size(); i++){
        // Condition 1 The level is either all increasing or decreasing 
        bool is_increasing = line[i] > prev;
        if(increasing != is_increasing) return false;
        // Condition 2 The two adjecent levels differ by 1 <=  diff <= 3
        int diff = abs(line[i] - prev);
        if( diff < 1  || diff > 3) return false;
        prev = line[i];
    }
    return true;
}

int main(int argc, char **argv){
    if(argc < 2){
        std::cout << "Filename not speficied!" << std::endl;
        return -1;
    }
    std::vector<std::vector<int>> data = input_parser(argv[1]);
    int sum = 0;
    for(int i=0; i< data.size(); i++){
        if(check_line(data[i])) sum++;
    }
    std::cout << sum << std::endl;
    return 0;
}