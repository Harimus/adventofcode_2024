#include<fstream>
#include<sstream>
#include<vector>
#include<string>

std::vector<std::vector<int>> input_parser(char *file_name){
    std::vector<std::vector<int>> output;
    std::fstream file(file_name);
    std::string line;
    while(std::getline(file, line)){
        std::stringstream ss(line);
        int n;
        std::vector<int> row;
        while(ss >> n){
            row.push_back(n);
        }
        output.push_back(row);
    }
    return output;
}