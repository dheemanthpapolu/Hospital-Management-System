#ifndef HOSPITAL_H
#define HOSPITAL_H

#include "Patient.h"
#include "Doctor.h"
#include "Department.h"
#include "Admin.h"
#include "Billing.h"
#include "PatientInterface.h"

#include <vector>
#include <queue>

class Hospital {
private:
    std::vector<Doctor*> doctors;
    std::vector<Admin*> admins;
    std::vector<Department*> departments;

    // Patients waiting for emergency score assignment
    std::vector<Patient*> pendingPatients;

    // Triage queue - Patients with emergency score assigned
    std::priority_queue<Patient*, std::vector<Patient*>, Patient::ComparePriority> triageQueue;

    Billing billing;

    int idCounter = 1000;  // Patient ID generator

public:

    void patientFlow();       // Patient registration
    void adminLogin();        // Admin menu
    void billingClerk();      // Billing menu
    void doctorLogin();       // Doctor menu

    Hospital();
    ~Hospital();
    void adminAssignEmergencyScores();
    void run();               // Main driver function
};

#endif
