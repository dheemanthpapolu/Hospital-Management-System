#ifndef BILLING_H
#define BILLING_H

#include "Patient.h"
#include <vector>
#include <queue>

class Billing {
private:
    std::queue<Patient*> billingQueue;

public:
    void addToBillingQueue(Patient* patient);
    bool hasPendingBills() const;
    void processNextBill();
    void clearBillingQueue(); // Add this
    static void dischargePatient(Patient* patient);
    static void generateBill(Patient* patient);
    void showPendingBills() const;
};

#endif
