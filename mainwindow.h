#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include "DataBaseConnector.h"
#include "opiniojnform.h"
#include "menuform.h"
#include "appoitmentform.h"
#include "myappoitmentsform.h"
#include "adddoctorform.h"
#include "addpatientform.h"
#include "outpatient_card_form.h"
#include "settingsform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_Authorize_clicked();

private:

    void show_menu();
    void show_make_opinion_page();
    void show_my_appoitments_page();
    void show_make_appoitment_page();
    void show_add_patient_page();
    void show_add_doctor_page();
    void show_outpatient_cards_page();
    void show_settings_page();

    DataBaseConnector db_connector;

    int user_id = -1;
    QString user_spec = "";

    MenuForm* menu_form;
    OpiniojnForm* opinion_form;
    AppoitmentForm* appoitment_form;
    MyAppoitmentsForm* my_app_form;
    AddDoctorForm* add_doctor_form;
    AddPatientForm* add_patient_form;
    outpatient_card_form* _outpatient_cards_form;
    SettingsForm* settings_form;

    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
