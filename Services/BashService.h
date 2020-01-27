//
// Created by markel33 on 1/25/20.
//

#ifndef CSGOREC_BASHSERVICE_H
#define CSGOREC_BASHSERVICE_H



class BashService {
public:
    BashService();

    virtual ~BashService();


    void StartRecording();

    void StopRecording();

    void StartGame();

    void StopGame();
};


#endif //CSGOREC_BASHSERVICE_H
