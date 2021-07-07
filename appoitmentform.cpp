#include "appoitmentform.h"
#include "ui_appoitmentform.h"
#include "DataBaseConnector.h"

#include <QString>
#include <QDateTime>
#include <QSqlQuery>
#include <QMessageBox>
#include <QVector>
#include <QCompleter>

AppoitmentForm::AppoitmentForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AppoitmentForm)
{
    ui->setupUi(this);

    setLayout(ui->gridLayout);

    this->ui->comboBox_DoctorSpec->addItem("");

    QVector<QString> specs = DataBaseConnector::get_exists_specs();

    for (int i = 0; i < specs.size() ; i++ ) {
        if(!(specs[i] == "admin"))
            this->ui->comboBox_DoctorSpec->addItem(specs[i]);
    }

    this->reset_input();
}

void AppoitmentForm::set_user_id(int ID){
    this->user_id = ID;
}

AppoitmentForm::~AppoitmentForm()
{
    delete ui;
}

void AppoitmentForm::reset_input(){
    this->ui->comboBox_Doctor->hide();
    this->ui->comboBox_Doctor->clear();

    this->ui->dateEdit_Appoimtn->hide();
    this->ui->dateEdit_Appoimtn->setDate(QDate::fromString("0.0.2000"));

    this->ui->dateTimeEdit->hide();
    this->ui->dateTimeEdit->setDateTime(QDateTime::fromString("01.01.2000 0:00:00"));

    this->ui->lineEdit_PatintName->hide();
    this->ui->lineEdit_PatintName->setText("");

    this->ui->pushButton_Apply->hide();

    this->ui->label_2->hide();
    this->ui->label->hide();
}

void AppoitmentForm::on_comboBox_DoctorSpec_currentTextChanged(const QString &arg1)
{
    Q_UNUSED(arg1);

    if(arg1 != ""){
        this->reset_input();
        QSqlQuery query;
        query.prepare("SELECT name FROM doctors WHERE spec = :spec;");
        query.bindValue(":spec", ui->comboBox_DoctorSpec->currentText());
        query.exec();
        qDebug() << query.lastError();

        while (query.next()) {
            this->ui->comboBox_Doctor->addItem(query.value(0).toString());
        }

        this->ui->comboBox_Doctor->show();
    }
    else{
        this->reset_input();
    }
}


void AppoitmentForm::on_comboBox_Doctor_currentTextChanged(const QString &arg1)
{
    Q_UNUSED(arg1);

    this->ui->dateTimeEdit->show();
    this->ui->label_2->show();
    this->ui->dateEdit_Appoimtn->show();
    this->ui->label->show();
    this->ui->lineEdit_PatintName->show();

    this->ui->pushButton_Apply->show();
}


void AppoitmentForm::on_pushButton_Cancel_clicked()
{
    this->reset_input();
    emit Finished();
}


void AppoitmentForm::on_pushButton_Apply_clicked()
{
    QString patien_name = this->ui->lineEdit_PatintName->text();
    QDate patoen_birth = this->ui->dateEdit_Appoimtn->date();
    QDateTime appoit_time = this->ui->dateTimeEdit->dateTime();

    if(appoit_time.date() < QDate::currentDate()){
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Incorrect date\n(lower than current)!");
        messageBox.setFixedSize(800,200);

        return;
    }

    QSqlQuery query;
    query.prepare("SELECT * FROM patients WHERE name = :pat_name AND birth_date = :bir_date;");
    query.bindValue(":pat_name", patien_name);
    query.bindValue(":bir_date", patoen_birth.toString("dd.MM.yyyy"));

    query.exec();

    if(query.next()){
        int patient_id = query.value(0).toInt();

        query.prepare("INSERT INTO appoitments VALUES(:patient_id, :doctor_id, :date_time);");

        int doctor_id = DataBaseConnector::get_doctor_id(ui->comboBox_Doctor->currentText(), ui->comboBox_DoctorSpec->currentText());

        query.bindValue(":patient_id", patient_id);
        query.bindValue(":doctor_id", doctor_id);
        query.bindValue(":date_time", appoit_time.toString("dd.MM.yyyy hh:mm"));

        query.exec();

        qDebug() << patient_id << " " << doctor_id;
        qDebug() << query.lastError();

        reset_input();
    }
    else{
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Incorrect data!");
        messageBox.setFixedSize(800,200);
    }
}

void AppoitmentForm::on_lineEdit_PatintName_textEdited(const QString &arg1)
{
    QStringList wordList;

    QSqlQuery query;
    query.prepare("SELECT name FROM patients WHERE name LIKE :name;");
    QString to_search = arg1 + "%";
    query.bindValue(":name", to_search);

    query.exec();

    while(query.next()){
        wordList << query.value(0).toString();
    }

    QCompleter *completer = new QCompleter(wordList, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->lineEdit_PatintName->setCompleter(completer);
}

