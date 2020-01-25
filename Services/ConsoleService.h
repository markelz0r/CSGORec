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
    int typeCommand(std::string command);



private:
//    Display *display;
//    Window winRoot;
//    Window winFocus;
//    int    revert;

    void InstertCommandFromString(const char *command);

    XKeyEvent createKeyEvent(Display *display, Window &win, Window &winRoot, bool press, int keycode, int modifiers);

    void sendKeyPress(KeySym key);



    void InstertCommandFromString(std::string command);
};


#endif //CSGOREC_CONSOLESERVICE_H
