#include "updatedialog.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QtWidgets/qlineedit.h>

UpdateDialog::UpdateDialog(ServiceCenterDatabase& db, int code, QWidget *parent)
    : QDialog(parent), malfunctionCode(code), database(db)
{
    setupUi();
    setWindowTitle("Update Malfunction Type");
}

void UpdateDialog::setupUi() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QFormLayout* formLayout = new QFormLayout();

    // Pre-fill fields with malfunction details
    MalfunctionType malfunction = database.getMalfunctionType(malfunctionCode);
    modelCodeEdit = new QSpinBox(this);
    modelCodeEdit->setValue(malfunction.getModelCode());

    descriptionEdit = new QLineEdit(malfunction.getDescription(), this);
    symptomsEdit = new QTextEdit(malfunction.getSymptoms(), this);
    repairMethodsEdit = new QTextEdit(malfunction.getRepairMethods(), this);

    formLayout->addRow("Model Code:", modelCodeEdit);
    formLayout->addRow("Description:", descriptionEdit);
    formLayout->addRow("Symptoms:", symptomsEdit);
    formLayout->addRow("Repair Methods:", repairMethodsEdit);

    // OK and Cancel buttons
    QPushButton* okButton = new QPushButton("OK", this);
    QPushButton* cancelButton = new QPushButton("Cancel", this);
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);

    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(okButton);
    mainLayout->addWidget(cancelButton);
}

void UpdateDialog::accept() {
    try {
        // Update database entry
        database.updateMalfunctionType(
            malfunctionCode,
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
