#include "servicecenterdatabase.h"

#include <fstream>
#include <iostream>
#include <limits>

ServiceCenterDatabase::ServiceCenterDatabase(QObject* parent)
    : QObject(parent), nextCode(1) {
    loadFromFile(); // Load data from file at startup
}

ServiceCenterDatabase::~ServiceCenterDatabase() {
    saveToFile(); // Save data to file on exit
}

MalfunctionType& ServiceCenterDatabase::addMalfunctionType(int modelCode, const QString& description,
                                                           const QString& symptoms, const QString& repairMethods,
                                                           int sparePart1, int sparePart2, int sparePart3,
                                                           double laborCost) {
    MalfunctionType newType;
    newType.setCode(generateCode());
    newType.setModelCode(modelCode);
    newType.setDescription(description);
    newType.setSymptoms(symptoms);
    newType.setRepairMethods(repairMethods);
    newType.setSparePart1Code(sparePart1);
    newType.setSparePart2Code(sparePart2);
    newType.setSparePart3Code(sparePart3);
    newType.setLaborCost(laborCost);

    malfunctionTypes.push_back(newType);
    saveToFile(); // Save to file after adding
    return malfunctionTypes.back();
}

const MalfunctionType& ServiceCenterDatabase::getMalfunctionType(int code) const {
    for (const auto& type : malfunctionTypes) {
        if (type.getCode() == code) return type;
    }
    throw std::runtime_error("Malfunction type not found.");
}

void ServiceCenterDatabase::deleteMalfunctionType(int code) {
    auto it = std::remove_if(malfunctionTypes.begin(), malfunctionTypes.end(),
                             [code](const MalfunctionType& type) { return type.getCode() == code; });
    if (it != malfunctionTypes.end()) {
        malfunctionTypes.erase(it, malfunctionTypes.end());
        saveToFile(); // Save to file after deletion
    } else {
        throw std::runtime_error("Malfunction type not found.");
    }
}

void ServiceCenterDatabase::displayAll() const {
    for (const auto& type : malfunctionTypes) {
        type.display();
    }
}

MalfunctionType& ServiceCenterDatabase::updateMalfunctionType(int code, int newModelCode, const QString& newDescription,
                                                  const QString& newSymptoms, const QString& newRepairMethods,
                                                  int newSparePart1, int newSparePart2, int newSparePart3,
                                                  double newLaborCost) {
    for (auto& type : malfunctionTypes) {
        if (type.getCode() == code) {
            // Update the fields with new values
            type.setModelCode(newModelCode);
            type.setDescription(newDescription);
            type.setSymptoms(newSymptoms);
            type.setRepairMethods(newRepairMethods);
            type.setSparePart1Code(newSparePart1);
            type.setSparePart2Code(newSparePart2);
            type.setSparePart3Code(newSparePart3);
            type.setLaborCost(newLaborCost);

            saveToFile();  // Save changes to file
            return type;
        }
    }
    throw std::runtime_error("Malfunction type not found.");
}

QVector<MalfunctionType> ServiceCenterDatabase::getMalfunctionTypes() const {
    return malfunctionTypes;
}

void ServiceCenterDatabase::saveToFile() const {
    std::ofstream outFile("malfunction_types.txt");
    if (!outFile) {
        std::cerr << "Could not open file for saving." << std::endl;
        return;
    }
    for (const auto& type : malfunctionTypes) {
        outFile << type.getCode() << "\n" << type.getModelCode() << "\n"
                << type.getDescription().toStdString() << "\n"
                << type.getSymptoms().toStdString() << "\n"
                << type.getRepairMethods().toStdString() << "\n"
                << type.getSparePart1Code() << "\n"
                << type.getSparePart2Code() << "\n"
                << type.getSparePart3Code() << "\n"
                << type.getLaborCost() << "\n";
    }
}

void ServiceCenterDatabase::loadFromFile() {
    std::ifstream inFile("malfunction_types.txt");
    if (!inFile) {
        std::cerr << "Could not open file for loading. Starting with empty database." << std::endl;
        return;
    }
    int code, modelCode, sparePart1, sparePart2, sparePart3;
    double laborCost;
    std::string description, symptoms, repairMethods;

    while (inFile >> code >> modelCode) {
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(inFile, description);
        std::getline(inFile, symptoms);
        std::getline(inFile, repairMethods);
        inFile >> sparePart1 >> sparePart2 >> sparePart3 >> laborCost;
        inFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        QString qDescription = QString::fromStdString(description);
        QString qSymptoms = QString::fromStdString(symptoms);
        QString qRepairMethods = QString::fromStdString(repairMethods);

        malfunctionTypes.emplace_back();
        malfunctionTypes.back().setCode(code);
        malfunctionTypes.back().setModelCode(modelCode);
        malfunctionTypes.back().setDescription(qDescription);
        malfunctionTypes.back().setSymptoms(qSymptoms);
        malfunctionTypes.back().setRepairMethods(qRepairMethods);
        malfunctionTypes.back().setSparePart1Code(sparePart1);
        malfunctionTypes.back().setSparePart2Code(sparePart2);
        malfunctionTypes.back().setSparePart3Code(sparePart3);
        malfunctionTypes.back().setLaborCost(laborCost);

        nextCode = std::max(nextCode, code + 1); // Keep next code updated
    }
}

int ServiceCenterDatabase::generateCode() {
    return nextCode++;
}
