//
// Created by Иван Морозов on 15.11.2018.
//

#ifndef KURSOVAYA2_0_COMMAND_H
#define KURSOVAYA2_0_COMMAND_H

class Command {
 public:
  virtual void execute() = 0;

 protected:
  Command() {}
};

#endif //KURSOVAYA2_0_COMMAND_H
