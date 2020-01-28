#include <iostream>
#include "Services/GameService.h"
#include <stdlib.h>

int main(int argc, char* argv[]) {

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << "tickrate start_tick final_tick" << std::endl;
        return 1;
    }

    int tickrate = strtol(argv[1], nullptr, 0);;
    int start_tick = strtol(argv[2], nullptr, 0);
    int final_tick = strtol(argv[3], nullptr, 0);

    int record_duration = (final_tick - start_tick) / tickrate;
  //  run(record_duration, start_tick);

    auto* g = new GameService(start_tick, record_duration);
    g->initRecording();

    return 0;
}