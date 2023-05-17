#ifndef CAR_FACTORY_H_
#define CAR_FACTORY_H_

#include "IEntity.h"
#include "IEntityFactory.h"
#include "Car.h"

#include <vector>

/**
 * @brief this class inhertis from the IEntityFactory class and
 *  represents a car factory to create cars.
 */
class CarFactory : public IEntityFactory {
  public:
    virtual ~CarFactory() {}
    /**
     * @brief Create a car.
     * @param[in] entity an entity
     * @return The car created.
     */
    IEntity* CreateEntity(JsonObject& entity);
};

#endif  // CAR_FACTORY_H_
