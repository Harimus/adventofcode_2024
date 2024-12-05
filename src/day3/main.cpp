#include<string>
#include<regex>
#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<iterator>

std::pair<int, int> split_mulstring(std::string str){
    std::stringstream ss(str);
    std::string s;
    std::getline(ss, s, '(');
    std::getline(ss, s, ')');
    std::stringstream ss2(s);
    std::getline(ss2, s, ',');
    int first = std::stoi(s);
    std::getline(ss2, s, ',');
    int second = std::stoi(s);
    std::pair<int, int> p(first, second);
    return p;
}


int main(int argc, char **argv){
  if(argc < 2){
    std::cout << "no filename specified!" << std::endl;
  }
  std::ifstream file(argv[1]);
  std::string str;
  std::string s;
  while(std::getline(file, s)){
    str += s;
  }
  std::regex findmul("mul\\((\\d{1,3},\\d{1,3})\\)");
  auto match_begin = std::sregex_iterator(str.begin(), str.end(), findmul);
  auto match_end = std::sregex_iterator();
  int sum = 0;
  auto N = std::distance(match_begin, match_end);
  std::cout << "found matches: " << std::distance(match_begin, match_end);
  for(std::sregex_iterator i = match_begin; i!=match_end; i++){
    std::smatch match = *i;
    std::string mulstr = match.str();
    std::cout << "found: " << mulstr << std::endl;
    auto pairs = split_mulstring(mulstr);
    sum += pairs.first * pairs.second;
  }
  std::cout << sum << std::endl;
  return sum;
}