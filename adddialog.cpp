#include "adddialog.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QMessageBox>

AddDialog::AddDialog(ServiceCenterDatabase& db, QWidget *parent)
    : QDialog(parent), database(db)
{
    setupUi();
    setWindowTitle("Add New Malfunction Type");
}

void AddDialog::setupUi()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QFormLayout* formLayout = new QFormLayout();

    modelCodeEdit = new QSpinBox(this);
    modelCodeEdit->setRange(0, 99999);

    descriptionEdit = new QLineEdit(this);
    symptomsEdit = new QTextEdit(this);
    repairMethodsEdit = new QTextEdit(this);

    sparePart1Edit = new QSpinBox(this);
    sparePart2Edit = new QSpinBox(this);
    sparePart3Edit = new QSpinBox(this);
    sparePart1Edit->setRange(-1, 99999);
    sparePart2Edit->setRange(-1, 99999);
    sparePart3Edit->setRange(-1, 99999);
    sparePart1Edit->setSpecialValueText("None");
    sparePart2Edit->setSpecialValueText("None");
    sparePart3Edit->setSpecialValueText("None");

    laborCostEdit = new QDoubleSpinBox(this);
    laborCostEdit->setRange(0, 99999.99);
    laborCostEdit->setPrefix("$");

    formLayout->addRow("Model Code:", modelCodeEdit);
    formLayout->addRow("Description:", descriptionEdit);
    formLayout->addRow("Symptoms:", symptomsEdit);
    formLayout->addRow("Repair Methods:", repairMethodsEdit);
    formLayout->addRow("Spare Part 1:", sparePart1Edit);
    formLayout->addRow("Spare Part 2:", sparePart2Edit);
    formLayout->addRow("Spare Part 3:", sparePart3Edit);
    formLayout->addRow("Labor Cost:", laborCostEdit);

    mainLayout->addLayout(formLayout);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    QPushButton* okButton = new QPushButton("OK", this);
    QPushButton* cancelButton = new QPushButton("Cancel", this);

    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

void AddDialog::accept()
{
    try {
        database.addMalfunctionType(
            modelCodeEdit->value(),
            descriptionEdit->text(),
            symptomsEdit->toPlainText(),
            repairMethodsEdit->toPlainText(),
            sparePart1Edit->value(),
            sparePart2Edit->value(),
            sparePart3Edit->value(),
            laborCostEdit->value()
            );
        QDialog::accept();
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}
