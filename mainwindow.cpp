#include "mainwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include "adddialog.h"
#include "displaydialog.h"
#include "updatedialog.h"
#include "deletedialog.h"
#include "servicecenterdatabase.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    setupTable();
    setupConnections();
    setWindowTitle("Service Center Management System");
}

MainWindow::~MainWindow() {
}

void MainWindow::setupUi()
{
    QWidget* centralWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    // Create table
    tableWidget = new QTableWidget(this);
    mainLayout->addWidget(tableWidget);

    // Create buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    addButton = new QPushButton("Add Malfunction", this);
    displayButton = new QPushButton("Display Details", this);
    updateButton = new QPushButton("Update", this);
    deleteButton = new QPushButton("Delete", this);

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(displayButton);
    buttonLayout->addWidget(updateButton);
    buttonLayout->addWidget(deleteButton);

    mainLayout->addLayout(buttonLayout);
    setCentralWidget(centralWidget);
}

void MainWindow::setupTable()
{
    QStringList headers;
    headers << "Code" << "Model Code" << "Description" << "Complex Repair" << "Special Tools";
    tableWidget->setColumnCount(headers.size());
    tableWidget->setHorizontalHeaderLabels(headers);
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    refreshTable();
}

void MainWindow::setupConnections()
{
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addMalfunctionType);
    connect(displayButton, &QPushButton::clicked, this, &MainWindow::displayMalfunctionType);
    connect(updateButton, &QPushButton::clicked, this, &MainWindow::updateMalfunctionType);
    connect(deleteButton, &QPushButton::clicked, this, &MainWindow::deleteMalfunctionType);
}

void MainWindow::refreshTable()
{
    tableWidget->setRowCount(0);
    for (const auto& malfunction : database.getMalfunctionTypes()) {
        int row = tableWidget->rowCount();
        tableWidget->insertRow(row);

        tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(malfunction.getCode())));
        tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(malfunction.getModelCode())));
        tableWidget->setItem(row, 2, new QTableWidgetItem(malfunction.getDescription()));
        tableWidget->setItem(row, 3, new QTableWidgetItem(malfunction.isComplexRepair() ? "Yes" : "No"));
        tableWidget->setItem(row, 4, new QTableWidgetItem(malfunction.requiresSpecialTools() ? "Yes" : "No"));
    }
}

void MainWindow::addMalfunctionType() {
    AddDialog addDialog(database, this);
    if (addDialog.exec() == QDialog::Accepted) {
        refreshTable(); // Refresh table after adding new entry
    }
}

// Opens the DisplayDialog for showing details of the selected malfunction type
void MainWindow::displayMalfunctionType() {
    int selectedRow = tableWidget->currentRow();
    if (selectedRow < 0) {
        QMessageBox::warning(this, "Selection Error", "Please select a malfunction type to display.");
        return;
    }

    int code = tableWidget->item(selectedRow, 0)->text().toInt();
    DisplayDialog displayDialog(database.getMalfunctionType(code), this);
    displayDialog.exec(); // Open dialog in read-only mode
}

// Opens the UpdateDialog for editing details of the selected malfunction type
void MainWindow::updateMalfunctionType() {
    int selectedRow = tableWidget->currentRow();
    if (selectedRow < 0) {
        QMessageBox::warning(this, "Selection Error", "Please select a malfunction type to update.");
        return;
    }

    int code = tableWidget->item(selectedRow, 0)->text().toInt();
    UpdateDialog updateDialog(database, code, this);
    if (updateDialog.exec() == QDialog::Accepted) {
        refreshTable(); // Refresh table after updating
    }
}

void MainWindow::deleteMalfunctionType() {
    int selectedRow = tableWidget->currentRow();
    if (selectedRow < 0) {
        QMessageBox::warning(this, "Selection Error", "Please select a malfunction type to delete.");
        return;
    }

    int code = tableWidget->item(selectedRow, 0)->text().toInt();

    // Confirmation dialog
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "Confirm Deletion",
        QString("Are you sure you want to delete the malfunction type with code %1?").arg(code),
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        database.deleteMalfunctionType(
            code
            );
        refreshTable(); // Refresh table after deletion
    }
}
