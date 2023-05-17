#include "DataCollector.h"

DataCollector* DataCollector::instance_ = nullptr;

DataCollector *DataCollector::GetInstance() {
    if (instance_ == nullptr) {
        instance_ = new DataCollector();
    }
    return instance_;
}

DataCollector::~DataCollector() { }

void DataCollector::NewDroneRecord(int id, std::string name) {
    drones[id].name = name;
    drones[id].total_dist = 0.0;
    drones[id].trip_dist = 0.0;
    drones[id].total_time = 0;
    drones[id].trip_time = 0;
    drones[id].num_trips = 0;
}

void DataCollector::UpdateTime(Drone *d, double dt) {
    int id = d->GetId();
    drones[id].total_time += dt;
    if (!d->GetAvailability()) {
        drones[id].active_time += dt;
        if (d->HasPickup()) {
            drones[id].trip_time += dt;
            drones[id].cur_trip.trip_time += dt;
        } else {
            drones[id].cur_trip.wait_time += dt;
        }
    }
}

void DataCollector::UpdateDist(Drone *d, double dist) {
    int id = d->GetId();
    drones[id].total_dist += dist;
    if (d->HasPickup()) {
        drones[id].trip_dist += dist;
        drones[id].cur_trip.trip_dist += dist;
    }
}

void DataCollector::BeginTrip(Drone *d, IEntity* e) {
    int id = d->GetId();
    drones[id].cur_trip.name = e->GetName();
    drones[id].cur_trip.drone_id = id;
    drones[id].cur_trip.wait_time = 0.0;
    drones[id].cur_trip.trip_time = 0.0;
    drones[id].cur_trip.trip_dist = 0.0;
}

void DataCollector::FinishTrip(Drone *d) {
    int id = d->GetId();
    drones[id].num_trips++;
    trips.push_back(drones[id].cur_trip);
}

void DataCollector::WriteLog() {
    std::time_t time = std::time(0);
    std::tm *now = std::localtime(&time);

    char file_name[100];
    sprintf(file_name, "logs/log_%04d_%02d_%02dT%02d_%02d_%02d.json",
        now->tm_year + 1900,
        now->tm_mon + 1,
        now->tm_mday,
        now->tm_hour,
        now->tm_min,
        now->tm_sec);

    std::ofstream my_file;
    my_file.open(file_name);

    my_file << '{' << std::endl << "    \"trips\":[";

    int n = trips.size();
    double sum_wait = 0.0;
    double min_wait = n ? trips[0].wait_time : 0.0;
    double max_wait = 0.0;

    for (int i = 0; i < n; i++) {
        if (i) my_file << ',';
        my_file << std::endl
                << "        {" << std::endl
                << "            \"name\":\""    << trips[i].name
                << "\"," << std::endl
                << "            \"drone_id\":"  << trips[i].drone_id
                << ','   << std::endl
                << "            \"wait_time\":" << trips[i].wait_time
                << ','   << std::endl
                << "            \"trip_time\":" << trips[i].trip_time
                << ','   << std::endl
                << "            \"trip_dist\":"
                << trips[i].trip_dist          << std::endl
                << "        }";

        sum_wait += trips[i].wait_time;
        min_wait = std::min(min_wait, trips[i].wait_time);
        max_wait = std::max(max_wait, trips[i].wait_time);
    }

    my_file << std::endl << "    ]," << std::endl
                         << "    \"trip_count\":" << n << ',' << std::endl
                         << "    \"avg_wait\":"   << (n ? sum_wait/n : 0)
                         << ',' << std::endl
                         << "    \"min_wait\":"   << min_wait << ','
                         << std::endl
                         << "    \"max_wait\":"   << max_wait << ','
                         << std::endl
                         << "    \"drones\":[";

    double sum_lifetime = 0.0;
    double sum_activity = 0.0;

    for (std::map<int,
         DroneRecord>::iterator it = drones.begin(); it != drones.end(); it++) {
        if (it != drones.begin()) my_file << ',';
        my_file << std::endl
          << "        {" << std::endl
          << "            \"id\":" << it->first << ",\n"
          << "            \"name\":\"" << it->second.name << "\",\n"
          << "            \"total_dist\":" << it->second.total_dist << ",\n"
          << "            \"trip_dist\":" << it->second.trip_dist << ",\n"
          << "            \"total_time\":" << it->second.total_time << ",\n"
          << "            \"active_time\":" << it->second.active_time << ",\n"
          << "            \"trip_time\":" << it->second.trip_time << ",\n"
          << "            \"num_trips\":" << it->second.num_trips << std::endl
          << "        }";

        sum_lifetime += it->second.total_time;
        sum_activity += it->second.active_time;
    }

    if (sum_lifetime)
        sum_activity /= sum_lifetime;

    my_file << std::endl << "    ]," << std::endl
                         << "    \"drone_count\":" << drones.size() << ",\n"
                         << "    \"time_active_ratio\":" << sum_activity
                         << std::endl << '}' << std::endl;

    my_file.close();
}
