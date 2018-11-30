//
// Created by Иван Морозов on 15.11.2018.
//

#ifndef KURSOVAYA2_0_OPEN_COMMAND_H
#define KURSOVAYA2_0_OPEN_COMMAND_H

#include "command.h"

class OpenCommand : public Command {
 public:
  OpenCommand(char *filepath);
  void execute() final;
 private:
  char *_filepath;

};

#endif //KURSOVAYA2_0_OPEN_COMMAND_H
