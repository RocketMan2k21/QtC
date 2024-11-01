#include "malfunctiontype.h"
#include <stdexcept>
#include <iostream>

// MalfunctionType.cpp
MalfunctionType::MalfunctionType()
    : mCode(-1), mModelCode(-1), mSparePart1Code(-1), mSparePart2Code(-1), mSparePart3Code(-1), mLaborCost(0.0) {}

void MalfunctionType::display() const {
    std::cout << "Malfunction Type: " << mCode << std::endl;
}

// Setters
void MalfunctionType::setCode(int code) { mCode = code; }
void MalfunctionType::setModelCode(int modelCode) { mModelCode = modelCode; }
void MalfunctionType::setDescription(const QString& description) { mDescription = description; }
void MalfunctionType::setSymptoms(const QString& symptoms) { mSymptoms = symptoms; }
void MalfunctionType::setRepairMethods(const QString& repairMethods) { mRepairMethods = repairMethods; }
void MalfunctionType::setSparePart1Code(int sparePartCode) { mSparePart1Code = sparePartCode; }
void MalfunctionType::setSparePart2Code(int sparePartCode) { mSparePart2Code = sparePartCode; }
void MalfunctionType::setSparePart3Code(int sparePartCode) { mSparePart3Code = sparePartCode; }
void MalfunctionType::setLaborCost(double laborCost) { mLaborCost = laborCost; }

// Getters
int MalfunctionType::getCode() const { return mCode; }
int MalfunctionType::getModelCode() const { return mModelCode; }
QString MalfunctionType::getDescription() const { return mDescription; }
QString MalfunctionType::getSymptoms() const { return mSymptoms; }
QString MalfunctionType::getRepairMethods() const { return mRepairMethods; }
int MalfunctionType::getSparePart1Code() const { return mSparePart1Code; }
int MalfunctionType::getSparePart2Code() const { return mSparePart2Code; }
int MalfunctionType::getSparePart3Code() const { return mSparePart3Code; }
double MalfunctionType::getLaborCost() const { return mLaborCost; }

bool MalfunctionType::isComplexRepair() const {
    return mLaborCost > 100.0 || (mSparePart1Code != -1 && mSparePart2Code != -1 && mSparePart3Code != -1);
}

bool MalfunctionType::requiresSpecialTools() const {
    return mRepairMethods.contains("special tool", Qt::CaseInsensitive);
}
