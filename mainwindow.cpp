#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QMap>
#include <QPair>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , db_connector()
    , ui(new Ui::MainWindow)
{

    this->menu_form = new MenuForm();
    this->opinion_form = new OpiniojnForm();
    this->appoitment_form = new AppoitmentForm();
    this->my_app_form = new MyAppoitmentsForm();
    this->add_doctor_form = new AddDoctorForm();
    this->add_patient_form = new AddPatientForm();
    this->_outpatient_cards_form = new outpatient_card_form();
    this->settings_form = new SettingsForm();

    connect(menu_form, &MenuForm::menuToOpinionSignal, this, &MainWindow::show_make_opinion_page);
    connect(menu_form, &MenuForm::menuToAppoitmentSignal, this, &MainWindow::show_make_appoitment_page);
    connect(menu_form, &MenuForm::menuToMyAppoitmentsSignal, this, &MainWindow::show_my_appoitments_page);
    connect(menu_form, &MenuForm::menuToAddDoctorSignal, this, &MainWindow::show_add_doctor_page);
    connect(menu_form, &MenuForm::menuToAddPatienSignal, this, &MainWindow::show_add_patient_page);
    connect(menu_form, &MenuForm::menuToOutpatientCardsSignal, this, &MainWindow::show_outpatient_cards_page);
    connect(menu_form, &MenuForm::menuToSettinsSignal, this, &MainWindow::show_settings_page);

    connect(opinion_form, &OpiniojnForm::finished, this, &MainWindow::show_menu);
    connect(opinion_form, &OpiniojnForm::finished_with_need_to_make_appotmnt, this, &MainWindow::show_make_appoitment_page);
    connect(appoitment_form, &AppoitmentForm::Finished, this, &MainWindow::show_menu);
    connect(my_app_form, &MyAppoitmentsForm::finished, this, &MainWindow::show_menu);
    connect(add_doctor_form, &AddDoctorForm::finished, this, &MainWindow::show_menu);
    connect(add_patient_form, &AddPatientForm::finished, this, &MainWindow::show_menu);
    connect(_outpatient_cards_form, &outpatient_card_form::finished, this, &MainWindow::show_menu);
    connect(settings_form, &SettingsForm::finished, this, &MainWindow::show_menu);

    ui->setupUi(this);

    ui->lineEdit_AuthPassword->setEchoMode(QLineEdit::Password);

    ui->gridLayout_Meny->addWidget(menu_form);
    ui->gridLayout_Opninion->addWidget(opinion_form);
    ui->gridLayout_MakeAppoit->addWidget(appoitment_form);
    ui->gridLayout_MyAppoits->addWidget(my_app_form);
    ui->gridLayout_AddDoctor->addWidget(add_doctor_form);
    ui->gridLayout_AddPatient->addWidget(add_patient_form);
    ui->gridLayout_OutpatientCards->addWidget(_outpatient_cards_form);
    ui->gridLayout_Settings->addWidget(settings_form);

    ui->centralwidget->setLayout(this->ui->gridLayout_Main);

    ui->page_Auth->setLayout(ui->gridLayout_AuthMain);
    ui->page_Menu->setLayout(this->ui->gridLayout_Meny);
    ui->page_Opniion->setLayout(this->ui->gridLayout_Opninion);
    ui->page_MakeAppit->setLayout(this->ui->gridLayout_MakeAppoit);
    ui->page_MyAppoits->setLayout(this->ui->gridLayout_MyAppoits);
    ui->page_AddDoctor->setLayout(this->ui->gridLayout_AddDoctor);
    ui->page_AddPatient->setLayout(this->ui->gridLayout_AddPatient);
    ui->page_OutpatientCards->setLayout(this->ui->gridLayout_OutpatientCards);
    ui->page_Settings->setLayout(this->ui->gridLayout_Settings);

    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::show_menu(){
    this->ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::show_make_opinion_page(){
    this->ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::show_make_appoitment_page(){
    this->ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::show_my_appoitments_page(){
    this->ui->stackedWidget->setCurrentIndex(4);
    this->my_app_form->setup_model();
}

void MainWindow::show_add_patient_page(){
    this->ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::show_add_doctor_page(){
    this->ui->stackedWidget->setCurrentIndex(6);
}

void MainWindow::show_outpatient_cards_page(){
    this->ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::show_settings_page(){
    this->ui->stackedWidget->setCurrentIndex(8);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Authorize_clicked()
{
    QString username = ui->lineEdit_AuthUsername->text();
    QString userpassword = ui->lineEdit_AuthPassword->text();

    if(!username.size() || !userpassword.size()){
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Empty filling!");
        messageBox.setFixedSize(800,200);
    }
    else{

        int auth_code = db_connector.auth_user_passw(username, userpassword);
        if(auth_code == -1){
            QMessageBox messageBox;
            messageBox.critical(0, "Error", "Uncorrect username or password!");
            messageBox.setFixedSize(800,200);
        }
        else{
            this->user_id = auth_code;
            this->opinion_form->set_user_id(auth_code);
            this->appoitment_form->set_user_id(auth_code);
            this->settings_form->set_userid(auth_code);

            this->user_spec = db_connector.get_spec_by_id(auth_code);

            if(this->user_spec == "admin"){
                this->menu_form->show_add_buttons();
            }

            this->ui->stackedWidget->setCurrentIndex(1);
        }
    }
}
