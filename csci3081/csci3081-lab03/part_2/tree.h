#ifndef TREE_H_
#define TREE_H_

#include "entity.h"
#include <vector>
using namespace std;

// Represents a Tree in a physical system
class Tree : public Entity {
 public:
  // Trees are on the ground, so do not have a z component
  Tree(const string name, double x, double y) : pos(2), name(name) {
    pos.at(0) = x;
    pos.at(1) = y;
  }
  // Gets the tree name
  const string GetName() { return name; }
  // Gets the tree position
  vector<double> GetPosition() { return pos; }

 private:
  vector<double> pos;
  const string name;
};

#endif
