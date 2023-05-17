#ifndef HELICOPTER_FACTORY_H_
#define HELICOPTER_FACTORY_H_

#include "IEntity.h"
#include "IEntityFactory.h"
#include "Helicopter.h"

#include <vector>

/**
 * @brief this class inhertis from the IEntityFactory class and
 *  represents a helicopter factory to create helicopters.
 */
class HelicopterFactory : public IEntityFactory {
  public:
    virtual ~HelicopterFactory() {}
    /**
     * @brief Create a helicopter.
     * @param[in] entity an entity
     * @return The helicopter created.
     */
    IEntity* CreateEntity(JsonObject& entity);
};

#endif  // HELICOPTER_FACTORY_H_
