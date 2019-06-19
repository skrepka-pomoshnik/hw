#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include "constants.hh"

typedef std::vector<std::pair<int,int>> phrase;
const std::string nname[] = {"One","Two","Three","Four"};
const std::string version = "\\version \"2.18.2\"\n"; //stable
const std::string footer = R"(\score {
  <<
    \new StaffGroup  <<
      \new Staff <<
        \clef "treble_8"
        \context Voice  \voicea
        \context Voice \voiceb
      >>
      \new TabStaff = "guitar tab" <<
        \context TabVoice  \voicea
        \context TabVoice \voiceb
      >>
    >>
  >>
\layout {}
\midi {}
})";

char numc(int x) {return x+'a';}

std::string phrasetostring (std::vector<phrase> input) {
    std::string output = "";
    for (unsigned i = 0; i < input.size(); i++) {
        output+="voice";
        output+=numc(i);
        output+=" = {\n \\voice"+nname[i]+"\n";
        for (auto j: input[i]) {
            std::string octnum;
            if (j.first/12 == 0) octnum = ","; 
            if (j.first/12 == 2) octnum = "\'";
            if (j.first/12 == 3) octnum = "\'\'";
            if (j.first/12 == 4) octnum = "\'\'\'"; //ififif
            output+= numbertonotes[j.first % Oct];
            output+= octnum;
            output+=std::to_string(j.second)+" ";
        }
        output+= "}\n";
    }
    output += "\n";
    return output; 
}

void OutputtoLily (std::vector<phrase> input, std::string outputname) {
    std::ofstream file;
    file.open (outputname+".ly");
    file << version << phrasetostring(input) << footer;
    file.close();
}
