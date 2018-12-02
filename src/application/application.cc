#include "application.h"

#include <vector>
#include <cmath>

void Application::test_function() {

}

void Application::setCommand(Command *command) {
  _command = command;
  _command->execute();
}