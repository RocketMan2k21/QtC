

#include "displaydialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

DisplayDialog::DisplayDialog(const MalfunctionType& malfunction, QWidget *parent)
    : QDialog(parent)
{
    setupUi(malfunction);
    setWindowTitle("Malfunction Details");
}

void DisplayDialog::setupUi(const MalfunctionType& malfunction) {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // Display various fields in labels (use QLabel for simplicity)
    mainLayout->addWidget(new QLabel("Code: " + QString::number(malfunction.getCode())));
    mainLayout->addWidget(new QLabel("Model Code: " + QString::number(malfunction.getModelCode())));
    mainLayout->addWidget(new QLabel("Description: " + malfunction.getDescription()));
    mainLayout->addWidget(new QLabel("Symptoms: " + malfunction.getSymptoms()));
    mainLayout->addWidget(new QLabel("Repair Methods: " + malfunction.getRepairMethods()));

    // Additional fields and OK button
    QPushButton* okButton = new QPushButton("OK", this);
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    mainLayout->addWidget(okButton);
}
