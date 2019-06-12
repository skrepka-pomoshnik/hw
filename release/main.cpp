#include <unistd.h>
#include <output.cpp>
#include <species.cpp>
#include <input.cpp>

std::string INPUTSTRING,OUTPUTNAME = "mymelody",
    LILYPONDP = "/usr/bin/lilypond";
int TYPE = 1;

void usage() {
    std::cout << "Как использовать: -i \"мелодия\" -t 1 (тип контрапункта) -o имяфайла (по умолчанию mymelody)" << std::endl;
}

//VERSION 0.02

int main(int argc, char *argv[]){
    phrase Output, Input = {{2*Oct+C,_2},{2*Oct+F,_2},{2*Oct+D,_2},{2*Oct+F,_2},{2*Oct+E,_2},{2*Oct+C,_2}};
    if (argc < 2) { usage(); } else {
        int opt = 0;
        while ( (opt = getopt(argc,argv,"i:t:o:")) != -1){
            switch (opt){
                case 'i': INPUTSTRING = optarg; break;
                case 't': TYPE = std::atoi(optarg); break;
                case 'o': OUTPUTNAME = optarg; break;
            };
        };
    }

    if(TYPE < 0 && TYPE > 2) {std::cout << "Неправильный тип контрапункта (пока доступны 1 и 2)"; return 0; }
    if(checkstring(INPUTSTRING)) {
        Input = stringtophrase(INPUTSTRING);
    } else {
        std::cout << "Неправильный ввод! Мелодия длиннее 8 нот или неправильно составлена." << std::endl;
        return 0;
    }
    if (ispropercf(Input) != 0) std::cout << "Предупреждение: мелодия не кантус фирмус!" << std::endl;
    srand(time(NULL));

    solutiontree Stree{ std::pair<int,int>(0,0)}; 

    if (TYPE == 1) {
        FirstSpecie::GenerateTree(Stree,Input);
        std::cout << "Сгенерировано элементов:" << Stree.size() << std::endl;
        FirstSpecie::AssessPairs(Stree,Input);
        std::cout << "Оценено" << std::endl;
        FirstSpecie::FindBest(Stree,Stree.begin(),Output,Input);
        std::vector<phrase> Twovoices = {Input,Output};

        OutputtoLily(Twovoices,OUTPUTNAME);
        std::string command = "lilypond -s "+OUTPUTNAME+".ly";
        system(command.c_str()); 
        std::cout << "Результат:" << OUTPUTNAME << ".pdf" << std::endl;
    }
    if (TYPE == 2) {
        SecondSpecie::GenerateTree(Stree,Input);
        std::cout << "Сгенерировано элементов:" << Stree.size() << std::endl;
        SecondSpecie::AssessPairs(Stree,Input);
        std::cout << "Оценено" << std::endl;
        SecondSpecie::FindBest(Stree,Stree.begin(),Output,Input);
        std::vector<phrase> Twovoices = {Input,Output};

        OutputtoLily(Twovoices,OUTPUTNAME);
        std::string command = LILYPONDP+" -s "+OUTPUTNAME+".ly";
        system(command.c_str()); 
        std::cout << "Результат:" << OUTPUTNAME << ".pdf" << std::endl;
    }
    return 0;
}
