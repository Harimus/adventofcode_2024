#include "parser.h"
#include<iostream>

/// 3 1 5 6 7
/// 5 1 7 8 9<- remove 1 and we good
/// 1 5 7 8 9<- remove first index and we good
/// 1 5 3 6 7<- remove 5 works but not 1
/// 1 5 4 3 1<- remove both 5 AND 1 works....
/// my solution only checks for second param and forward

bool check_line2(const std::vector<int> line){
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

inline bool check_line(const std::vector<int> &line){
    //essentially  moving window of size 2 but now with one tolerance
    bool tolerance_used = false;
    bool is_increasing = line[0] < line[1];
    auto cond1 = [&](int l, int r){
        bool increasing = line[l] < line[r];
        if(increasing != is_increasing){
            return false;
        }
        return true;
    };
    auto cond2 = [&](int l, int r){
        int diff = abs(line[r] - line[l]);
        if(diff < 1 || diff > 3){
            return false;
        }
        return true; 
    };
    // window
    int l = 0;
    int m = 1;
    int r = 2;
    while(r<line.size()){
        if(cond1(l, m) && cond1(m, r) && cond2(l,m) && cond2(m, r)){
            r++;
            m = r-1;
            l = r-2;
            is_increasing = line[l] < line[m];
            continue;
        }
        else{
            if(tolerance_used) return false;
            tolerance_used = true;
            if(cond2(l, r) && (cond1(l, r) || l==0)){ // we skip m
                r++;
                m = r-1;
                is_increasing = line[l] < line[m];
            }
            else{
                return false;
            }
            
        }
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
        bool correct = check_line2(data[i]);
        if(correct){
            sum++;
        }
        else{
            std::cout << "Incorrect: ";
            for(int j=0; j<data[i].size(); j++){
                std::cout << data[i][j] << " ";
            } 
            std::cout << std::endl;
        }
    }
    std::cout << "now with tolerance..." << std::endl;
    std::cout << sum << std::endl;
    return 0;
}