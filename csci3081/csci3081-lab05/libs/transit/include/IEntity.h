#ifndef ENTITY_H_
#define ENTITY_H_

#include <vector>

#include "graph.h"
#include "math/vector3.h"
#include "util/json.h"

using namespace routing;

//--------------------  Controller Interface ----------------------------

/**
 * @brief
 * Abstract controller class used in the Transit Service. Uses the Model View
 * Controller Pattern
 */
class IEntity {
 public:
  /**
   * @brief The default constructor
   */
  IEntity() {
    static int currentId = 0;
    id = currentId;
    currentId++;
  }

  /**
   * The destructor
   */
  virtual ~IEntity() {}

  /**
   * @brief Returns the id of this IEntity object
   * @return The id of this IEntity object as an integer
   */
  virtual int GetId() const { return id; }

  /**
   * @brief Returns the position of this IEntity object
   * @return The position of this IEntity object as a Vector3 object
   */
  virtual Vector3 GetPosition() const = 0;

  /**
   * @brief Returns the direction of this IEntity object
   * @return The direction of this IEntity object as a Vector3 object
   */
  virtual Vector3 GetDirection() const = 0;

  /**
   * @brief Returns the destination of this IEntity object
   * @return The destination of this IEntity object as a Vector3 object
   */
  virtual Vector3 GetDestination() const = 0;

  /**
   * @brief Returns the details of this IEntity object
   * @return The details of this IEntity object as a JsonObject
   */
  virtual JsonObject GetDetails() const = 0;

  /**
   * @brief Returns the speed of this IEntity object
   * @return The speed of this IEntity object as a float
   */
  virtual float GetSpeed() const = 0;

  /**
   * @brief Returns the availability of this IEntity object
   * @return The availability of this IEntity object as a boolean
   */
  virtual bool GetAvailability() const = 0;

  /**
   * @brief Sets the availability of the IEntity object
   * @param[in] choice The boolean to set the IEntity object's availability to
   */
  virtual void SetAvailability(bool choice) {}

  /**
   * @brief Updates the IEntity object
   * 
   * @param[in] dt The time step to use
   * @param[in] scheduler The entity list to use
   */
  virtual void Update(double dt, std::vector<IEntity*> scheduler) {}

  /**
   * @brief Sets the graph of the IEntity object
   * @param[in] graph The graph to set for the IEntity object
   */
  void SetGraph(const IGraph* graph) { this->graph = graph; }

  /**
   * @brief Sets the position of the IEntity object
   * @param[in] pos_ The Vector3 to set the IEntity object's position to
   */
  virtual void SetPosition(Vector3 pos_) {}

  /**
   * @brief Sets the direction of the IEntity object
   * @param[in] dir_ The Vector3 to set the IEntity object's direction to
   */
  virtual void SetDirection(Vector3 dir_) {}

  /**
   * @brief Sets the destination of the IEntity object
   * @param[in] des_ The Vector3 to set the IEntity object's destination to
   */
  virtual void SetDestination(Vector3 des_) {}

  /**
   * @brief Rotates the IEntity object
   * @param[in] dt The amount to rotate the IEntity object by
   */
  virtual void Rotate(double dt) {}

 protected:
  int id;
  const IGraph* graph;
};

#endif
