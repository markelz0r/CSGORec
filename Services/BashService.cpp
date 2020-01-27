//
// Created by markel33 on 1/25/20.
//

#include <cstdlib>
#include "BashService.h"
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <cstring>

BashService::BashService() {

}

void BashService::StartRecording(int duration) {

    std::string part1 = "ffmpeg -y -hide_banner -loglevel panic -video_size 1920x1080 -framerate 60 -f x11grab -t ";
    std::string part2 = part1.append(std::to_string(duration));
    std::string part3 = part2.append(" -i :1 -f pulse -t ");
    std::string part4 = part3.append(std::to_string(duration));
    std::string part5 = part4.append(" -i alsa_output.usb-Kingston_HyperX_Virtual_Surround_Sound_00000000-00.analog-stereo.monitor -c:v h264_nvenc -b:v 10M  /home/markel33/Videos/output.mp4");

    system(part5.c_str());
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

//std::string BashService::Execute(const char* cmd) {
//    std::array<char, 128> buffer;
//    std::string result;
//    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
//    if (!pipe) {
//        throw std::runtime_error("popen() failed!");
//    }
//    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
//        result += buffer.data();
//    }
//    return result;
//}

BashService::~BashService() {

}
