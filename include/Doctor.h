#ifndef DOCTOR_H
#define DOCTOR_H

#include "Patient.h"
#include <string>
#include <vector>

class Doctor {
private:
    int id;
    std::string name;
    std::string department;
    std::vector<Patient*> assignedPatients;

public:
    Doctor(int id, const std::string& name, const std::string& department);
    int getID() const;
    std::string getName() const;
    std::string getDepartment() const;
    int getPatientCount() const;

    void assignPatient(Patient* patient);
    void viewPatients() const;
    void addNotes(int patientID, const std::string& note);
    void markPatientForDischarge(int patientID);
    std::vector<Patient*>& getPatients();
};

#endif
