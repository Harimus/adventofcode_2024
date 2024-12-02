#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>


std::pair<std::vector<int>, std::vector<int>> input_parser(int argc, char *argv[]){
//Takes input text file, read it line by line and return

  if(argc < 2){
    std::cout << "no filename specified!" << std::endl;
  }
  std::ifstream file(argv[1]);
  std::pair<std::vector<int>, std::vector<int>> output;
  std::vector<int> left;
  std::vector<int> right;
  std::string str;
  while(std::getline(file, str)){
    std::stringstream linestream(str);
    int l, r;
    linestream >> l >> r;
    left.push_back(l);
    right.push_back(r);
  }
  output.first = right;
  output.second = left;
  return output;

}
