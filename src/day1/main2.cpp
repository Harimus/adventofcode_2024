#include<algorithm>
#include<string>
#include<cmath>
#include<unordered_map>

#include "parser.h"




int main(int argc, char *argv[]){
  auto data= input_parser(argc, argv);
  std::sort(data.first.begin(), data.first.end());
  std::sort(data.second.begin(), data.second.end());
  std::unordered_map<int, int> count_left;
  std::unordered_map<int, int> count_right;
  for(int i=0; i<data.first.size(); i++){
    int l = data.first[i];
    int r = data.second[i];
    if(count_left.find(l) != count_left.end()){
      count_left[l] += 1;
    }
    else{
      count_left[l] = 1;
    }
    if(count_right.find(r) != count_right.end()){
      count_right[r] += 1;
    }
    else{
      count_right[r] = 1;
    }
  }
  int sum = 0;
  for(auto& it : count_right){
    if(count_left.find(it.first) != count_left.end()){
      sum += it.first * count_left[it.first] * it.second;
    }
  }
  std::cout << sum << std::endl;


  return 0;
}

