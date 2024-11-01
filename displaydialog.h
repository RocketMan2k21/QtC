
#define DISPLAYDIALOG_H
#pragma once
#include <QDialog>
#include "servicecenterdatabase.h"

class DisplayDialog : public QDialog {
    Q_OBJECT

public:
    DisplayDialog(const MalfunctionType& malfunction, QWidget *parent = nullptr);

private:
    void setupUi(const MalfunctionType& malfunction);
};
