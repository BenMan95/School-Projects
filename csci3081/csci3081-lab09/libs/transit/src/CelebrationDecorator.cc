
#include "CelebrationDecorator.h"

CelebrationDecorator::CelebrationDecorator(IStrategy *strategy) {
  this->strategy = strategy;
  this->time = 0;
}

CelebrationDecorator::~CelebrationDecorator() {
  delete strategy;
}

bool CelebrationDecorator::IsCompleted() {
  return time > 1.5;
}

void CelebrationDecorator::Move(IEntity* entity, double dt) {
  return strategy->Move(entity, dt);
}
