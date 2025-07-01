#include "Patient.h"
#include "Doctor.h"
#include <sstream>

Patient::Patient(int id, const std::string& name, int age,
                 const std::vector<std::string>& pastIllnesses,
                 const std::vector<std::string>& currentSymptoms,
                 int severityScore)
    : id(id), name(name), age(age),
      pastIllnesses(pastIllnesses),
      currentSymptoms(currentSymptoms),
      severityScore(severityScore),
      readyForDischarge(false),
      assignedDoctor(nullptr) {}

int Patient::getID() const {
    return id;
}

int Patient::getAge() const {
    return age;
}

std::string Patient::getName() const {
    return name;
}

int Patient::getSeverityScore() const {
    return severityScore;
}

void Patient::addNotes(const std::string& note) {
    notes += note + "\n";
}

void Patient::markForDischarge() {
    readyForDischarge = true;
}

bool Patient::isReadyForDischarge() const {
    return readyForDischarge;
}

void Patient::setAssignedDoctor(Doctor* d) {
    assignedDoctor = d;
}

Doctor* Patient::getAssignedDoctor() const {
    return assignedDoctor;
}

std::string Patient::getSummary() const {
    std::ostringstream oss;
    oss << "Patient ID: " << id << "\n"
        << "Name: " << name << "\n"
        << "Age: " << age << "\n"
        << "Emergency Score: " << emergencyScore << "\n"
        << "Assigned Doctor: " << (assignedDoctor ? assignedDoctor->getName() : "None") << "\n"
        << "Notes: " << notes;
    return oss.str();
}

void Patient::setEmergencyScore(int score) {
    emergencyScore = score;
}

const std::vector<std::string>& Patient::getPastIllnesses() const {
    return pastIllnesses;
}

const std::vector<std::string>& Patient::getCurrentSymptoms() const {
    return currentSymptoms;
}
