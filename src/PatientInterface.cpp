#include "PatientInterface.h"
#include <iostream>
#include <limits>

Patient* PatientInterface::registerPatient(int id) {
    std::string name;
    int age;
    int score;

    std::cout << "Enter patient's name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Enter patient's age: ";
    std::cin >> age;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::vector<std::string> pastIllnesses;
    std::cout << "Enter past illnesses (comma-separated): ";
    std::string pastInput;
    std::getline(std::cin, pastInput);
    size_t start = 0, end;
    while ((end = pastInput.find(',', start)) != std::string::npos) {
        pastIllnesses.push_back(pastInput.substr(start, end - start));
        start = end + 1;
    }
    if (!pastInput.empty()) {
        pastIllnesses.push_back(pastInput.substr(start));
    }

    std::vector<std::string> currentSymptoms;
    std::cout << "Enter current symptoms (comma-separated): ";
    std::string symptomInput;
    std::getline(std::cin, symptomInput);
    start = 0;
    while ((end = symptomInput.find(',', start)) != std::string::npos) {
        currentSymptoms.push_back(symptomInput.substr(start, end - start));
        start = end + 1;
    }
    if (!symptomInput.empty()) {
        currentSymptoms.push_back(symptomInput.substr(start));
    }

    Patient* p = new Patient(id, name, age, pastIllnesses, currentSymptoms, score);
    std::cout << "Patient registered with ID: " << p->getID() << "\n";
    return p;
}
