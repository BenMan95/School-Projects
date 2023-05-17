#define _USE_MATH_DEFINES
#include "robot.h"

#include <cmath>
using namespace std;

Robot::Robot(const string name, float radius)
    : name(name), pos(2), angle(0.0), radius(radius) {
  pos.at(0) = radius * cos(angle);
  pos.at(1) = radius * sin(angle);
}

void Robot::Update(double dt) {
  angle += dt;
  pos.at(0) = radius * cos(angle);
  pos.at(1) = radius * sin(angle);
}
