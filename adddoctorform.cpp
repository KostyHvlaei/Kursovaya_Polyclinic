#include "adddoctorform.h"
#include "ui_adddoctorform.h"
#include "DataBaseConnector.h"

#include <QSqlQuery>
#include <QRegularExpression>
#include <QMessageBox>

AddDoctorForm::AddDoctorForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddDoctorForm)
{
    ui->setupUi(this);

    setLayout(ui->gridLayout_ADd);

    ui->comboBox->addItem("admin");
    ui->comboBox->addItem("therapist");
    ui->comboBox->addItem("pediatrician");
    ui->comboBox->addItem("cardiologist");
    ui->comboBox->addItem("ophthalmologist");
    ui->comboBox->addItem("otolaryngologist");
    ui->comboBox->addItem("surgeon");
    ui->comboBox->addItem("traumatologist");
    ui->comboBox->addItem("physiotherapist");
    ui->comboBox->addItem("virologist");
    ui->comboBox->addItem("phlebologist");
    ui->comboBox->addItem("histologist");
    ui->comboBox->addItem("mammologist");
    ui->comboBox->addItem("endocrinologist");
    ui->comboBox->addItem("allergist");
}

AddDoctorForm::~AddDoctorForm()
{
    delete ui;
}

void AddDoctorForm::clear_fields(){
    ui->lineEdit_name->setText("");
    ui->lineEdit_adress->setText("");
    ui->lineEdit_phone->setText("");
}

void AddDoctorForm::on_pushButton_Back_clicked()
{
    emit finished();
}


void AddDoctorForm::on_pushButton_Submit_clicked()
{
    QString name = ui->lineEdit_name->text();
    QString adress = ui->lineEdit_adress->text();
    QString phone = ui->lineEdit_phone->text();
    QString spec = ui->comboBox->currentText();

    QRegularExpression reg_pn("^[0-9]{7,12}$");

    if(name.length() < 6 || adress.length() < 6 || !reg_pn.match(phone).hasMatch()){
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Incorrect data!");
        messageBox.setFixedSize(800,200);

        return;
    }

    int id = DataBaseConnector::get_table_rows_count("doctors") + 1;

    QSqlQuery query;

    query.prepare("INSERT INTO users VALUES(:id, :username, :userpassword)");
    query.bindValue(":id", id);
    query.bindValue(":username", name);
    query.bindValue(":userpassword", name);

    query.exec();

    query.prepare("INSERT INTO doctors VALUES(:id, :name, :spec, :adress, :phone);");
    query.bindValue(":id", id);
    query.bindValue(":name", name);
    query.bindValue(":spec", spec);
    query.bindValue(":adress", adress);
    query.bindValue(":phone", phone);

    if(!query.exec()){
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Something wrong!");
        messageBox.setFixedSize(800,200);
    }

    clear_fields();
}

