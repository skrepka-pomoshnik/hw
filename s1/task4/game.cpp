#include "game.h"

int main () {
    //create world
    srand(time(NULL));
    Upworker Student;
    Worker Aspirant;
    State s;
    Upgrade Lecture(1);
    Upgrade Double(1);
    World w = World (s, Aspirant, Student, Lecture,Double);

    //    menu declaration
    const int items = 5;
    Menuitem Mw = Menuitem('w',"write a new publication",&writeapub);
    Menuitem Ms = Menuitem('s',"show stats",&showStat);
    Menuitem Mg = Menuitem('g',"search for student",false,&searchforS);
    Menuitem Ma = Menuitem('a',"search for aspirant",&searchforA);
    Menuitem Ml = Menuitem('l',"go the library",&golibrary);
    Menuitem MenuA[items] = {Mw, Ms, Mg, Ma, Ml};

    //start the world
    std::thread([&]
            {
            while(true)
            {
            slp(1);
            w.changestate();
            ChangeMenuState(MenuA,items,w);
            }
            }).detach();

    std::cout << "Welcome to the lazy doc simulator. Press [q] to exit. Press [enter] to continue";

    //menu cycle
    while (char in = std::cin.get()) {
        cls();
        std::cout << "Good morning, doc" << hello;
        ListMenu(MenuA,items);
        w.state.sclog();
        for (const auto i : MenuA) 
            if (in == i.letter && i.avail) i.action(w); 
        if (in == 'q') break;
    }

    std::cout << "Bye then" << std::endl;
    return 0;
}
