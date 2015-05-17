#ifndef CONCRETE_COMMANDS_H
#define CONCRETE_COMMANDS_H
#include "Command.h"
#include "Enumerations.hpp"

Command moveLeft;
moveLeft.category = Category::PlayerAircraft;
moveLeft.action = AircraftMover(-player)


#endif //CONCRETE_COMMANDS_H