#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <tuple>

using namespace std;

string XML = ""; //input file
typedef vector< tuple<string,int,string>> table;// tag, content, children

int findMaxOccur (table A, string b) {
    int max = 0;
    for (int i = 0; i < A.size(); i++) {
        if (get<0>(A[i]) == b) max = i;
    }
    return max;
}

void printTable (table A) {
    for (int i = 0; i < A.size(); i++) {
        cout << get<0>(A[i]) << " " << get<1>(A[i]) << " " << get<2>(A[i]) << endl;
    }
}

void printToFile (ofstream& f, table A) {
    for (int i = 0; i < A.size(); i++) {
        f << get<0>(A[i]) << " " << get<1>(A[i]) << " " << get<2>(A[i]) << endl;
    }
}

//assuming consistent xml
int symbols (ifstream& s) {
    int a = 0;
    char c;
    while((s.get(c), s.eof()) == false){
    if (c == '<') a++;
    }
    return a/2;
}

bool contains(string a, char k) {
    return a.find(k) != std::string::npos?true:false;
}

bool only_space(string a) {
    return (a.find_first_not_of(' ') != std::string::npos)?true:false;
}


void parsetheLINE(table &g, string line) {
    for (;;) {
        // write and remove
        if (contains(line,'<')) {
            int start,end;
            string tag;
            start = line.find_first_of("<");
            end = line.find_first_of(">");
            tag = line.substr(start+1,end-start-1); 

            if (!contains(tag,'/')) {
                g.push_back(make_tuple(tag,0,""));
            } else  {
                int o = findMaxOccur(g,tag.erase(0,1));
                if (o!=g.size()-1) get<1>(g.at(o)) = g.size() - 1 - o;
            } // add number of kids
            line.erase(start,end-start+1);
            end = line.find_first_of("<"); // temp reassign 
            start = line.find_first_not_of(' ');  //
                if (0 != end && only_space(line)) {
                    get<2>(g.back()) = line.substr(start,end);
                }
                line.erase(0,start);
            } else { 
                break;
            }
       }
}


int main (int argc, char *argv[]) { 
    if (argc<2) return 0;
    XML = argv[1];
    ifstream xml; 
    xml.open(XML);
    if (!xml) {
        cerr << "fail";
        exit(1); 
    }

    table IamaGraph;
    string line;


    while (getline(xml, line)) {
        parsetheLINE(IamaGraph,line); 
    }
    xml.close();

    printTable(IamaGraph);

    ofstream out;
    out.open (XML+".txt");
    printToFile(out,IamaGraph);
    out.close();

    return 0;
}
