#include "Doctor.h"
#include <iostream>

Doctor::Doctor(int id, const std::string& name, const std::string& department)
    : id(id), name(name), department(department) {}

std::string Doctor::getName() const {
    return name;
}

std::string Doctor::getDepartment() const {
    return department;
}

int Doctor::getPatientCount() const {
    return assignedPatients.size();
}

void Doctor::assignPatient(Patient* patient) {
    assignedPatients.push_back(patient);
}

std::vector<Patient*>& Doctor::getPatients() {
    return assignedPatients;
}

void Doctor::viewPatients() const {
    std::cout << "--- Patients Assigned to Dr. " << name << " ---\n";
    for (auto* p : assignedPatients) {
        std::cout << p->getSummary() << "\n------------------------\n";
    }
}

void Doctor::addNotes(int patientID, const std::string& note) {
    for (auto* p : assignedPatients) {
        if (p->getID() == patientID) {
            p->addNotes(note);
            std::cout << "Note added.\n";
            return;
        }
    }
    std::cout << "Patient not found.\n";
}

void Doctor::markPatientForDischarge(int patientID) {
    for (auto* p : assignedPatients) {
        if (p->getID() == patientID) {
            p->markForDischarge();
            std::cout << "Patient marked for discharge.\n";
            return;
        }
    }
    std::cout << "Patient not found.\n";
}

int Doctor::getID() const {
    return id;
}
