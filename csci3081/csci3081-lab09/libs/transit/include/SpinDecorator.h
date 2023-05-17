#ifndef LIBS_TRANSIT_INCLUDE_SPINDECORATOR_H_
#define LIBS_TRANSIT_INCLUDE_SPINDECORATOR_H_

/**
 * include
 */
#include "IStrategy.h"
#include "IEntity.h"
#include "CelebrationDecorator.h"
/**
 * @brief this class inherits from the CelebrationDecorator class and is responsible for generating the beeline that the drone will take.
 */
class SpinDecorator : public CelebrationDecorator {
 public:
  /**
   * @brief This class inherits from IStrategy & CelebrationDecorator
   *  This is a Decorator class for the interface IStrategy
   *  which causes an entity to spin after reaching its destination
   */
  SpinDecorator(IStrategy *strategy);
  /**
   * @brief Destructor. Deletes strategy
   */
  ~SpinDecorator();
  /**
   * @brief Moves the passed in entity.
   *  If strategy is completed and current decorator not completed,
   *  continue spinning. Else, call strategy's Move
   * @param[in] entity IEntity pointer (i.e. Drone object pointer)
   * @param[in] dt Time internal for update
   */
  void Move(IEntity* entity, double dt);
  /**
   * @brief Checks if celebration is completed.
   * @return True if completed, false if not completed.
   */
  bool IsCompleted();
};  // end class
#endif  // LIBS_TRANSIT_INCLUDE_SPINDECORATOR_H_
