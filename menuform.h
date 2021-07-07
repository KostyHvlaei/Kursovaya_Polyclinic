#ifndef MENUFORM_H
#define MENUFORM_H

#include <QWidget>

namespace Ui {
class MenuForm;
}

class MenuForm : public QWidget
{
    Q_OBJECT

public:
    explicit MenuForm(QWidget *parent = nullptr);
    ~MenuForm();

    void hide_add_buttons();
    void show_add_buttons();

signals:
    void menuToOpinionSignal();
    void menuToAppoitmentSignal();
    void menuToMyAppoitmentsSignal();
    void menuToAddPatienSignal();
    void menuToAddDoctorSignal();
    void menuToOutpatientCardsSignal();
    void menuToSettinsSignal();

private slots:
    void on_pushButton_MakeAppoitment_clicked();

    void on_pushButton_MakeOpinion_clicked();

    void on_pushButton_MyAppoitments_clicked();

    void on_pushButton_AddPatient_clicked();

    void on_pushButton_AddDoctor_clicked();

    void on_pushButton_Settings_clicked();

    void on_pushButton_OutPatientsCards_clicked();

private:
    Ui::MenuForm *ui;
};

#endif // MENUFORM_H
