#ifndef UFO_H_
#define UFO_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

/**
 * @brief this class inhertis from the IEntity class and
 * represents an ufo in a physical system.
 */
class Ufo : public IEntity {
  public:
      /**
       * @brief Parameter constructor.
       *
       * @param[in] obj json object
       */
      Ufo(JsonObject& obj);

      /**
      * @brief Destructor.
      */
      ~Ufo();

      /**
       * @brief Get the speed of the ufo.
       * @return The speed of the ufo.
       */
      float GetSpeed() const { return speed; }

      /**
       * @brief Gets the ufo position.
       * @return The ufo position
       */
      Vector3 GetPosition() const { return position; }

      /**
       * @brief Get the direction of the ufo.
       * @return The direction of the ufo.
       */
      Vector3 GetDirection() const { return direction; }

      /**
       * @brief Get the destination of the ufo.
       * @return The destination of the ufo.
       */
      Vector3 GetDestination() const { return destination; }

      /**
       * @brief Get the details of the ufo.
       * @return The details of the ufo.
       */
      JsonObject GetDetails() const { return details; }

      /**
       * @brief Get whether the ufo is available or not.
       * @return Whether the ufo is available or not.
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
       * @brief Update the ufo.
       * @param[in] dt delta time.
       * @param[in] scheduler the scheduled entity list.
       */
      void Update(double dt, std::vector<IEntity*> scheduler);

      /**
       * @brief Set the ufo position.
       * @param[in] pos_ the position you would like to set to the ufo.
       */
      void SetPosition(Vector3 pos_) { position = pos_; }

      /**
       * @brief Set the ufo direction.
       * @param[in] dir_ the direction you would like to set to the ufo.
       */
      void SetDirection(Vector3 dir_) { direction = dir_; }

      /**
       * @brief Set the ufo destination.
       * @param[in] des_ the destination you would like to set to the ufo.
       */
      void SetDestination(Vector3 des_) { destination = des_; }

      /**
       * @brief Rotate the ufo.
       * @param[in] angle the angle you would like to rotate the ufo.
       */
      void Rotate(double angle);

      Ufo(const Ufo& ufo) = delete;
      Ufo& operator=(const Ufo& ufo) = delete;

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

#endif  // UFO_H_
