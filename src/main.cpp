#include "Hospital.h"
#include <iostream>

int main() {
    Hospital hospital;
    int choice;

    while (true) {
        std::cout << "\n=== Hospital Management System ===\n";
        std::cout << "1. Patient\n";
        std::cout << "2. Admin\n";
        std::cout << "3. Billing Clerk\n";
        std::cout << "4. Doctor\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                hospital.patientFlow();
                break;
            case 2:
                hospital.adminLogin();
                break;
            case 3:
                hospital.billingClerk();
                break;
            case 4:
                hospital.doctorLogin();
                break;
            case 5:
                std::cout << "Exiting system...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
