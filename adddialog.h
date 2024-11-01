

#define ADDDIALOG_H

#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include "servicecenterdatabase.h"

class AddDialog : public QDialog {
    Q_OBJECT

public:
    AddDialog(ServiceCenterDatabase& db, QWidget *parent = nullptr);

private slots:
    void accept() override;

private:
    void setupUi();

    QSpinBox* modelCodeEdit;
    QLineEdit* descriptionEdit;
    QTextEdit* symptomsEdit;
    QTextEdit* repairMethodsEdit;
    QSpinBox* sparePart1Edit;
    QSpinBox* sparePart2Edit;
    QSpinBox* sparePart3Edit;
    QDoubleSpinBox* laborCostEdit;

    ServiceCenterDatabase& database;
};
