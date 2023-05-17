#ifndef CSCI_3081W_F22_HW4_LIBS_TRANSIT_INCLUDE_SIMULATIONMODEL_H_
#define CSCI_3081W_F22_HW4_LIBS_TRANSIT_INCLUDE_SIMULATIONMODEL_H_

#include "IController.h"
#include "CompositeFactory.h"
#include "IEntity.h"
#include "graph.h"
using namespace routing;

//--------------------  Model ----------------------------
/**
 * @brief Simulation Model handling the transit simulation.
 * The model can communicate with the controller.
 */
class SimulationModel {
 public:
  /**
   * @brief Parameter constructor.
   *
   * @param[in] controller communicated controller
   */
  SimulationModel(IController& controller);

  /**
   * @brief Set graph.
   *
   * @param[in] graph The graph to be set.
   */
  void SetGraph(const IGraph* graph) { this->graph = graph; }

  /**
   * @brief Creates an simulation entity.
   * @param[in] entity Entity created in the simulation.
   */
  void CreateEntity(JsonObject& entity);

  /**
   * @brief Creates multiple simulation entities.
   * @param[in] entities Entities to create in the simulation.
   */
  void CreateEntities(JsonObject& entities);

  /**
   * @brief Schedules a trip for an object in the scene.
   * @param[in] details Details of the trip scheduled.
   */
  void ScheduleTrip(JsonObject& details);

  /**
   * @brief Updates the simulation.
   * @param[in] dt Delta time.
   */
  void Update(double dt);

  /**
   * @brief Adds a new entity type.
   * @param[in] factory The new type entity factory.
   */
  void AddFactory(IEntityFactory* factory);

 protected:
  IController& controller;
  std::vector<IEntity*> entities;
  std::vector<IEntity*> scheduler;
  const IGraph* graph;
  CompositeFactory* compFactory;
};

#endif  // CSCI_3081W_F22_HW4_LIBS_TRANSIT_INCLUDE_SIMULATIONMODEL_H_
