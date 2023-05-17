#define _USE_MATH_DEFINES
#include "drone.h"

#include <cmath>
#include <vector>
using namespace std;

Drone::Drone(const string name) : name(name), position(3), velocity(3) {}

void Drone::SetVelocity(vector<double> velocity) {
  // Copy the velocity data into the member variable array.
  this->velocity.at(0) = velocity.at(0);
  this->velocity.at(1) = velocity.at(1);
  this->velocity.at(2) = velocity.at(2);
}

void Drone::Update(double dt) {
  // Updates the drone position based on velocity and change in time
  for (int i = 0; i < 3; i++) {
    position.at(i) = position.at(i) + velocity.at(i) * dt;
  }
}

void Drone::Rotate(double angle) {
  // Rotates the drone by changing the velocity by a
  // specified angle.
  double x = velocity.at(0);
  double y = velocity.at(1);
  velocity.at(0) = x * cos(angle) - y * sin(angle);
  velocity.at(1) = x * sin(angle) + y * cos(angle);
}
