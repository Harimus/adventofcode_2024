#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<string>
#include<cmath>

#include "parser.h"

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

