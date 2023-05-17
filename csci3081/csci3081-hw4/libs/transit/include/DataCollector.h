#ifndef CSCI_3081W_F22_HW4_LIBS_TRANSIT_INCLUDE_DATACOLLECTOR_H_
#define CSCI_3081W_F22_HW4_LIBS_TRANSIT_INCLUDE_DATACOLLECTOR_H_

#include "Drone.h"
#include <iostream>
#include <fstream>
#include <ctime>

/**
 * @brief This class is to collect data for trips and drones.
 */
class DataCollector {
    /** @struct TripRecord
     *  This is a struct
     *
     *  @var TripRecord::name
     *    Name of the trip.
     *  @var TripRecord::drone_id
     *    Id of the drone for the trip.
     *  @var TripRecord::wait_time
     *    Wait time of the trip.
     *  @var TripRecord::trip_time
     *    Trip time for the trip.
     *  @var TripRecord::trip_dist
     *    Distance of the trip.
     */
    typedef struct {
      std::string name;
      int drone_id;
      double wait_time;
      double trip_time;
      double trip_dist;
    } TripRecord;

    /** @struct DroneRecord
     *  This is a struct
     *
     *  @var DroneRecord::name
     *    Name of the drone.
     *  @var DroneRecord::total_dist
     *    Total distance travelled by the drone.
     *  @var DroneRecord::trip_dist
     *    Trip distance of the drone.
     *  @var DroneRecord::total_time
     *    Total time of the drone.
     *  @var DroneRecord::active_time
     *    Active time of the drone.
     *  @var DroneRecord::trip_time
     *    Trip time of the drone.
     *  @var DroneRecord::num_trips
     *    Number of trips of the drone.
     *  @var DroneRecord::cur_trip
     *    Current trip of the drone.
     */
    typedef struct {
        std::string name;
        double total_dist;
        double trip_dist;
        double total_time;
        double active_time;
        double trip_time;
        int num_trips;
        TripRecord cur_trip;
    } DroneRecord;

 protected:
    /**
     * @brief Default Constructor.
     */
    DataCollector() {}

    /**
     * @brief Destructor.
     */
    ~DataCollector();

    /**
     * @brief Get the instance collected data.
     * @return The pointer to the instance collected data.
     */
    static DataCollector* instance_;

    /**
     * @brief Get trips.
     * @return The vector to the trips.
     */
    std::vector<TripRecord> trips;

    /**
     * @brief Get the drones.
     * @return The vector to the drones.
     */
    std::map<int, DroneRecord> drones;

 public:
    DataCollector(DataCollector &other) = delete;

    void operator=(const DataCollector &other) = delete;

    /**
     * @brief Get instance data collector.
     * @return The instance of the collected data.
     */
    static DataCollector *GetInstance();

    /**
     * @brief Record new drone.
     * @param[in] id The id of the new drone would like to be recorded.
     * @param[in] name The name of the new drone would like to be recorded.
     */
    void NewDroneRecord(int id, std::string name);

    /**
     * @brief Update time.
     * @param[in] d The pointer to the drone.
     * @param[in] dt Delta time.
     */
    void UpdateTime(Drone *d, double dt);

    /**
     * @brief Update distance.
     * @param[in] d The drone that would like to update distance.
     * @param[in] dist The distance would like to be updated.
     */
    void UpdateDist(Drone *d, double dist);

    /**
     * @brief Begin trips.
     * @param[in] d The pointer to the drone begins the trip.
     * @param[in] e The pointer to the entity begins the trip.
     */
    void BeginTrip(Drone *d, IEntity *e);

    /**
     * @brief Finish trip.
     * @param[in] d The pointer to the drone that finished trip.
     */
    void FinishTrip(Drone *d);

    /**
     * @brief Write down collected data.
     */
    void WriteLog();
};

#endif  // CSCI_3081W_F22_HW4_LIBS_TRANSIT_INCLUDE_DATACOLLECTOR_H_

