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
  std::regex finddo("do\\(\\)");
  std::regex finddont("don\\'t\\(\\)");
  auto match_begin = std::sregex_iterator(str.begin(), str.end(), findmul);
  auto do_it = std::sregex_iterator(str.begin(), str.end(), finddo);
  auto dont_it = std::sregex_iterator(str.begin(), str.end(), finddont);
  auto match_end = std::sregex_iterator();
  int sum = 0;
  auto N = std::distance(match_begin, match_end);
  auto Ndo = std::distance(do_it, match_end);
  auto Ndont = std::distance(dont_it, match_end);
  
  int current_do_pos = 0;
  int current_dont_pos = dont_it->position(0);
  int incl = true; //switch between include and not include
  std::cout << "current do pos: " << current_do_pos << std::endl;
  std::cout << "current dont pos: " << current_dont_pos << std::endl;
  int iter = 0;
  for(std::sregex_iterator i = match_begin; i !=match_end; i++){
    std::smatch match = *i;
    int position = match.position(0);
    if(position > current_dont_pos){
        while(current_do_pos < current_dont_pos && do_it != match_end){
            do_it++;
            current_do_pos = do_it->position(0);
            std::cout << "current do pos: " << current_do_pos << " dont: " << current_dont_pos << std::endl;
        }
    }
    if(position > current_do_pos){
        while(current_dont_pos <= current_do_pos && dont_it != match_end){
            dont_it++;
            current_dont_pos = dont_it->position(0);
            std::cout << "current dont pos: " << current_dont_pos << std::endl;
        }
    }
    if(position > current_do_pos && position < current_dont_pos){
        std::string mulstr = match.str();
        std::cout << "found: " << mulstr << " at pos:" << match.position(0) << std::endl;
        auto pairs = split_mulstring(mulstr);
        sum += pairs.first * pairs.second;
    }
  }
  std::cout << "found matches: " <<  N << std::endl;
  std::cout << "found dos: " << Ndo << std::endl;
  std::cout << "found donts: " << Ndont << std::endl;
  std::cout << std::endl  << sum << std::endl;
  return sum;
}