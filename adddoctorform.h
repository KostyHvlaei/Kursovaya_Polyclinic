#ifndef ADDDOCTORFORM_H
#define ADDDOCTORFORM_H

#include <QWidget>

namespace Ui {
class AddDoctorForm;
}

class AddDoctorForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddDoctorForm(QWidget *parent = nullptr);
    ~AddDoctorForm();

signals:
    void finished();

private slots:
    void on_pushButton_Back_clicked();

    void on_pushButton_Submit_clicked();

private:
    void clear_fields();

    Ui::AddDoctorForm *ui;
};

#endif // ADDDOCTORFORM_H
