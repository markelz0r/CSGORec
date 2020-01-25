//
// Created by markel33 on 1/25/20.
//

#ifndef CSGOREC_BASHSERVICE_H
#define CSGOREC_BASHSERVICE_H


#include <bits/basic_string.h>

class BashService {
public:
    BashService();

    virtual ~BashService();


    void StartRecording();

    void StopRecording();

    std::__cxx11::basic_string<char> Execute(const char *cmd);
};


#endif //CSGOREC_BASHSERVICE_H
