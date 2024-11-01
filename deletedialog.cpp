#include "deletedialog.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QtWidgets/qlineedit.h>

DeleteDialog::DeleteDialog(ServiceCenterDatabase& db, int code, QWidget *parent)
    : QDialog(parent), malfunctionCode(code), database(db)
{
    setupUi();
    setWindowTitle("Update Malfunction Type");
}

void DeleteDialog::setupUi() {

}

void DeleteDialog::accept() {
    try {
        // Update database entry
        database.deleteMalfunctionType(
            malfunctionCode
            );
        QDialog::accept();
    }
    catch (const std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
    }
}
