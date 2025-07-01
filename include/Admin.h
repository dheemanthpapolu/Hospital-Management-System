#ifndef ADMIN_H
#define ADMIN_H

#include "Patient.h"
#include "Department.h"
#include <vector>
#include <queue>

class Admin {
private:
    int id;
    std::string name;

public:
    Admin();
    Admin(int id, const std::string& name);

    int getID() const;
    std::string getName() const;

    void assignEmergencyScores(std::vector<Patient*>& waitingList,
        std::priority_queue<Patient*, std::vector<Patient*>, Patient::ComparePriority>& triageQueue);

    void admitPatient(std::priority_queue<Patient*, std::vector<Patient*>, Patient::ComparePriority>& triageQueue,
                      std::vector<Department*>& departments);

    void viewAllBeds(const std::vector<Department*>& departments) const;
    void viewAllPatients(const std::vector<Department*>& departments) const;
};

#endif
