#ifndef ADDPATIENTFORM_H
#define ADDPATIENTFORM_H

#include <QWidget>

namespace Ui {
class AddPatientForm;
}

class AddPatientForm : public QWidget
{
    Q_OBJECT

public:
    explicit AddPatientForm(QWidget *parent = nullptr);
    ~AddPatientForm();

signals:
    void finished();

private slots:
    void on_pushButton_Back_clicked();

    void on_pushButton_Submit_clicked();

private:
    void clear_fields();

    Ui::AddPatientForm *ui;
};

#endif // ADDPATIENTFORM_H
