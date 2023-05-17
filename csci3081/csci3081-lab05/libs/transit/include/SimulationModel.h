#ifndef SIMULATION_MODEL_H_
#define SIMULATION_MODEL_H_

#include "IController.h"
#include "Drone.h"
#include "IEntity.h"
#include "graph.h"
#include "Robot.h"
using namespace routing;

//--------------------  Model ----------------------------

/**
 * @brief
 * Simulation Model handling the transit simulation.  The model can communicate
 * with the controller.
 */
class SimulationModel {
 public:
  /**
   * @brief Constructor for creating a SimulationModel object
   * @param[in] controller The controller to create the SimulationModel with
   */
  SimulationModel(IController& controller);

  /**
   * @brief Sets the graph of this SimulationModel object
   * @param[in] graph The graph to set for this SimulationModel object
   */
  void SetGraph(const IGraph* graph) { this->graph = graph; }

  /**
   * @param[in] entity The data to create the new entity from
   */
  void CreateEntity(JsonObject& entity);

  /**
   * @brief Schedules a trip for an object in the scene
   * @param[in] details The details to schedule the trip with
   */
  void ScheduleTrip(JsonObject& details);

  /**
   * @brief Updates the simulation
   * @param[in] dt The time step to use
   */
  void Update(double dt);

 protected:
  IController& controller;
  std::vector<IEntity*> entities;
  std::vector<IEntity*> scheduler;
  const IGraph* graph;
};

#endif
