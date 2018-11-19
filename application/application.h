#ifndef APPLICATION_H
#define APPLICATION_H

#include "../command.h"
#include "model.h"

class Application
{
public:
    Application() = default;
    void setCommand(Command *command);
    void test_function();
    Model *model;

private:
    Command *_command;
};

#endif // APPLICATION_H
