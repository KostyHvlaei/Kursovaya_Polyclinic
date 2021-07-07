#include "opiniojnform.h"
#include "ui_opiniojnform.h"

#include <QString>
#include <QDate>
#include <QDateTime>
#include <QSqlQuery>
#include <QMessageBox>
#include <QCompleter>
#include <QSqlError>

OpiniojnForm::OpiniojnForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OpiniojnForm)
{
    ui->setupUi(this);
    setLayout(ui->gridLayout);

}

void OpiniojnForm::set_user_id(int ID){
    this->user_id = ID;
}

OpiniojnForm::~OpiniojnForm()
{
    delete ui;
}

void OpiniojnForm::on_pushButton_Apply_clicked()
{
    QString patient_name = this->ui->lineEdit_Name->text();
    QDate birth_date = this->ui->dateEdit_BithDate->date();

    QSqlQuery query;
    query.prepare("SELECT * FROM patients WHERE name = :name AND birth_date = :birthdate;");
    query.bindValue(":name", patient_name);
    query.bindValue(":birthdate", birth_date.toString("dd.MM.yyyy"));

    query.exec();

    if(query.next()){
        QString text = this->ui->plainTextEdit_Opinion->toPlainText();
        if(text.size() == 0){
            QMessageBox messageBox;
            messageBox.critical(0, "Error", "Opinion is empty!");
            messageBox.setFixedSize(800,200);
            return;
        }

        int patient_id = query.value(0).toInt();

        QSqlQuery query;
        query.prepare("INSERT INTO opinions VALUES(:patient_id , :doctor_id , :op_text, :date_time);");

        query.bindValue(":patient_id", patient_id);
        query.bindValue(":doctor_id", user_id);
        query.bindValue(":op_text", text);
        query.bindValue(":date_time", QDateTime::currentDateTime().toString("dd.MM.yyyy hh:mm"));

        query.exec();
    }
    else{
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Patient doesn't exists!");
        messageBox.setFixedSize(800,200);
        return;
    }


    if(this->ui->radioButton_MakeAppoitnment->isChecked()){

        emit finished_with_need_to_make_appotmnt();
    }
    else{
        emit finished();
    }
}


void OpiniojnForm::on_pushButton_Cancel_clicked()
{
    emit finished();
}


void OpiniojnForm::on_lineEdit_Name_textEdited(const QString &arg1)
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
    ui->lineEdit_Name->setCompleter(completer);
}

