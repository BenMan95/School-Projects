#ifndef UFO_FACTORY_H_
#define UFO_FACTORY_H_

#include "IEntity.h"
#include "IEntityFactory.h"
#include "Ufo.h"

#include <vector>

/**
 * @brief this class inhertis from the IEntityFactory class and
 *  represents an ufo factory to create ufos.
 */
class UfoFactory : public IEntityFactory {
  public:
    virtual ~UfoFactory() {}
    /**
     * @brief Create an ufo.
     * @param[in] entity an entity
     * @return The ufo created.
     */
    IEntity* CreateEntity(JsonObject& entity);
};

#endif  // UFO_FACTORY_H_
