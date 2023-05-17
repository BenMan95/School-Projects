#ifndef ROBOT_H_
#define ROBOT_H_

#include "entity.h"
#include <vector>
using namespace std;

// Represents a robot in a physical system.
// Robots move in a circle with a specified radius.
class Robot : public MovableEntity {
 public:
  // Robots are declared with a name and a radius
  Robot(const string name, float radius);
  // Gets the robot name
  const string GetName() { return name; }
  // Gets the robot position
  vector<double> GetPosition() { return pos; }
  // Updates the robot's position
  void Update(double dt);

 private:
  string name;
  vector<double> pos;
  double angle;
  double radius;
};

#endif
