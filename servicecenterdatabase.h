#define SERVICECENTERDATABASE_H

#pragma once
#include <QObject>
#include <QVector>
#include "MalfunctionType.h"

class ServiceCenterDatabase : public QObject
{
    Q_OBJECT

public:
    explicit ServiceCenterDatabase(QObject* parent = nullptr);
    ~ServiceCenterDatabase();

    MalfunctionType& addMalfunctionType(int modelCode, const QString& description, const QString& symptoms,
                                        const QString& repairMethods, int sparePart1, int sparePart2,
                                        int sparePart3, double laborCost);

    MalfunctionType& updateMalfunctionType(int code, int newModelCode, const QString& newDescription,
                               const QString& newSymptoms, const QString& newRepairMethods,
                               int newSparePart1, int newSparePart2, int newSparePart3,
                               double newLaborCost);

    const MalfunctionType& getMalfunctionType(int code) const;
    void deleteMalfunctionType(int code);
    void displayAll() const;

    QVector<MalfunctionType> getMalfunctionTypes() const;

public slots:
    void saveToFile() const;
    void loadFromFile();

private:
    QVector<MalfunctionType> malfunctionTypes;
    int nextCode;

    int generateCode();
};

