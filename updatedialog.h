
#define UPDATEDIALOG_H

#pragma once

#include <QDialog>
#include <QDoubleSpinBox>
#include <QTextEdit>
#include "servicecenterdatabase.h"

class UpdateDialog : public QDialog {
    Q_OBJECT

public:
    UpdateDialog(ServiceCenterDatabase& db, int code, QWidget *parent = nullptr);

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

    int malfunctionCode;
   ServiceCenterDatabase& database;
};
