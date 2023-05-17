
/**
 * include
 */

#include "SpinDecorator.h"
/**
 * @brief This class inherits from IStrategy & CelebrationDecorator
 *  This is a Decorator class for the interface IStrategy,
 *  which causes an entity to spin after reaching its destination
 */
SpinDecorator::SpinDecorator(IStrategy *strategy)
  : CelebrationDecorator(strategy) {
}

SpinDecorator::~SpinDecorator() {
  delete strategy;
}

bool SpinDecorator::IsCompleted() {
  return time > 1.5;
}

void SpinDecorator::Move(IEntity* entity, double dt) {
  if (strategy->IsCompleted() && !IsCompleted()) {
    entity->Rotate(dt * 10);
    time = time + dt;
  } else {
    strategy->Move(entity, dt);
  }
}
