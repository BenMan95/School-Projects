#ifndef DRONE_H_
#define DRONE_H_

#include <vector>

#include "IEntity.h"
#include "math/vector3.h"

/**
 * @brief
 * Represents a drone in a physical system.
 * Drones move using euler integration based on a specified
 * velocity and direction.
 */
class Drone : public IEntity {
 public:
  /**
   * @brief Constructor for creating a Drone from a JsonObject
   * @param[in] obj A JsonObject with the details to create the Drone with
   */
  Drone(JsonObject& obj);

  /**
   * @brief Destructor
   */
  ~Drone();
  
  /**
   * @brief Returns the speed of this Drone object
   * @return The speed of this Drone object as a float
   */
  float GetSpeed() const { return speed; }

  /**
   * @brief Returns the position of this Drone object
   * @return The position of this Drone object as a Vector3 object
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Returns the direction of this Drone object
   * @return The direction of this Drone object as a Vector3 object
   */
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Returns the destination of this Drone object
   * @return The destination of this Drone object as a Vector3 object
   */
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Returns the details of this Drone object
   * @return The details of this Drone object as a JsonObject
   */
  JsonObject GetDetails() const { return details; }

  /**
   * @brief Returns the availability of this Drone object
   * @return The availability of this Drone object as a boolean
   */
  bool GetAvailability() const { return available; }

  /**
   * @brief Finds the nearest entity and saves its position
   * @param[in] scheduler The list of entities to use
   */
  void GetNearestEntity(std::vector<IEntity*> scheduler);

  /**
   * @brief Updates the position of the drone
   * 
   * @param[in] dt The time step to use
   * @param[in] schedule The list of entities to use
   */
  void Update(double dt, std::vector<IEntity*> scheduler);

  /**
   * @brief Sets the position of the drone
   * @param[in] pos_ The Vector3 to set the drone's position to
   */
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Sets the drone's direction
   * @param[in] dir_ The Vector3 to set the drone's direction to
   */
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
   * @brief Sets the drone's destination
   * @param[in] dir_ The Vector3 to set the drone's destination to
   */
  void SetDestination(Vector3 des_) { destination = des_; }

  /**
   * @brief Rotates a drone
   * @param[in] angle The angle to rotate the drone by
   */
  void Rotate(double angle);

  // Removing the copy constructor and assignment operator
  // so that drones cannot be coppied.
  Drone(const Drone& drone) = delete;
  Drone& operator=(const Drone& drone) = delete;

 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  Vector3 destination;
  float speed;
  bool available;

  IEntity* nearestEntity = NULL;
};

#endif
