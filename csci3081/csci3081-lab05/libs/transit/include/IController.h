#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "IEntity.h"
#include "util/json.h"

//--------------------  Controller Interface ----------------------------

/**
 * @brief
 * Abstract controller class used in the Transit Service.  Uses the Model View
 * Controller Pattern
 */
class IController {
 public:
  /**
   * @brief The default constructor
   */
  virtual ~IController() {}

  /**
   * @brief Adds an entity to the program
   * @param[in] entity The entity to add
   */
  virtual void AddEntity(const IEntity& entity) = 0;

  /**
   * @brief Updates an entity in the program
   * @param[in] entity The entity to update
   */
  virtual void UpdateEntity(const IEntity& entity) = 0;

  /**
   * @brief Removes an entity from the program
   * @param[in] id The id of the entity to be removed
   */
  virtual void RemoveEntity(int id) = 0;

  /**
   * @brief Adds a path to the program
   * @param[in] id The id of the drone to add the path for
   * @param[in] path The path to add to the program
   */
  virtual void AddPath(int id,
                       const std::vector<std::vector<float> >& path) = 0;

  /**
   * @brief Removes a path from the program
   * @param[in] id The id of the path to remove
   */
  virtual void RemovePath(int id) = 0;

  /**
   * @brief Allows messages to be passed back to the view
   * @param[in] event The event to send a message about
   * @param[in] details The details of the message to send
   */
  virtual void SendEventToView(const std::string& event,
                               const JsonObject& details) = 0;
};

#endif
