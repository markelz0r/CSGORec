#include <iostream>
#include "Services/ConsoleService.h"
#include "Services/BashService.h"
#include <unistd.h>
#include <thread>
#include <X11/keysym.h>
#include <stdlib.h>

void run(int duration, int start_tick);

int main(int argc, char* argv[]) {

//    if (argc < 3) {
//        std::cerr << "Usage: " << argv[0] << "--destination DESTINATION SOURCE" << std::endl;
//        return 1;
//    }

    int tickrate = strtol(argv[1], nullptr, 0);;
    int start_tick = strtol(argv[2], nullptr, 0);
    int final_tick = strtol(argv[3], nullptr, 0);

    //std::cin >> tickrate >> start_tick >> final_tick;

    int record_duration = (final_tick - start_tick) / tickrate;
    run(record_duration, start_tick);


    return 0;
}

void run(int duration, int start_tick) {
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

    std::string command = "demo_gototick ";
    command.append(std::to_string(start_tick));

    c->typeCommand(command);
    c->typeCommand("demo_resume");
    c->closeConsole();


    std::cout << "Starting Recording\n";
    std::cout << duration;

//    std::thread recording([b, duration]{
//
//    });
    b->StartRecording(duration);


    //std::cout << "Killing FFmpeg\n";
    //b->StopRecording();
}