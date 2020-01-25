//
// Created by markel33 on 1/25/20.
//

#include <iostream>
#include "ConsoleService.h"
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <unistd.h>
#include <cstring>

#define INSERT_KEY XK_Insert
#define ESC_KEY XK_Escape
#define PERIOD XK_period
#define SPACE XK_space
#define ENTER XK_Return

using namespace std;
ConsoleService::ConsoleService() = default;

XKeyEvent createKeyEvent(Display *display, Window &win,
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
    Display *display = XOpenDisplay(nullptr);
    Window winRoot = XDefaultRootWindow(display);
    Window winFocus;
    int    revert;
    XGetInputFocus(display, &winFocus, &revert);

    //TODO parametrise this
    XKeyEvent event = createKeyEvent(display, winFocus, winRoot, true, INSERT_KEY, 0);
    XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

    event = createKeyEvent(display, winFocus, winRoot, false, INSERT_KEY, 0);
    XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

    XCloseDisplay(display);
    return 0;
}

int ConsoleService::typeCommand(char *command) {
    sleep(1);

    Display *display = XOpenDisplay(nullptr);
    Window winRoot = XDefaultRootWindow(display);
    Window winFocus;
    int    revert;
    XGetInputFocus(display, &winFocus, &revert);

    for (int i = 0; i < strlen(command); i++){
        std::string str = "volume 0.6";
        string sym(1, str[i]);

        KeySym com = XStringToKeysym(sym.c_str());

        if (sym == ".")
            com = PERIOD;

        if (sym == " ")
            com = SPACE;

        XKeyEvent event = createKeyEvent(display, winFocus, winRoot, true, com, 0);
        XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

        event = createKeyEvent(display, winFocus, winRoot, false, com, 0);
        XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

    }

    XKeyEvent event = createKeyEvent(display, winFocus, winRoot, true, ENTER, 0);
    XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

    event = createKeyEvent(display, winFocus, winRoot, false, ENTER, 0);
    XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);


// Done.
    cout << "Command executed";
    XCloseDisplay(display);
    return 0;
}


int ConsoleService::closeConsole() {
    Display *display = XOpenDisplay(nullptr);
    if(display == nullptr)
        return -1;

// Get the root window for the current display.
    Window winRoot = XDefaultRootWindow(display);
// Find the window which has the current keyboard focus.
    Window winFocus;
    int    revert;
    XGetInputFocus(display, &winFocus, &revert);

// Send a fake key press event to the window.
    XKeyEvent event = createKeyEvent(display, winFocus, winRoot, true, ESC_KEY, 0);
    XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

// Send a fake key release event to the window.
    event = createKeyEvent(display, winFocus, winRoot, false, ESC_KEY, 0);
    XSendEvent(event.display, event.window, True, KeyPressMask, (XEvent *)&event);

// Done.
    cout << "Console Closed";
    XCloseDisplay(display);
    return 0;
}


ConsoleService::ConsoleService(const ConsoleService& orig) = default;

ConsoleService::~ConsoleService() = default;