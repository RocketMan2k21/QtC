#ifndef DELETEDIALOG_H
#define DELETEDIALOG_H

#include <QDoubleSpinBox>
#include <ServiceCenterDatabase.h>
#include <qdialog.h>


class DeleteDialog : public QDialog {
    Q_OBJECT

public:
    DeleteDialog(ServiceCenterDatabase& db, QWidget *parent = nullptr);

    DeleteDialog(ServiceCenterDatabase &db, int code, QWidget *parent);
private slots:
    void accept() override;

private:
    void setupUi();

    QSpinBox* modelCodeEdit;
      int malfunctionCode;
    ServiceCenterDatabase& database;
};

#endif // DELETEDIALOG_H
