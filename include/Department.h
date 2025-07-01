// Department.h
#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <string>
#include <vector>
#include "Doctor.h"
#include "Patient.h"

class Department {
private:
    std::string name;
    int totalBeds;
    std::vector<Doctor*> doctors;
    std::vector<Patient*> patients;

public:
    Department(const std::string& name, int bedCount);

    std::string getName() const;
    int getAvailableBeds() const;

    void addDoctor(Doctor* d);
    void addPatient(Patient* p);

    const std::vector<Doctor*>& getDoctors() const;
    const std::vector<Patient*>& getPatients() const;
};

#endif // DEPARTMENT_H
