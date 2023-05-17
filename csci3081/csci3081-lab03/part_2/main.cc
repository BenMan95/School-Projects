#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "drone.h"
#include "robot.h"
#include "tree.h"
using namespace std;

int main(int argc, char** argv) {
  // Initialize the number of iterations and simulation dt
  int iterations = 3;
  double dt = 0.1;
  if (argc > 1) {
    iterations = atoi(argv[1]);
    dt = atof(argv[2]);
  }

  // Create two drones (Drone-A and Drone-X) and set their
  // initial velocity and rotation.
  Drone* mainDrone = new Drone("Drone-A");
  Drone* droneX = new Drone("Drone-X");
  vector<double> velocity(3);
  velocity.at(0) = 1;
  velocity.at(1) = 0;
  velocity.at(2) = 1;
  mainDrone->SetVelocity(velocity);
  mainDrone->Rotate(M_PI / 4.0);
  droneX->SetVelocity(velocity);

  // Create a vector that holds entities (simulation entities).
  // This includes anything that inherits from Entity.
  // Add some entities to the vector.
  vector<Entity*> entities;
  entities.push_back(mainDrone);
  entities.push_back(new Tree("Oak", 50.0, 50.0));
  entities.push_back(new Robot("Johnny-Five", 1.0));
  entities.push_back(new Tree("Maple", 100.0, 100.0));
  entities.push_back(droneX);
  entities.push_back(new Robot("Dave", 4));

  // Iteratively call several simulation steps (iterations)
  for (int iteration = 0; iteration < iterations; iteration++) {
    // Output the time step
    cout << "Time = " << (iteration * dt) << ":" << endl;
    cout << "--------------" << endl;

    // Loop through the entities
    for (int i = 0; i < entities.size(); i++) {
      // Print out the current entity
      Entity& entity = *entities.at(i);
      cout << entity.GetName();
      vector<double> pos = entity.GetPosition();
      for (int i = 0 ; i < pos.size() ; i++) {
        cout << ", " << pos.at(i);
      }
      cout << endl;

      // Update all movable entities (entities that have an update function)
      // E.g. Trees do not update, but drones and robots will.
      MovableEntity* movable = dynamic_cast<MovableEntity*>(entities.at(i));
      if (movable)
        movable->Update(dt);
    }
    cout << endl;
  }

  // Delete Entities
  for (int i = 0; i < entities.size(); i++) {
    delete entities.at(i);
  }

  cout << "Simulation Complete" << endl;

  return 0;
}
