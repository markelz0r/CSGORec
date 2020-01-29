//
// Created by markel33 on 1/28/20.
//

#ifndef CSGOREC_GAMESERVICE_H
#define CSGOREC_GAMESERVICE_H

#include <iostream>
#include <X11/X.h>

class GameService {
public:
    GameService(int startTick, int duration, std::string demoPath);
    void initRecording();

private:
    int start_tick;
    int duration;
    std::string demo_path;

    void recordPlayer(int player_number);


    KeySym getKeySymForPlayerNumber(int player_number);
};


#endif //CSGOREC_GAMESERVICE_H
