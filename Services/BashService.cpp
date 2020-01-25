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

BashService::BashService() {

}

void BashService::StartRecording() {
    system("ffmpeg -hide_banner -loglevel panic -video_size 1920x1080 -framerate 60 -f x11grab -i :0.0+0,0 -f pulse -i alsa_output.usb-Kingston_HyperX_Virtual_Surround_Sound_00000000-00.analog-stereo.monitor -c:v h264_nvenc -b:v 10M  /home/markel33/Videos/output.mp4");
}

void BashService::StopRecording() {
    system("killall -INT ffmpeg");
}

std::string BashService::Execute(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

BashService::~BashService() {

}
