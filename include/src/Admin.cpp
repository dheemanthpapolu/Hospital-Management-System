#include "Admin.h"
#include <iostream>
#include <limits>
#include <queue>

Admin::Admin() : id(0), name("Default Admin") {}

Admin::Admin(int id, const std::string& name) : id(id), name(name) {}

int Admin::getID() const {
    return id;
}

std::string Admin::getName() const {
    return name;
}


void Admin::admitPatient(std::priority_queue<Patient*, std::vector<Patient*>, Patient::ComparePriority>& triageQueue,
                         std::vector<Department*>& departments) {
    if (triageQueue.empty()) {
        std::cout << "No patients waiting in triage queue.\n";
        return;
    }

    Patient* p = triageQueue.top();
    triageQueue.pop();

    std::cout << "Admitting patient: \n" << p->getSummary() << "\n";

    std::cout << "Select department to admit to:\n";
    for (size_t i = 0; i < departments.size(); ++i) {
        std::cout << i + 1 << ". " << departments[i]->getName() << "\n";
    }

    int choice;
    while (true) {
        std::cout << "Enter choice: ";
        std::cin >> choice;
        if (choice >= 1 && choice <= (int)departments.size()) break;
        std::cout << "Invalid choice. Try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    Department* dept = departments[choice - 1];

    if (dept->getDoctors().empty()) {
        std::cout << "No doctors available in this department.\n";
        return;
    }

    Doctor* assignedDoctor = dept->getDoctors()[0];
    for (auto doctor : dept->getDoctors()) {
        if (doctor->getPatientCount() < assignedDoctor->getPatientCount()) {
            assignedDoctor = doctor;
        }
    }

    assignedDoctor->assignPatient(p);
    p->setAssignedDoctor(assignedDoctor);
    dept->addPatient(p);

    std::cout << "Patient admitted to " << dept->getName()
              << " under " << assignedDoctor->getName() << "\n";
}

void Admin::viewAllBeds(const std::vector<Department*>& departments) const {
    std::cout << "--- Bed Availability ---\n";
    for (const auto& dept : departments) {
        std::cout << dept->getName() << ": " << dept->getAvailableBeds() << " beds available\n";
    }
}

void Admin::viewAllPatients(const std::vector<Department*>& departments) const {
    std::cout << "--- All Patients in Hospital ---\n";
    for (const auto& dept : departments) {
        std::cout << "Department: " << dept->getName() << "\n";
        for (const auto& patient : dept->getPatients()) {
            std::cout << "ID: " << patient->getID()
                      << ", Name: " << patient->getName() << "\n";
        }
        std::cout << "--------------------------\n";
    }
}
