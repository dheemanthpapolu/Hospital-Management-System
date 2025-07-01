#include "Billing.h"
#include <iostream>
#include <iomanip>

void Billing::dischargePatient(Patient* patient) {
    if (!patient->isReadyForDischarge()) {
        std::cout << "Patient is not marked for discharge.\n";
        return;
    }

    std::cout << "Discharging patient ID " << patient->getID() << ", Name: " << patient->getName() << "\n";
    generateBill(patient);
}

void Billing::generateBill(Patient* patient) {
    double baseCost = 1000.0;
    double doctorFee = 500.0;
    double medication = 300.0;
    double roomCharge = 200.0 * 3; // Assuming 3-day stay

    double total = baseCost + doctorFee + medication + roomCharge;

    std::cout << "--- Final Bill ---\n";
    std::cout << "Patient Name: " << patient->getName() << "\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Base Cost:      $" << baseCost << "\n";
    std::cout << "Doctor Fee:     $" << doctorFee << "\n";
    std::cout << "Medication:     $" << medication << "\n";
    std::cout << "Room Charges:   $" << roomCharge << "\n";
    std::cout << "------------------------\n";
    std::cout << "Total:          $" << total << "\n";
}

void Billing::addToBillingQueue(Patient* patient) {
    billingQueue.push(patient);
}

bool Billing::hasPendingBills() const {
    return !billingQueue.empty();
}

void Billing::processNextBill() {
    if (billingQueue.empty()) {
        std::cout << "No pending bills to process.\n";
        return;
    }

    Patient* patient = billingQueue.front();
    billingQueue.pop();

    if (!patient->isReadyForDischarge()) {
        std::cout << "Patient is not ready for discharge.\n";
        return;
    }

    std::cout << "Processing bill for patient ID " << patient->getID() << ", Name: " << patient->getName() << "\n";
    generateBill(patient);
    dischargePatient(patient);
}

void Billing::clearBillingQueue() {
    while (!billingQueue.empty()) {
        delete billingQueue.front();
        billingQueue.pop();
    }
}

void Billing::showPendingBills() const {
    if (billingQueue.empty()) {
        std::cout << "No pending bills.\n";
        return;
    }

    std::cout << "--- Pending Bills ---\n";
    
    std::queue<Patient*> tempQueue = billingQueue; // Copy to preserve original

    while (!tempQueue.empty()) {
        Patient* p = tempQueue.front();
        tempQueue.pop();
        std::cout << "Patient ID: " << p->getID()
                  << ", Name: " << p->getName() << "\n";
    }

    std::cout << "----------------------\n";
}

