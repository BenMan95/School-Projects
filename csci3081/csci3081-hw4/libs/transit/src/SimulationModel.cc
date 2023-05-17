#include "SimulationModel.h"
#include "DroneFactory.h"
#include "RobotFactory.h"
#include "CarFactory.h"
#include "HelicopterFactory.h"
#include "UfoFactory.h"
#include "DataCollector.h"
#include <cmath>

SimulationModel::SimulationModel(IController& controller)
    : controller(controller) {
  compFactory = new CompositeFactory();
  AddFactory(new DroneFactory());
  AddFactory(new RobotFactory());
  AddFactory(new CarFactory());
  AddFactory(new HelicopterFactory());
  AddFactory(new UfoFactory());}

void SimulationModel::CreateEntity(JsonObject& entity) {
  DataCollector *s = DataCollector::GetInstance();
  std::string type = entity["type"];
  std::string name = entity["name"];
  JsonArray position = entity["position"];
  std::cout << name << ": " << position << std::endl;

  IEntity* myNewEntity = compFactory->CreateEntity(entity);
  myNewEntity->SetGraph(graph);

  if (type.compare("drone") == 0) {
    s->NewDroneRecord(myNewEntity->GetId(), name);
  }

  // Call AddEntity to add it to the view
  controller.AddEntity(*myNewEntity);
  entities.push_back(myNewEntity);
}

int GetRandomNum(int min, int max) {
    return (rand() % (max - min + 1) + min);
}

void SimulationModel::CreateEntities(JsonObject& entities) {
  int n = entities["count"];
  JsonArray xr(entities["xrange"]);
  JsonArray yr(entities["yrange"]);
  JsonArray zr(entities["zrange"]);
  for (int i = 0; i < n; i++) {
    float x = (float) GetRandomNum(xr[0], xr[1]);
    float y = (float) GetRandomNum(yr[0], yr[1]);
    float z = (float) GetRandomNum(zr[0], zr[1]);
    JsonArray pos = {x, y, z};
    entities["position"] = pos;
    CreateEntity(entities);
  }
}

/// Schedules a trip for an object in the scene
void SimulationModel::ScheduleTrip(JsonObject& details) {
  std::string name = details["name"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];
  std::cout << name << ": " << start << " --> " << end << std::endl;

  for (auto entity : entities) {  // Add the entity to the scheduler
    JsonObject detailsTemp = entity->GetDetails();
    std::string nameTemp = detailsTemp["name"];
    std::string typeTemp = detailsTemp["type"];
    if (name.compare(nameTemp) == 0 && typeTemp.compare("robot")
        == 0 && entity->GetAvailability()) {
      std::string strategyName = details["search"];
      entity->SetStrategyName(strategyName);
      entity->SetDestination(Vector3(end[0], end[1], end[2]));
      scheduler.push_back(entity);
      break;
    }
  }
  controller.SendEventToView("TripScheduled", details);
}

/// Updates the simulation
void SimulationModel::Update(double dt) {
  for (int i = 0; i < entities.size(); i++) {
    entities[i]->Update(dt, scheduler);
    controller.UpdateEntity(*entities[i]);
  }
}

void SimulationModel::AddFactory(IEntityFactory* factory) {
  compFactory->AddFactory(factory);
}
