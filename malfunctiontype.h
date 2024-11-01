
#define MALFUNCTIONTYPE_H

#pragma once
#include <QString>

    class MalfunctionType
{
public:
    MalfunctionType();
    void display() const;

    // Setters
    void setCode(int code);
    void setModelCode(int modelCode);
    void setDescription(const QString& description);
    void setSymptoms(const QString& symptoms);
    void setRepairMethods(const QString& repairMethods);
    void setSparePart1Code(int sparePartCode);
    void setSparePart2Code(int sparePartCode);
    void setSparePart3Code(int sparePartCode);
    void setLaborCost(double laborCost);

    // Getters
    int getCode() const;
    int getModelCode() const;
    QString getDescription() const;
    QString getSymptoms() const;
    QString getRepairMethods() const;
    int getSparePart1Code() const;
    int getSparePart2Code() const;
    int getSparePart3Code() const;
    double getLaborCost() const;

    bool isComplexRepair() const;
    bool requiresSpecialTools() const;

private:
    int mCode;
    int mModelCode;
    QString mDescription;
    QString mSymptoms;
    QString mRepairMethods;
    int mSparePart1Code;
    int mSparePart2Code;
    int mSparePart3Code;
    double mLaborCost;
};

