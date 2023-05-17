#define _USE_MATH_DEFINES
#include "Ufo.h"
#include "BeelineStrategy.h"

#include <cmath>
#include <limits>

Ufo::Ufo(JsonObject& obj) : details(obj) {
    JsonArray pos(obj["position"]);
    position = {pos[0], pos[1], pos[2]};

    JsonArray dir(obj["direction"]);
    direction = {dir[0], dir[1], dir[2]};

    speed = obj["speed"];

    std::string temp = obj["name"];
    name = temp;

    available = true;
}

Ufo::~Ufo(){
    // ...
}

int Ufo::GetRandomNum(int min, int max){
    return (rand() % (max - min + 1) + min);
}

Vector3 Ufo::GetRandDest(){
    float x = (float) GetRandomNum(-1400, 1500);
    float y = 400.0; //(float) GetRandomNum(400, 1000);
    float z = (float) GetRandomNum(-800, 800);
    return {x, y, z};
}

void Ufo::Update(double dt, std::vector<IEntity*> scheduler){
    
    if(available){
        destination = GetRandDest();       // Get Random Destination.
        toDestStrategy = new BeelineStrategy(position, destination);
        available = false;
    }

    // If the Ufo has a destination...
    if(toDestStrategy){
        // Move the Ufo
        toDestStrategy->Move(this, dt);

        // Once the Ufo arrives at the destination...
        if(toDestStrategy->IsCompleted()){
            delete toDestStrategy;
            toDestStrategy = NULL;
            available = true;
        }
    }
    
}

void Ufo::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}
