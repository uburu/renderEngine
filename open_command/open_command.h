//
// Created by Иван Морозов on 15.11.2018.
//

#ifndef KURSOVAYA2_0_OPEN_COMMAND_H
#define KURSOVAYA2_0_OPEN_COMMAND_H

#include "../command.h"
#include "model.h"

class OpenCommand : public Command {
 public:
  OpenCommand(Model **model, char *filepath);
  void execute() final;
 private:
  Model **_model;
  char *_filepath;

};

#endif //KURSOVAYA2_0_OPEN_COMMAND_H
