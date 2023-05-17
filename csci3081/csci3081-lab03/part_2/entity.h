#ifndef ENTITY_H_
#define ENTITY_H_

#include <string>
#include <vector>
using namespace std;

// Entity is the base class for any simulation object
class Entity {
 public:
  // Destructor
  virtual ~Entity() {}
  // Returns the name of the entity
  virtual const string GetName();
  // Returns the position of the entity in space
  virtual vector<double> GetPosition() = 0;
};

// An entity that can move and be updated
class MovableEntity : public Entity {
 public:
  // Updates the movable entity
  virtual void Update(double dt) = 0;
};

#endif
