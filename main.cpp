#include <iostream>
#include "Services/ConsoleService.h"
#include "Services/BashService.h"
#include <unistd.h>
#include <thread>


int main() {
    sleep(5);
    auto* c = new ConsoleService();
    auto* b = new BashService();


    c->openConsole();
    c->typeCommand("playdemo demo.dem");
    c->closeConsole();

    std::cout << "Strating Demo\n";

    sleep(30);


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

    sleep(60);

    std::cout << "Killing FFmpeg\n";
    b->StopRecording();

}
