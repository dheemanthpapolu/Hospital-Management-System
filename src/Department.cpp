// Department.cpp
#include "Department.h"

Department::Department(const std::string& name, int bedCount)
    : name(name), totalBeds(bedCount) {}

std::string Department::getName() const {
    return name;
}

int Department::getAvailableBeds() const {
    return totalBeds - patients.size();
}

void Department::addDoctor(Doctor* d) {
    doctors.push_back(d);
}

void Department::addPatient(Patient* p) {
    patients.push_back(p);
}

const std::vector<Doctor*>& Department::getDoctors() const {
    return doctors;
}

const std::vector<Patient*>& Department::getPatients() const {
    return patients;
}
