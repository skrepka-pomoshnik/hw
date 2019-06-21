#include "input.h"

void erasesubstr(std::string& str, const std::string& sub){
    size_t pos = str.find(sub);
    if (pos != std::string::npos) {
        str.erase(pos, sub.length());
    }
}

int extractesis(std::string & str) {
    if (str.find("is") != std::string::npos) {
        erasesubstr(str, "is");
        return 1;
    }
    if (str.find("es") != std::string::npos) {
        erasesubstr(str, "es");
        return -1;
    }
    return 0;
}

std::string extractnumber(std::string const & str) {
    std::size_t const n = str.find_first_of("0123456789");
    if (n != std::string::npos) {
        std::size_t const m = str.find_first_not_of("0123456789", n);
        return str.substr(n, m != std::string::npos ? m-n : m);
    }
    return "1";
}

void removess(std::string& s, const std::string &ss) {
    size_t pos = std::string::npos;
    while ((pos  = s.find(ss) )!= std::string::npos){
        s.erase(pos, ss.length());
    }
}

bool checkstring (std::string input) {
    if (input == "") return false;
    if (input.find_first_not_of(" abcdefghirs,'|~123456789") != std::string::npos) return false;
    int s = 0;
    while (input.size()!= 0) {
        int p;
        if (input.find_first_of(" ") != std::string::npos) {
            p = input.find_first_of(" ");
            s++;
        } else {
            p = input.length();
        }
        if (p > 7) return false;
        if ((input.substr(0,1)).find_first_not_of("abcdefghr") != std::string::npos) return false;
        input.erase(0,p+1);
        if (s > 8) return false;
    }
    return true;
}

std::vector<std::pair<int,int>> stringtophrase (std::string input) {
    std::vector<std::pair<int,int>> output;
    removess(input,"|");
    while (!input.empty()) {
        int f;
        if (input.find_first_of(" ") != std::string::npos) {
            f = input.find_first_of(" ");
        } else {
            f = input.length();
        }
        std::string note = input.substr(0,f);
        std::string value = note.substr(0,1);
        std::string time = extractnumber(note);
        int accidental = extractesis(note);
        erasesubstr(note,value);
        erasesubstr(note,time);
        input.erase(0,f+1);
        int noct = std::count(note.begin(),note.end(),',')*-1 + std::count(note.begin(),note.end(),'\'');
        output.push_back(std::make_pair(Oct*(1+noct)+notestonumber.at(value[0])+accidental,std::stoi(time)));
    }
    return output; 
}

int ispropercf (std::vector<std::pair<int,int>> input) {
    bool climax = false; 
    int lowest = input.front().first,highest = input.front().first, l = 0;
    for (int i = 0; i < input.size(); i++) {
        if (input[i].first < lowest) lowest = input[i].first;
        if (input[i].first > highest) {
            highest = input[i].first;
            climax = true;
        }
        if (input[i].first == highest) climax = false;
        //if (i>0 && !InSet(Cons,abs(input[i].first - input[i-1].first))) return 1; //consonanse
        if (i>0 && abs(Leap(i-1,i)) == 1) l++; 
        if (i>1 && Leap(input[i-2].first,input[i-1].first)*Leap(input[i-1].first,input[i].first) == 1) return 2; //two leaps
    }
    if ((input.front().first-input.back().first)%12 != 0) return 3; //tonic
    if (l > input.size()/2) return 4; //too many leaps
    if (climax) return 5; //range
    if ((highest-lowest) > 15) return 6; //range
    if (abs(input.at(input.size()-2).first - input.at(input.size()-2).first) > 2) return 7; //last step


    return 0;
}
