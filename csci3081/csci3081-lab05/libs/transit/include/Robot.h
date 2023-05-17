#ifndef ROBOT_H
#define ROBOT_H

#include <vector>

#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"

/**
 * @brief Represents a robot in a physical system.
 */
class Robot : public IEntity { public: Robot(JsonObject& obj);

  /**
   *  @brief Override the destructor
   */
  ~Robot() override = default;

  /**
   * @brief Returns the position of this Robot object
   * @return The position of this Robot object as a Vector3 object
   */
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Returns the direction of this Robot object
   * @return The direction of this Robot object as a Vector3 object
   */
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Returns the destination of this Robot object
   * @return The destination of this Robot object as a Vector3 object
   */
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Returns the availability of this Robot object
   * @return The availability of this Robot object as a boolean
   */
  bool GetAvailability() const { return available; }

  /**
   * @brief Returns the details of this Robot object
   * @return The details of this Robot object as a JsonObject
   */
  JsonObject GetDetails() const override;

  float GetSpeed() const { return speed; }

  /**
   * @brief Returns the availability of this Robot object
   * @return The availability of this Robot object as a boolean
   */
  void SetAvailability(bool choice);

  /**
   * @brief Sets the position of the Robot
   * @param[in] pos_ The Vector3 to set the robot's postion to
   */
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Sets the direction of the Robot
   * @param[in] dir_ The Vector3 to set the robot's direction to
   */
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
   * @brief Sets the destination of the Robot
   * @param[in] des_ The Vector3 to set the robot's destination to
   */
  void SetDestination(Vector3 des_) { destination = des_; }

  /**
   * @brief Rotates a robot
   * @param[in] angle The angle to rotate the robot by
   */
  void Rotate(double angle);

 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  Vector3 destination;
  float speed;
  bool available;
};

#endif  // ROBOT_H
