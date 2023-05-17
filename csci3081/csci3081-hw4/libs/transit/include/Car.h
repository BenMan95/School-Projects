#ifndef CAR_H_
#define CAR_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

/**
 * @brief this class inhertis from the IEntity class and
 *  represents a car in a physical system.
 */
class Car : public IEntity {
  public:
      /**
       * @brief Parameter constructor.
       *
       * @param[in] obj json object
       */
      Car(JsonObject& obj);

      /**
      * @brief Destructor.
      */
      ~Car();

      /**
       * @brief Get the speed of the car.
       * @return The speed of the car.
       */
      float GetSpeed() const { return speed; }
      /**
       * @brief Gets the car position.
       * @return The car position
       */
      Vector3 GetPosition() const { return position; }

      /**
       * @brief Get the direction of the car.
       * @return The direction of the car.
       */
      Vector3 GetDirection() const { return direction; }

      /**
       * @brief Get the destination of the car.
       * @return The destination of the car.
       */
      Vector3 GetDestination() const { return destination; }

      /**
       * @brief Get the details of the car.
       * @return The details of the car.
       */
      JsonObject GetDetails() const { return details; }

      /**
       * @brief Get whether the car is available or not.
       * @return Whether the car is available or not.
       */
      bool GetAvailability() const { return available; }

      // Gets a random position given a min/max number
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
       * @brief Update the car.
       * @param[in] dt delta time.
       * @param[in] scheduler the scheduled entity list.
       */
      void Update(double dt, std::vector<IEntity*> scheduler);

      /**
       * @brief Set the car position.
       * @param[in] pos_ the position you would like to set to the car.
       */
      void SetPosition(Vector3 pos_) { position = pos_; }

      /**
       * @brief Set the car direction.
       * @param[in] dir_ the direction you would like to set to the car.
       */
      void SetDirection(Vector3 dir_) { direction = dir_; }

      /**
       * @brief Set the car destination.
       * @param[in] des_ the destination you would like to set to the car.
       */
      void SetDestination(Vector3 des_) { destination = des_; }

      /**
       * @brief Rotate the car.
       * @param[in] angle the angle you would like to rotate the car.
       */
      void Rotate(double angle);

      Car(const Car& car) = delete;
      Car& operator=(const Car& car) = delete;

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

#endif  // CAR_H_
