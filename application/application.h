#ifndef APPLICATION_H
#define APPLICATION_H

#include "commands/command.h"

class Application
{
public:
    Application() = default;
    void setCommand(Command *command);
    void test_function();

private:
    Command *_command;
};

#endif // APPLICATION_H
