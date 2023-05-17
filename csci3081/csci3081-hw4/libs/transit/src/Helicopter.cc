#define _USE_MATH_DEFINES
#include "Helicopter.h"
#include "BeelineStrategy.h"

#include <cmath>
#include <limits>

Helicopter::Helicopter(JsonObject& obj) : details(obj) {
    JsonArray pos(obj["position"]);
    position = {pos[0], pos[1], pos[2]};

    JsonArray dir(obj["direction"]);
    direction = {dir[0], dir[1], dir[2]};

    speed = obj["speed"];

    std::string temp = obj["name"];
    name = temp;

    available = true;
}

Helicopter::~Helicopter(){
    // ...
}

int Helicopter::GetRandomNum(int min, int max){
    return (rand() % (max - min + 1) + min);
}

Vector3 Helicopter::GetRandDest(){
    float x = (float) GetRandomNum(-1400, 1500);
    float y = (float) GetRandomNum(300, 1000);
    float z = (float) GetRandomNum(-800, 800);
    return {x, y, z};
}

void Helicopter::Update(double dt, std::vector<IEntity*> scheduler){
    
    if(available){
        destination = GetRandDest();       // Get Random Destination.
        toDestStrategy = new BeelineStrategy(position, destination);
        available = false;
    }

    // If the Helicopter has a destination...
    if(toDestStrategy){
        // Move the Helicopter
        toDestStrategy->Move(this, dt);

        // Once the Helicopter arrives at the destination...
        if(toDestStrategy->IsCompleted()){
            delete toDestStrategy;
            toDestStrategy = NULL;
            available = true;
        }
    }
    
}

void Helicopter::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}
