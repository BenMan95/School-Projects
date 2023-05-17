#ifndef DRONE_H_
#define DRONE_H_

#include "entity.h"
#include <vector>
using namespace std;

// Represents a drone in a physical system.
// Drones move using euler integration based on a specified
// velocity and direction.
class Drone : public MovableEntity {
 public:
  // Drones are created with a name
  Drone(const string name);
  // Gets the drone name
  const string GetName() { return name; }
  // Gets the drone position
  vector<double> GetPosition() { return position; }
  // Updates the drone's position
  void Update(double dt);
  // Sets the drone's velocity
  void SetVelocity(vector<double> velocity);
  // Rotates a drone
  void Rotate(double angle);

  // Removing the copy constructor and assignment operator
  // so that drones cannot be coppied.
  Drone(const Drone& drone) = delete;
  Drone& operator=(const Drone& drone) = delete;

 private:
  string name;
  vector<double> position;
  vector<double> velocity;
};

#endif
