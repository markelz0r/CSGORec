//
// Created by markel33 on 1/28/20.
//

#include "GameService.h"
#include <iostream>
#include "ConsoleService.h"
#include "BashService.h"
#include <unistd.h>
#include <thread>
#include <X11/keysym.h>

GameService::GameService(int startTick, int duration, std::string demoPath) : start_tick(startTick), duration(duration), demo_path(demoPath) {

}

void GameService::initRecording() {
    for (int i = 0; i < 10 ; i++) {
        std::cout << "Startding recording for player " << i;
        recordPlayer(i);
    }

}

void GameService::recordPlayer(int player_number) {
    sleep(5);
    auto* c = new ConsoleService();
    auto* b = new BashService();


    std::thread game([b, this]{
        b->StartGame(demo_path);
    });

    std::cout << "Launching the game\n";
    sleep(60);
    std::cout << "Strating Demo\n";
    std::cout << "Selecting player\n";

    sleep(1);

    c->openConsole();
    std::string command = "demo_gototick ";
    command.append(std::to_string(start_tick));
    c->typeCommand(command);
    c->closeConsole();
    sleep(1);

    c->sendKeyPress(getKeySymForPlayerNumber(player_number));

    sleep(1);

    std::cout << "Configuring Demo\n";

    c->openConsole();
    c->typeCommand("demo_pause");
    std::string command1 = "demo_gototick ";
    command1.append(std::to_string(start_tick));
    c->typeCommand(command1);
    c->typeCommand("demo_resume");
    c->closeConsole();

    std::cout << "Start Recording\n";

    b->StartRecording(duration, player_number);

    game.join();

    b->StopGame();

}

KeySym GameService::getKeySymForPlayerNumber(int player_number) {
    switch (player_number) {
        case 0:
            return XK_0;
        case 1:
            return XK_1;
        case 2:
            return XK_2;
        case 3:
            return XK_3;
        case 4:
            return XK_4;
        case 5:
            return XK_5;
        case 6:
            return XK_6;
        case 7:
            return XK_7;
        case 8:
            return XK_8;
        case 9:
            return XK_9;
        default:
            return XK_0;

    }

}