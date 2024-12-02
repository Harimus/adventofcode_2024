#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
#include<cmath>

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



int main(int argc, char *argv[]){
  auto data= input_parser(argc, argv);
  std::sort(data.first.begin(), data.first.end());
  std::sort(data.second.begin(), data.second.end());
  int sum = 0;
  for(int i=0; i<data.first.size(); i++){
    sum += abs(data.first[i] - data.second[i]);

  }
  std::cout << sum << std::endl;


  return 0;
}

