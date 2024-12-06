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
    std::string text ="XMAS";
    std::vector<direction> check_dirs;
    direction front;
    direction diagonal_topfront;
    direction top;
    direction diagonal_topback;
    direction back;
    direction diagonal_downback;
    direction down;
    direction diagonal_downfront;
    for(int i=0; i<text.size(); i++){
        front.push_back(cidxpair(text[i], ipair(0, i)));
        diagonal_topfront.push_back(cidxpair(text[i], ipair(i, i)));
        top.push_back(cidxpair(text[i], ipair(i, 0)));
        diagonal_topback.push_back(cidxpair(text[i], ipair(i, -i)));
        back.push_back(cidxpair(text[i], ipair(0, -i)));
        diagonal_downback.push_back(cidxpair(text[i], ipair(-i, -i)));
        down.push_back(cidxpair(text[i], ipair(-i, 0)));
        diagonal_downfront.push_back(cidxpair(text[i], ipair(-i, i)));
    }
    check_dirs.push_back(front);
    check_dirs.push_back(diagonal_topfront);
    check_dirs.push_back(top);
    check_dirs.push_back(diagonal_topback);
    check_dirs.push_back(back);
    check_dirs.push_back(diagonal_downback);
    check_dirs.push_back(down);
    check_dirs.push_back(diagonal_downfront);
    auto bound = [&](int i, int j){
        if(i >= 0 && i < n && j >= 0 && j < m) return true;
        else return false;
    };
    auto check = [&](int i, int j){
        int total = 0;
        for(int x=0; x<check_dirs.size(); x++){
            bool match = true;
            for(int y=0; y<check_dirs[x].size(); y++){
                int a = check_dirs[x][y].second.first; 
                int b = check_dirs[x][y].second.second;
                if(bound(i+a, j+b)){
                    char c = data[i+a][j+b];
                    if(check_dirs[x][y].first == c){
                        //std::cout << "at " << i+a << ' ' << j+b << " char " << c << std::endl;
                        continue;
                    }
                    else{
                        match=false;
                        break;
                    }
                }
                else{
                    match=false;
                    break;
                }
            }
            if(match){
                std::cout <<"match at " << i << " "<< j << " for x " << x << std::endl;
                total++;
                }
        } 
        return total;
    };
    int sum = 0;
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(data[i][j]=='X'){
                sum += check(i, j);
            }
        }
    }
    std::cout << sum << std::endl;
}