#ifndef HELICOPTER_H_
#define HELICOPTER_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

/**
 * @brief this class inhertis from the IEntity class and
 *  represents a helicopter in a physical system.
 */
class Helicopter : public IEntity {
  public:
      /**
       * @brief Parameter constructor.
       *
       * @param[in] obj json object
       */
      Helicopter(JsonObject& obj);

      /**
      * @brief Destructor.
      */
      ~Helicopter();

      /**
       * @brief Get the speed of the helicopter.
       * @return The speed of the helicopter.
       */
      float GetSpeed() const { return speed; }

      /**
       * @brief Gets the helicopter position.
       * @return The helicopter position
       */
      // Gets the Helicopter position
      Vector3 GetPosition() const { return position; }

      /**
       * @brief Get the direction of the helicopter.
       * @return The direction of the helicopter.
       */
      Vector3 GetDirection() const { return direction; }

      /**
       * @brief Get the destination of the helicopter.
       * @return The destination of the helicopter.
       */
      Vector3 GetDestination() const { return destination; }

      /**
       * @brief Get the details of the helicopter.
       * @return The details of the helicopter.
       */
      JsonObject GetDetails() const { return details; }

      /**
       * @brief Get whether the helicopter is available or not.
       * @return Whether the helicopter is available or not.
       */
      bool GetAvailability() const { return available; }

      /**
       * @brief Gets a random position given a min/max number.
       * @param[in] min the minimum boundary.
       * @param[in] max the maximum boundary.
       * @return The random number.
       */
      int GetRandomNum(int min, int max);

      /**
       * @brief Gets the random destination.
       * @return The random destination.
       */
      Vector3 GetRandDest();

      /**
       * @brief Update the helicopter.
       * @param[in] dt delta time.
       * @param[in] scheduler the scheduled entity list.
       */
      void Update(double dt, std::vector<IEntity*> scheduler);

      /**
       * @brief Set the helicopter position.
       * @param[in] pos_ the position you would like to set to the helicopter.
       */
      void SetPosition(Vector3 pos_) { position = pos_; }

      /**
       * @brief Set the helicopter direction.
       * @param[in] dir_ the direction you would like to set to the helicopter.
       */
      void SetDirection(Vector3 dir_) { direction = dir_; }

      /**
       * @brief Set the helicopter destination.
       * @param[in] des_ the destination you would like to set to
       * the helicopter.
       */
      void SetDestination(Vector3 des_) { destination = des_; }

      /**
       * @brief Rotate the helicopter.
       * @param[in] angle the angle you would like to rotate the helicopter.
       */
      void Rotate(double angle);

      Helicopter(const Helicopter& helicopter) = delete;
      Helicopter& operator=(const Helicopter& helicopter) = delete;

  private:
        JsonObject details;
        Vector3 position;
        Vector3 direction;
        Vector3 destination;
        bool available;
        bool reached;
        float speed;
        IStrategy* toDestStrategy;
};

#endif  // HELICOPTER_H_
