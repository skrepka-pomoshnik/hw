#include "output.h"

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
