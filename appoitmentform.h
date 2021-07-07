#ifndef APPOITMENTFORM_H
#define APPOITMENTFORM_H

#include <QWidget>

namespace Ui {
class AppoitmentForm;
}

class AppoitmentForm : public QWidget
{
    Q_OBJECT

public:
    explicit AppoitmentForm(QWidget *parent = nullptr);
    ~AppoitmentForm();
    void reset_input();
    void set_user_id(int ID);

signals:
    void Finished();

private slots:
    void on_comboBox_DoctorSpec_currentTextChanged(const QString &arg1);

    void on_comboBox_Doctor_currentTextChanged(const QString &arg1);

    void on_pushButton_Cancel_clicked();

    void on_pushButton_Apply_clicked();

    void on_lineEdit_PatintName_textEdited(const QString &arg1);

private:
    int user_id = -1;

    Ui::AppoitmentForm *ui;
};

#endif // APPOITMENTFORM_H
