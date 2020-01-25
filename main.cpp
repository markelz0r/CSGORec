#include <iostream>
#include "ConsoleService.h"
#include <unistd.h>


int main() {
    sleep(5);
    auto* c = new ConsoleService();
    c->openConsole();
    char command[] = "volume 0.5";
    c->typeCommand(command);
}
