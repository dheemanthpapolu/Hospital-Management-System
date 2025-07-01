#include "Hospital.h"
#include <iostream>
#include <limits>

Hospital::Hospital() {
    Department* cardiology = new Department("Cardiology", 10);
    Department* neurology = new Department("Neurology", 10);
    Department* orthopedics = new Department("Orthopedics", 10);

    Doctor* doc1 = new Doctor(101, "Dr. Kapoor", "Cardiology");
    Doctor* doc2 = new Doctor(102, "Dr. Bose", "Neurology");
    Doctor* doc3 = new Doctor(103, "Dr. Mehta", "Orthopedics");

    cardiology->addDoctor(doc1);
    neurology->addDoctor(doc2);
    orthopedics->addDoctor(doc3);

    departments.push_back(cardiology);
    departments.push_back(neurology);
    departments.push_back(orthopedics);

    doctors.push_back(doc1);
    doctors.push_back(doc2);
    doctors.push_back(doc3);

    admins.push_back(new Admin(1, "Super Admin"));
}

Hospital::~Hospital() {
    for (auto d : doctors) delete d;
    for (auto a : admins) delete a;
    for (auto dept : departments) delete dept;

    while (!triageQueue.empty()) {
        delete triageQueue.top();
        triageQueue.pop();
    }
    billing.clearBillingQueue();
}

void Hospital::run() {
    int choice;
    do {
        std::cout << "\nSelect User Type:\n";
        std::cout << "1. Patient\n2. Admin\n3. Billing Clerk\n4. Doctor\n5. Exit\nChoice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: patientFlow(); break;
            case 2: adminLogin(); break;
            case 3: billingClerk(); break;
            case 4: doctorLogin(); break;
            case 5: std::cout << "Exiting...\n"; break;
            default: std::cout << "Invalid choice.\n";
        }
    } while (choice != 5);
}

void Hospital::patientFlow() {
    Patient* p = PatientInterface::registerPatient(idCounter++);
    pendingPatients.push_back(p);
    std::cout << "Patient registered successfully.\n";
    std::cout << "Assigned ID: " << p->getID() << "\n";
}

void Hospital::adminLogin() {
    int choice;
    Admin* admin = admins[0];

    while (true) {
        std::cout << "\nAdmin Menu:\n";
        std::cout << "1. Assign Emergency Scores\n";
        std::cout << "2. Admit Patient\n";
        std::cout << "3. View All Beds\n";
        std::cout << "4. View All Patients\n";
        std::cout << "5. Logout\nChoice: ";
        std::cin >> choice;

        if (choice == 1) {
            if (pendingPatients.empty()) {
                std::cout << "No patients waiting for emergency score assignment.\n";
            } else {
                for (size_t i = 0; i < pendingPatients.size(); ++i) {
                    Patient* p = pendingPatients[i];
                    std::cout << "\nID: " << p->getID()
                              << ", Name: " << p->getName()
                              << ", Age: " << p->getAge()
                              << "\nSymptoms: ";
                    for (const auto& s : p->getCurrentSymptoms()) {
                        std::cout << s << " ";
                    }
                    std::cout << "\nPast Illnesses: ";
                    for (const auto& s : p->getPastIllnesses()) {
                        std::cout << s << " ";
                    }
                    std::cout << "\nEnter Emergency Score (1 - 10): ";
                    int score;
                    std::cin >> score;
                    p->setEmergencyScore(score);
                    triageQueue.push(p);
                }
                pendingPatients.clear();
            }
        } else if (choice == 2) {
            admin->admitPatient(triageQueue, departments);
        } else if (choice == 3) {
            admin->viewAllBeds(departments);
        } else if (choice == 4) {
            admin->viewAllPatients(departments);
        } else if (choice == 5) {
            break;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}

void Hospital::doctorLogin() {
    std::cout << "Available Doctors:\n";
    for (auto& doc : doctors) {
        std::cout << doc->getID() << " - " << doc->getDepartment() << " - Dr. " << doc->getName() << "\n";
    }

    int id;
    std::cout << "Enter your Doctor ID: ";
    std::cin >> id;

    Doctor* current = nullptr;
    for (auto d : doctors) {
        if (d->getID() == id) {
            current = d;
            break;
        }
    }

    if (!current) {
        std::cout << "Invalid ID.\n";
        return;
    }

    int choice;
    while (true) {
        std::cout << "\nDoctor Menu:\n1. View Patients\n2. Add Notes\n3. Mark for Discharge\n4. Logout\nChoice: ";
        std::cin >> choice;

        if (choice == 1) {
            current->viewPatients();
        } else if (choice == 2) {
            int pid;
            std::string note;
            std::cout << "Enter Patient ID: ";
            std::cin >> pid;
            std::cin.ignore();
            std::cout << "Enter Note: ";
            std::getline(std::cin, note);

            for (auto p : current->getPatients()) {
                if (p->getID() == pid) {
                    p->addNotes(note);
                    std::cout << "Note added.\n";
                    break;
                }
            }
        } else if (choice == 3) {
            int pid;
            std::cout << "Enter Patient ID to discharge: ";
            std::cin >> pid;

            for (auto p : current->getPatients()) {
                if (p->getID() == pid) {
                    p->markForDischarge();
                    billing.addToBillingQueue(p);
                    std::cout << "Marked for discharge and added to billing.\n";
                    break;
                }
            }
        } else if (choice == 4) {
            break;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}

void Hospital::billingClerk() {
    int choice;
    while (true) {
        std::cout << "\nBilling Clerk Menu:\n1. View Pending Bills\n2. Generate Next Bill\n3. Logout\nChoice: ";
        std::cin >> choice;

        if (choice == 1) {
            billing.showPendingBills();
        } else if (choice == 2) {
            if (billing.hasPendingBills()) {
                billing.processNextBill();
            } else {
                std::cout << "No pending bills to process.\n";
            }
        } else if (choice == 3) {
            break;
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
}


void Hospital::adminAssignEmergencyScores() {
    if (pendingPatients.empty()) {
        std::cout << "No patients awaiting emergency score.\n";
        return;
    }

    std::cout << "--- Assign Emergency Scores ---\n";
    for (int i = 0; i < (int)pendingPatients.size(); ++i) {
        Patient* p = pendingPatients[i];
        std::cout << "\nPatient " << i + 1 << ":\n";
        std::cout << "ID: " << p->getID() << "\n";
        std::cout << "Name: " << p->getName() << "\n";
        std::cout << "Age: " << p->getAge() << "\n";
        std::cout << "Past Illnesses: ";
        for (auto& illness : p->getPastIllnesses()) std::cout << illness << " ";
        std::cout << "\nCurrent Symptoms: ";
        for (const auto& symptom : p->getCurrentSymptoms()) std::cout << symptom << " ";
        std::cout << "\n";

        int score;
        std::cout << "Enter emergency score (1 - 10): ";
        std::cin >> score;
        p->setEmergencyScore(score);

        triageQueue.push(p); // Now eligible for admission
    }

    pendingPatients.clear(); // All have been assigned and moved to triage
}
