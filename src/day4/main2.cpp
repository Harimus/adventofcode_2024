#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>

typedef std::pair<int, int> ipair;
typedef std::pair<char, ipair> cidxpair; 
typedef std::vector<cidxpair> direction;

std::vector<std::vector<char>> input_parser(const char *fn){
  std::ifstream file(fn);
  std::string s;
  std::vector<std::vector<char>> data;
  while(std::getline(file, s)){
    std::vector<char> line;
    line.reserve(s.size());
    for(int i=0; i<s.size(); i++){
        line.push_back(s[i]);
    }
    data.push_back(line);
  }
  return data;
}



int main(int argc, const char **argv){
    const char *fn;
    std::string fns ="./data/input4.txt";
    if(argc < 2){
    std::cout << "no filename specified!" << std::endl;
    fn = fns.c_str();
    }
    else{
        fn = argv[1];
    }
    auto data = input_parser(fn);
    int n = data.size();
    int m = data[0].size();
    std::string text ="MAS";
    std::vector<std::pair<direction, direction>> check_dirs;
    direction diagonal_front;
    direction diagonal_front_reverse;
    direction diagonal_back;
    direction diagonal_back_reverse;
    int ts = text.size();
    for(int i=0; i<ts; i++){
        diagonal_front.push_back(cidxpair(text[i], ipair(i-(ts/2), i-(ts/2))));
        diagonal_front_reverse.push_back(cidxpair(text[ts-1-i], ipair(i-(ts/2), i-(ts/2))));
        diagonal_back.push_back(cidxpair(text[i], ipair(i-(ts/2), -i+(ts/2))));
        diagonal_back_reverse.push_back(cidxpair(text[ts-1-i], ipair(i-(ts/2), -i+(ts/2))));
    }
    check_dirs.push_back(std::pair<direction, direction>(diagonal_front, diagonal_front_reverse));
    check_dirs.push_back(std::pair<direction, direction>(diagonal_back, diagonal_back_reverse));
    //for(int i=0; i < check_dirs.size(); i++){
    //    std::cout << "checkdirs i=" << i << std::endl;
    //    for(int j=0; j< check_dirs[i].size(); j++){
    //        std::cout << "char="<<check_dirs[i][j].first;
    //        std::cout<<" idx: " << check_dirs[i][j].second.first << " " << check_dirs[i][j].second.second << std::endl;
    //    }
    //}
    //return 0;
    auto bound = [&](int i, int j){
        if(i >= 0 && i < n && j >= 0 && j < m) return true;
        else return false;
    };
    auto check_one = [&](int i, int j, direction d){
        bool ret = true;
        for(int x=0; x<d.size(); x++){
            int a = d[x].second.first;
            int b = d[x].second.second;
            char c = d[x].first;
            if(bound(i+a, j+b)){
                if(c == data[i+a][j+b]){
                    //std::cout << "at " << i+a << ' ' << j+b << " char " << c << std::endl;
                    continue;
                }
                else{
                    ret=false;
                    break;
                }
            }
            else{
                ret=false;
                break;
            }
        }
        return ret;
    };
    auto check = [&](int i, int j){
        int total = 0;
        // Diagonal front
        bool df = check_one(i, j, diagonal_front) || check_one(i, j, diagonal_front_reverse);
        // Diagonal back
        bool db = check_one(i, j, diagonal_back) || check_one(i, j, diagonal_back_reverse);
        if(df && db) total = 1;
        if(total){
            std::cout << "match at: " << i <<  " " << j << " " << std::endl;
        }
        return total;
    };
    int sum = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(data[i][j]=='A'){
                sum += check(i, j);
            }
        }
    }
    std::cout << sum << std::endl;
}