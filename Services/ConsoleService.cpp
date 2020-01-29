//
// Created by markel33 on 1/25/20.
//

#include <iostream>
#include "ConsoleService.h"
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <unistd.h>

#define INSERT_KEY XK_Insert
#define ESC_KEY XK_Escape
#define PERIOD XK_period
#define SPACE XK_space
#define ENTER XK_Return
#define MINUS_KEY XK_minus
#define UNDERSCORE_KEY XK_underscore

using namespace std;
ConsoleService::ConsoleService() = default;

XKeyEvent ConsoleService::createKeyEvent(Display *display, Window &win,
                         Window &winRoot, bool press,
                         int keycode, int modifiers)
{
    XKeyEvent event;

    event.display     = display;
    event.window      = win;
    event.root        = winRoot;
    event.subwindow   = None;
    event.time        = CurrentTime;
    event.x           = 1;
    event.y           = 1;
    event.x_root      = 1;
    event.y_root      = 1;
    event.same_screen = True;
    event.keycode     = XKeysymToKeycode(display, keycode);
    event.state       = modifiers;

    if(press)
        event.type = KeyPress;
    else
        event.type = KeyRelease;

    return event;
}

int ConsoleService::openConsole() {
    sendKeyPress(INSERT_KEY);
    return 0;
}

int ConsoleService::typeCommand(string command) {
    sleep(1);
    InstertCommandFromString(command);
    sendKeyPress(ENTER);
    return 0;
}

void ConsoleService::sendKeyPress(KeySym key) {
    Display *display = XOpenDisplay(nullptr);
    Window winRoot = XDefaultRootWindow(display);
    Window winFocus;
    int    revert;
    XGetInputFocus(display, &winFocus, &revert);


    XKeyEvent event = createKeyEvent(display, winFocus, winRoot, true, key, 0);
    XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

    event = createKeyEvent(display, winFocus, winRoot, false, key, 0);
    XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

    XCloseDisplay(display);
}

void ConsoleService::InstertCommandFromString(string command) {

    Display *display = XOpenDisplay(nullptr);
    Window winRoot = XDefaultRootWindow(display);
    Window winFocus;
    int    revert;
    XGetInputFocus(display, &winFocus, &revert);

    for (int i = 0; i < command.length(); i++){
        string str = "volume 0.6";
        string sym(1, command[i]);

        KeySym com = XStringToKeysym(sym.c_str());
        int modifier = 0;

        if (sym == ".")
            com = PERIOD;

        if (sym == " ")
            com = SPACE;

        if (sym == "_") {
            com = UNDERSCORE_KEY;
            modifier = 1;
        }

        if (sym == "-")
            com = MINUS_KEY;

        if (sym == "/")
            com = XK_slash;

        XKeyEvent event = createKeyEvent(display, winFocus, winRoot, true, com, modifier);
        XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

        event = createKeyEvent(display, winFocus, winRoot, false, com, modifier);
        XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);
    }

    XKeyEvent event = createKeyEvent(display, winFocus, winRoot, true, ENTER, 0);
    XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

    event = createKeyEvent(display, winFocus, winRoot, false, ENTER, 0);
    XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

    XCloseDisplay(display);
}


int ConsoleService::closeConsole() {
    Display *display = XOpenDisplay(nullptr);
    if(display == nullptr)
        return -1;
    Window winRoot = XDefaultRootWindow(display);
    Window winFocus;
    int    revert;
    XGetInputFocus(display, &winFocus, &revert);

    XKeyEvent event = createKeyEvent(display, winFocus, winRoot, true, ESC_KEY, 0);
    XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

    event = createKeyEvent(display, winFocus, winRoot, false, ESC_KEY, 0);
    XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

    XCloseDisplay(display);
    return 0;
}


ConsoleService::ConsoleService(const ConsoleService& orig) = default;

ConsoleService::~ConsoleService() = default;