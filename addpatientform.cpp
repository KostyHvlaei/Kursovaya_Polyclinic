#include "addpatientform.h"
#include "ui_addpatientform.h"

#include "DataBaseConnector.h"

#include <QString>
#include <QSqlQuery>
#include <QRegularExpression>
#include <QMessageBox>

AddPatientForm::AddPatientForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddPatientForm)
{
    ui->setupUi(this);
    setLayout(ui->gridLayout);
}

void AddPatientForm::clear_fields(){
    this->ui->lineEdit_Adress->setText("");
    this->ui->lineEdit_Name->setText("");
    this->ui->lineEdit_Phone->setText("");

    this->ui->dateEdit_BirhDate->setDate(QDate::fromString("0.0.2000"));
}

AddPatientForm::~AddPatientForm()
{
    delete ui;
}

void AddPatientForm::on_pushButton_Back_clicked()
{
    emit finished();
}


void AddPatientForm::on_pushButton_Submit_clicked()
{
    QString name = this->ui->lineEdit_Name->text();
    QString adress = this->ui->lineEdit_Adress->text();
    QString phone = this->ui->lineEdit_Phone->text();

    QDate date = ui->dateEdit_BirhDate->date();

    QRegularExpression reg_pn("^[0-9]{7,12}$");

    if(name.length() < 6 || adress.length() < 6 || !reg_pn.match(phone).hasMatch() || date > QDate::currentDate()){
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Incorrect data!");
        messageBox.setFixedSize(800,200);

        return;
    }

    int id = DataBaseConnector::get_table_rows_count("patients") + 1;

    QSqlQuery query;

    query.prepare("INSERT INTO patients VALUES(:id, :name, :adress, :phone, :birth_date);");
    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":adress", adress);
    query.bindValue(":phone", phone);
    query.bindValue(":birth_date", date.toString("dd.MM.yyyy"));

    query.exec();

    clear_fields();
}

