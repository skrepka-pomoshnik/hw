#include "game.h"
#include <cassert>

void Upgrade_Tests() {
    Upgrade U1 (0);
    assert (U1.maxlvl==0);
    Upgrade U2 (-1);
    assert (!(U2.maxlvl==-1));
    U1.up(); 
    U1.up(); 
    assert (U1.maxlvl==0);
}

void State_Tests() {
    State S1;
    S1.pplus();
    assert (S1.numofpub==1);
    S1.log = "test";
    S1.sclog();
    assert (S1.log == "");
}

void World_Tests() {
srand(time(NULL));
    Upworker Student;
    Worker Aspirant;
    State s;
    Upgrade Lecture(1);
    Upgrade Double(1);
    World w = World (s, Aspirant, Student, Lecture,Double);
    w.changestate();
    assert (!(w.state.log == ""));

}

void Menuitem_Tests() {
    Upworker Student;
    Worker Aspirant;
    State s;
    Upgrade Lecture(1);
    Upgrade Double(1);
    World w = World (s, Aspirant, Student, Lecture,Double);
    std::thread([&]
            {
            while(true)
            {
            slp(1);
            w.changestate();
            }
            }).detach();

    std::string a = "";
    Menuitem M1 = Menuitem('a',a, false, &writeapub);
}

int main () {
    Upgrade_Tests();
    State_Tests();
     World_Tests();
    Menuitem_Tests(); 
    
    return 0;
}
