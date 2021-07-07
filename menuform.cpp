#include "menuform.h"
#include "ui_menuform.h"

MenuForm::MenuForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MenuForm)
{
    ui->setupUi(this);

    setLayout(ui->gridLayout);

    this->hide_add_buttons();
    this->ui->pushButton_Settings->setText(tr("\u2699"));
}

void MenuForm::hide_add_buttons(){
    this->ui->pushButton_AddDoctor->hide();
    this->ui->pushButton_AddPatient->hide();
}

void MenuForm::show_add_buttons(){
    this->ui->pushButton_AddDoctor->show();
    this->ui->pushButton_AddPatient->show();
}

MenuForm::~MenuForm()
{
    delete ui;
}

void MenuForm::on_pushButton_MakeAppoitment_clicked()
{
    emit menuToAppoitmentSignal();
}


void MenuForm::on_pushButton_MakeOpinion_clicked()
{
    emit menuToOpinionSignal();
}


void MenuForm::on_pushButton_MyAppoitments_clicked()
{
    emit menuToMyAppoitmentsSignal();
}


void MenuForm::on_pushButton_AddPatient_clicked()
{
    emit menuToAddPatienSignal();
}


void MenuForm::on_pushButton_AddDoctor_clicked()
{
    emit menuToAddDoctorSignal();
}


void MenuForm::on_pushButton_Settings_clicked()
{
    emit menuToSettinsSignal();
}


void MenuForm::on_pushButton_OutPatientsCards_clicked()
{
    emit menuToOutpatientCardsSignal();
}

