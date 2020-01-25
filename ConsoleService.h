//
// Created by markel33 on 1/25/20.
//

#ifndef CSGOREC_CONSOLESERVICE_H
#define CSGOREC_CONSOLESERVICE_H


#include <X11/Xlib.h>

class ConsoleService {
public:
    ConsoleService();
    ConsoleService(const ConsoleService& orig);
    virtual ~ConsoleService();
    int openConsole();
    int closeConsole();
    int typeCommand(char *command);



private:
//    Display *display;
//    Window winRoot;
//    Window winFocus;
//    int    revert;

};


#endif //CSGOREC_CONSOLESERVICE_H
