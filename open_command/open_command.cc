//
// Created by Иван Морозов on 15.11.2018.
//

#include "open_command.h"

OpenCommand::OpenCommand(Model **model, char *filepath) : _model(model), _filepath(filepath) {}

void OpenCommand::execute() {
  (*_model) = new Model(_filepath);
}