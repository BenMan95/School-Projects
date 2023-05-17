#ifndef LIBS_TRANSIT_INCLUDE_CELEBRATIONDECORATOR_H_
#define LIBS_TRANSIT_INCLUDE_CELEBRATIONDECORATOR_H_

/**
 * include
 */
#include "math/vector3.h"
#include <vector>
#include "IStrategy.h"
#include "IEntity.h"
/**
 * @brief This class inherits from the IStrategy class.
 *  This is a Decorator class for the interface IStrategy
 */
class CelebrationDecorator : public IStrategy {
 public:
    /**
     * @brief Created with a IStrategy pointer.
     *  Sets strategy member variable and sets time to 0.
     * @param[in] strategy IStrategy pointer (i.e. Astar, Dfs, Dijkstra)
     */
    CelebrationDecorator(IStrategy *strategy);
    /**
     * @brief Destructor. Deletes strategy
     */
    ~CelebrationDecorator();
    /**
     * @brief Calls the concrete decorator's Move function.
     *  (i.e. return strategy->Move(entity, dt))
     * @param[in] entity IEntity pointer (i.e. Drone object pointer)
     * @param[in] dt Time internal for update
     */
    void Move(IEntity* entity, double dt);
    /**
     * @brief Checks if celebration is completed
     * @return True if completed, false if not completed.
     */
    bool IsCompleted();

 protected:
    IStrategy *strategy;
    float time;
};  // end class

#endif  // LIBS_TRANSIT_INCLUDE_CELEBRATIONDECORATOR_H_
