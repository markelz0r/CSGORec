//
// Created by markel33 on 1/25/20.
//

#ifndef CSGOREC_BASHSERVICE_H
#define CSGOREC_BASHSERVICE_H

#include <string>


class BashService {
public:
    BashService();

    virtual ~BashService();


    void StartRecording(int duration, int player_number);

    void StopRecording();

    void StartGame();

    void StopGame();

    std::string Execute(const char *cmd);

    std::string GetStdoutFromCommand(std::string cmd);

    void RemoveNewLine(std::string &s);

    std::string GenerateFFmpegCommand();

    std::string GenerateFFmpegCommand(int duration, int player_number);
};


#endif //CSGOREC_BASHSERVICE_H
