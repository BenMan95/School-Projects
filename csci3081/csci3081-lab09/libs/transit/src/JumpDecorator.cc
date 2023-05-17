
/**
 * include
 */
#include "JumpDecorator.h"
/**
 * @brief this class inherits from the CelebrationDecorator class.
 */

JumpDecorator::JumpDecorator(IStrategy *strategy)
  : CelebrationDecorator(strategy) {
}

JumpDecorator::~JumpDecorator() {
  delete strategy;
}

bool JumpDecorator::IsCompleted() {
  return time > 1.5;
}

void JumpDecorator::Move(IEntity* entity, double dt) {
  if (strategy->IsCompleted() && !IsCompleted()) {
    entity->Jump(5);
    time = time + dt;
  } else {
    strategy->Move(entity, dt);
  }
}
