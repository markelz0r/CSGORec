#include <iostream>
#include "Services/ConsoleService.h"
#include "Services/BashService.h"
#include <unistd.h>
#include <thread>
#include <X11/keysym.h>

int main() {

    sleep(5);
    auto* c = new ConsoleService();
    auto* b = new BashService();

    std::thread game([b]{
        b->StartGame();
    });


    std::cout << "Launching the game\n";

    sleep(60);

    std::cout << "Strating Demo\n";

    c->openConsole();
    c->typeCommand("playdemo demo.dem");
    c->closeConsole();

    sleep(30);



    std::cout << "Selecting player\n";
    c->sendKeyPress(XK_2);

    sleep(1);

    std::cout << "Configuring Demo\n";

    c->openConsole();
    c->typeCommand("demo_pause");
    c->typeCommand("demo_gototick 0");
    c->typeCommand("demo_resume");
    c->closeConsole();





    std::cout << "Starting Recording\n";

    std::thread recording([b]{
        b->StartRecording();
    });

    sleep(60*15);

    std::cout << "Killing FFmpeg\n";
    b->StopRecording();

    return 0;

}
