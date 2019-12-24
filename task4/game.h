#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <stdexcept>

class Upgrade {
    public:
        Upgrade(int a) try: uplvl(0) {
            a>0?maxlvl=a:maxlvl=0;
        }
        catch (const std::invalid_argument er) {
        std::cout << "E: wrong lvl exception" << er.what();
        }
        int uplvl;
        int maxlvl;
        void up () {
            if (maxlvl > uplvl) uplvl++;
        }
        bool isup() {
            return (uplvl == 1)?true:false;
        }
};

class Worker {
    public:
        Worker(): num(0){} //can't fail
        int num;
};

class Upworker : public Worker, public Upgrade {
    public:
        Upworker(): Worker(),Upgrade(10){} //cant fail
        int eff = (int) feff;
    private:
        float feff = 1 + uplvl * 0.1;
};


class State {
    public:
        int numofpub;
        float hind,hrate;
        std::string log;

        State(): hind(0),numofpub(0),hrate(0.001),log(""){}

        void pplus() {
            numofpub++;
        }

        void sclog () { // clear log
            std::cout << log;
            log = "";
        }

        void showpublic () {
            std::cout << "Your published " << numofpub << " articles. Your h-index is " << hind;
        }
};


//RANDOM (enum?)
const int RHIRSH = 5;
const int RPOSTDOC = 10;
const int RPOSTSEARCH = 10;
const int RSTUDENT = 20;
const int RLECTURE = 10;
const int RDOUBLE = 15;


class World { //here come the light
    public:
        World(State a, Worker b, Upworker c, Upgrade d, Upgrade e)try : state(a),workers{b},upworkers{c},upgrades{d,e} {}
        catch (const std::invalid_argument er) {
        std::cout << "E: world initiation exception" << er.what();
        }
        State state;
        Worker workers[1];
        Upworker upworkers[1];
        Upgrade upgrades[2];
        //tick
        void changestate () {
            if (3 == rand()%RHIRSH) { state.hind += state.hrate*state.numofpub;
                state.log += "someone has copy-pasted your article. your hirsh increased \n";
            }
            if (3 == rand()%RPOSTDOC && workers[0].num != 0) { 
                state.numofpub += workers[0].num;
                state.log += "one of postdocs publsihed something for you \n";
            } 
            if (3 == rand()%RSTUDENT && workers[0].num != 0) { 
                state.numofpub += upworkers[0].num*upworkers[0].eff;
                state.log += "one of students publsihed something for you \n";
            }

        }
};

class Menuitem {
    public:
        void(*action)(World&);
        Menuitem(char a, std::string s, void(*c)(World&)) 
            try: letter(a), desc(s) { 
                action = c; 
                avail = true;
            } catch (std::invalid_argument er) {
                std::cout << "E: menu init error " << er.what();
        };
        Menuitem(char a, std::string s, bool t, void(*c)(World&))
            try: letter(a), desc(s) { 
            action = c; 
            avail = t;
            } catch (std::invalid_argument er) {
                std::cout << "E: No action for the menu point" << er.what();
        };
        char letter;
        bool avail; 
        std::string desc;
        
};

void ListMenu(Menuitem a[], int n) {
    for (int i = 0; i < n; i++) {
        if (a[i].avail)
            std::cout << "[" << a[i].letter << "]" << a[i].desc << std::endl;
    }
}

void ChangeMenuState(Menuitem a[], int n, World &w) { //literally useless function
    for (int i = 0; i < n; i++) {
        if (!a[i].avail) {
            if (w.upgrades[0].isup()) a[i].avail = true;
        }
    }
}

//supplementary functions

void waitfor(char c) {
    while (char in = std::cin.get()) {
        if (in == c) break;
    }
}

void cls() {
    for (int n = 0; n < 5; n++)
        printf( "\n\n\n\n\n\n\n\n\n\n" );
}

void slp (int x) {
    std::this_thread::sleep_for(std::chrono::seconds(x));
}

void cycles (std::string a[], int n) {
    for (int i = 0; i < n; i++) {
        if (rand() % n == 1) { 
            std::cout << a[i] << std::endl;
            break;
        }
        i = 0;
    }
}

//graphics
const std::string computer= R"(
                  .----.
      .---------. | == |
      |.-"""""-.| |----|
      ||       || | == |
      ||       || |----|
      |'-.....-'| |::::|
      `"")---(""` |___.|
     /:::::::::::\" _  "
    /:::=======:::\`\`\
    `"""""""""""""`  '-'
)";


const std::string cathedral = R"(
 _____________________________________________
|.'.'',                                 ,''.'.|
|.'.'.'',                             ,''.'.'.|
|.'.'.'.'',                         ,''.'.'.'.|
|.'.'.'.'.|                         |.'.'.'.'.|
|.'.'.'.'.|===;                 ;===|.'.'.'.'.|
|.'.'.'.'.|:::|',             ,'|:::|.'.'.'.'.|
|.'.'.'.'.|---|'.|, _______ ,|.'|---|.'.'.'.'.|
|.'.'.'.'.|:::|'.|'|???????|'|.'|:::|.'.'.'.'.|
|,',',',',|---|',|'|???????|'|,'|---|,',',',',|
|.'.'.'.'.|:::|'.|'|???????|'|.'|:::|.'.'.'.'.|
|.'.'.'.'.|---|','   /%%%\   ','|---|.'.'.'.'.|
|.'.'.'.'.|===:'    /%%%%%\    ':===|.'.'.'.'.|
|.'.'.'.'.|%%%%%%%%%%%%%%%%%%%%%%%%%|.'.'.'.'.|
|.'.'.'.','       /%%%%%%%%%\       ','.'.'.'.|
|.'.'.','        /%%%%%%%%%%%\        ','.'.'.|
|.'.','         /%%%%%%%%%%%%%\         ','.'.|
|.','          /%%%%%%%%%%%%%%%\          ','.|
|;____________/%%%%%%%%%%%%%%%%%\____________;|
)";

const std::string hello = R"(
                             Z             
                       Z                   
        .,.,        z           
      (((((())    z             
     ((('_  _`) '               
     ((G   \ |)                 
    (((`   " ,                  
     .((\.:~:          .--------------.    
     __.| `"'.__      | \              |     
  .~~   `---'   ~.    |  .             :     
 /                `   |   `-.__________)     
|     ~       ~       |  :             :   
|                     |  :  |              
|    _                |     |   [ ##   :   
 \    ~~-.            |  ,   oo_______.'   
  `_   ( \) _____/~~~~ `--___              
  | ~`-)  ) `-.   `---   ( - -----         
  |   '///`  | `-.                         
  |     | |  |    `-.                      
  |     | |  |       `-.                   
  |     | |\ |                             
  |     | | \|                             
   `-.  | |  |                             
      `-| '
)";

//events
void writeapub (World &w) {
    char in;
    std::string title = "";
    cls();
    std::cout << computer;
    std::cin.get();
    std::cout << "Write a title:";
    while (in = std::cin.get()) {
        if (in == '\n') break;
        title += in;
    }
    std::cout << "Write a content:";
    waitfor('\n');
    w.state.pplus();
    if (w.upgrades[1].isup()) w.state.pplus();
    cls();
    std::cout << "Your article " << title << " is published!";
    if (w.upgrades[1].isup()) 
    std::cout << "You published another one just changing the key words.";
}

//event
void searchforA(World &w) {
    cls();
    std::cout << cathedral;
    std::cout << "You decide to take a walk to the department, go to the (l)eft or the (r)ight?" << std::endl;
    while (char in = std::cin.get()) {
        if (in == 'l') { 
            cls();
            std::cout << "You take the left passage" << std::endl;
            std::string reply[3] = {"Everybody is hiding.", "Someone ran away", "You see nobody"};
            cycles(reply,3);
        }
        if (in == 'r') {
            cls();
            std::cout << "You take the right passage" << std::endl;
            std::string reply[3] = {"Everybody is hiding.", "Someone ran away", "You see nobody"};
            cycles(reply,3);
        }
        if (3 == rand()%(RPOSTSEARCH+5*w.workers[0].num)) { 
            w.workers[0].num++;
            cls();
            std::cout << "You found an postgraduate to write an article for you.";
            break;}

        if (in == 'q') std::cout << "You decided to give up";
    }
}

//event
void searchforS (World &w) {
    cls();
    std::cout << "You decided to find some graduates and teach them something" << std::endl; 
    waitfor('\n');
    std::string reply[3] = {"You read a lecture. Some students seems interested.","You tell a good old joke. Some students are interested.","You ask for help. Nobody is interested, but you use your power.",};
    cycles(reply,3);
    w.upworkers[0].num++;
    w.upworkers[0].up();
}

void golibrary (World &w) {
    waitfor('\n');
    std::cout << "You decided to visit library" << std::endl;
    std::cout << "You can try to [r]ead some book or silently [q]uit." << std::endl;
    while (char in = std::cin.get()) {
        if (in == 'r') {
            if (5 == rand()%RLECTURE){
                cls();
                std::cout << "You know a little more know, you can use that in your lecture" << std::endl;
                w.upworkers[0].up();
                w.upgrades[0].up();
                waitfor('\n');
                break;
            } else if (5 == rand()%RDOUBLE && !w.upgrades[1].isup()){
                cls();
                std::cout << "You found up that your theory is similar to the theory from another field. You can can write two articles simultaneously" << std::endl;
                w.upgrades[1].up();
                waitfor('\n');
                break;
            } else{
                cls();
                std::string reply[3] = {"You accidentally read some fiction.","You read a biography of famous scientist","You can't decide what to read."};
                cycles(reply,3);
            }
        }
        if (in == 'q') break;}
}

//event
void showStat(World& w) {
    w.state.showpublic();
    if (w.upworkers[0].num != 0)
        std::cout << std::endl << "Your number of students is: " << w.upworkers[0].num;
    if (w.workers[0].num != 0)
        std::cout << std::endl << "Your number of postdocs is: " << w.workers[0].num;
    std::cout << std::endl;
    waitfor('\n');
}
