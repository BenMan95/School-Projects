#ifndef SPIN_DECORATOR_H_
#define SPIN_DECORATOR_H_

#include <vector>

#include "CelebrationDecorator.h"
#include "IStrategy.h"

/**
 * @brief this class inhertis from the CelebrationDecorator class and
 *  represents a spin decorator in a physical system.
 */
class SpinDecorator : public CelebrationDecorator {
 public:
  /**
   * @brief Parameter constructor.
   *
   * @param[in] strategy_ A pointer to the strategy
   */
  SpinDecorator(IStrategy* strategy_) : CelebrationDecorator(strategy_) {}
  /**
   * @brief Check if the decorator is completed.
   * @return True if completed; otherwise, false.
   */
  bool IsCompleted();
  /**
   * @brief Make move.
   *
   * @param[in] entity A pointer to the entity.
   * @param[in] dt Delta time.
   */
  void Move(IEntity* entity, double dt);
};  // close class

#endif  // SPIN_DECORATOR_H_

