//
// Created by markel33 on 1/25/20.
//

#include <cstdlib>
#include "BashService.h"
#include <string>
#include <unistd.h>
#include <cstdio>
#include <iostream>

BashService::BashService() {

}

void BashService::StartRecording(int duration, int player_number) {

   std::string cmd = GenerateFFmpegCommand(duration, player_number);
   system(cmd.c_str());
}

void BashService::StopRecording() {
    system("killall -INT ffmpeg");
}

void BashService::StartGame() {
    system("steam -applaunch 730 -fullscreen");
}

void BashService::StopGame() {
    system("killall csgo_linux64");
}

std::string BashService::GetStdoutFromCommand(std::string cmd) {

    std::string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");
    if (stream) {
        while (!feof(stream))
            if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
        pclose(stream);
    }
    RemoveNewLine(data);
    return data;
}

void BashService::RemoveNewLine(std::string &s)
{
    int pos;
    if((pos=s.find('\n')) != std::string::npos)
        s.erase(pos);
}


std::string BashService::GenerateFFmpegCommand(int duration, int player_number) {
    std::string default_monitor_cmd= "pacmd info | grep -e \"Default sink name\" | gawk -F\"name: \" '/name/{print $2}'";
    std::string default_monitor = GetStdoutFromCommand(default_monitor_cmd).append(".monitor");

    std::cout << "Default sound device - " << default_monitor;

    //std::string init = "ffmpeg -y -hide_banner -loglevel panic -video_size 1920x1080 -framerate 60 -f x11grab -t ";
    std::string init = "ffmpeg -y -video_size 1920x1080 -framerate 60 -f x11grab -t ";
    std::string cmd = init.append(std::to_string(duration))
            .append(" -i :1 -f pulse -t ")
            .append(std::to_string(duration))
            .append(" -i ")
            .append(default_monitor)
            .append(" -c:v h264_nvenc -b:v 10M  ~/Videos/demo_player")
            .append(std::to_string(player_number))
            .append(".mp4");

    return cmd;
}



BashService::~BashService() {

}
