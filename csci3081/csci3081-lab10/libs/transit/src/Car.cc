#define _USE_MATH_DEFINES
#include "Car.h"
#include "AstarStrategy.h"

#include <cmath>
#include <limits>

Car::Car(JsonObject& obj) : details(obj) {
    JsonArray pos(obj["position"]);
    position = {pos[0], pos[1], pos[2]};

    JsonArray dir(obj["direction"]);
    direction = {dir[0], dir[1], dir[2]};

    speed = obj["speed"];

    available = true;
}

Car::~Car(){
    // ...
}

int Car::GetRandomNum(int min, int max){
    return (rand() % (max - min + 1) + min);
}

Vector3 Car::GetRandDest(){
    float x = (float) GetRandomNum(-1400, 1500);
    float y = 243.0; //(float) GetRandomNum(240, 1000);
    float z = (float) GetRandomNum(-800, 800);
    return {x, y, z};
}

void Car::Update(double dt, std::vector<IEntity*> scheduler){
    
    if(available){
        destination = GetRandDest();       // Get Random Destination.
        toDestStrategy = new AstarStrategy(position, destination, graph);
        available = false;
    }

    // If the Car has a destination...
    if(toDestStrategy){
        // Move the Car
        toDestStrategy->Move(this, dt);

        // Once the Car arrives at the destination...
        if(toDestStrategy->IsCompleted()){
            delete toDestStrategy;
            toDestStrategy = NULL;
            available = true;
        }
    }
    
}

void Car::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}
