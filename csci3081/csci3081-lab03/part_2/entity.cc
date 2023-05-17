#include "entity.h"
using namespace std;

const string Entity::GetName() {
  // static allows us to keep the name entity for the duration
  // of the entire program.  This allows us to pass a reference back.
  // When a variable is declared static, there is only one variable per class.
  static string name("Entity");
  return name;
}
