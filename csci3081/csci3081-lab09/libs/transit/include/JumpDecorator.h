#ifndef LIBS_TRANSIT_INCLUDE_JUMPDECORATOR_H_
#define LIBS_TRANSIT_INCLUDE_JUMPDECORATOR_H_

/**
 * include
 */
#include "IStrategy.h"
#include "IEntity.h"
#include "CelebrationDecorator.h"
/**
 * @brief This class inherits from IStrategy & CelebrationDecorator
 *  This is a Decorator class for the interface IStrategy
 *  which causes an entity to jump after reaching its destination
 */
class JumpDecorator : public CelebrationDecorator {
 public:
  /**
   * @brief Created with a IStrategy pointer. Initalizes
   *  strategy member variable by calling CelebrationDecorator constructor
   * @param[in] strategy IStrategy pointer (i.e. Strategy, or Decorator)
   */
  JumpDecorator(IStrategy *strategy);
  /**
   * @brief Destructor. Deletes strategy
   */
  ~JumpDecorator();
  /**
   * @brief Moves the passed in entity.
   *  If strategy is completed and current decorator not completed,
   *  continue jumping. Else, call strategy's Move
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
#endif  // LIBS_TRANSIT_INCLUDE_JUMPDECORATOR_H_
