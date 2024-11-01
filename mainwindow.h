
#define MAINWINDOW_H

#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include "servicecenterdatabase.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addMalfunctionType();
    void displayMalfunctionType();
    void updateMalfunctionType();
    void deleteMalfunctionType();
    void refreshTable();

private:
    void setupUi();
    void setupTable();
    void setupConnections();

    QTableWidget* tableWidget;
    QPushButton* addButton;
    QPushButton* displayButton;
    QPushButton* updateButton;
    QPushButton* deleteButton;

    ServiceCenterDatabase database;
};
