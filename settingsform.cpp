#include "settingsform.h"
#include "ui_settingsform.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QRegularExpression>

SettingsForm::SettingsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsForm)
{
    ui->setupUi(this);
    setLayout(this->ui->gridLayout);
}

void SettingsForm::set_userid(int ID){
    this->user_id = ID;
    update_labels();
}

void SettingsForm::update_labels(){
    if(user_id == -1)
        return;

    QSqlQuery query;
    query.prepare("SELECT adress, phone FROM doctors WHERE id = :id;");
    query.bindValue(":id", user_id);

    query.exec();

    query.next();

    this->ui->lineEdit_Adress->setPlaceholderText(query.value(0).toString());
    this->ui->lineEdit_phoneNumber->setPlaceholderText(query.value(1).toString());

    query.prepare("SELECT username FROM users WHERE id = :id;");
    query.bindValue(":id", user_id);
    query.exec();
    query.next();

    this->ui->lineEdit_Username->setPlaceholderText(query.value(0).toString());

    this->ui->lineEdit_newPassword->setText("");
    this->ui->lineEdit_newPasswordSuggest->setText("");
    this->ui->lineEdit_OldPassword->setText("");
}

SettingsForm::~SettingsForm()
{
    delete ui;
}

void SettingsForm::on_pushButton_Back_clicked()
{
    emit finished();
}


void SettingsForm::on_pushButton_PasswOk_clicked()
{
    QString old_psw = ui->lineEdit_OldPassword->text();
    QString new_psw = ui->lineEdit_newPassword->text();
    QString new_psw_sug = ui->lineEdit_newPasswordSuggest->text();

    if(!old_psw.size() || !new_psw.size() || !new_psw_sug.size()){
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "Fill in all the fields!");
        messageBox.setFixedSize(800,200);
    }
    else{
        QMessageBox messageBox;
        QRegularExpression regex("^(?=.*\\d)(?=.*[a-z])(?=.*[A-Z]).{6,}$");

        QSqlQuery query;
        query.prepare("SELECT password FROM users WHERE id = :id;");
        query.bindValue(":id", user_id);
        query.exec();
        query.next();
        if(old_psw != query.value(0).toString()){
            messageBox.critical(0, "Error", "Incorrect Password!");
            messageBox.setFixedSize(800,200);
            return;
        }
        if(new_psw != new_psw_sug){
            messageBox.critical(0, "Error", "Password mismatch!");
            messageBox.setFixedSize(800,200);
            return;
        }
        if(!regex.match(new_psw).hasMatch()){
            messageBox.critical(0, "Error", "Uncorrect password format\nNeed to more than 6 symbols\nMore than 1 uppercase, lowercase, digit symbols!");
            messageBox.setFixedSize(800,200);
            return;
        }

        query.prepare("UPDATE users SET password = :password WHERE id = :id;");
        query.bindValue(":password", new_psw);
        query.bindValue(":id", user_id);
        query.exec();

        this->update_labels();
    }
}


void SettingsForm::on_pushButton_Submit_clicked()
{
    QString new_phone = ui->lineEdit_phoneNumber->text();
    QString new_adres = ui->lineEdit_Adress->text();
    QString new_username = ui->lineEdit_Username->text();

    QSqlQuery query;
    if(new_phone.size()){
        QRegularExpression reg_pn("^[0-9]{7,12}$");
        if(reg_pn.match(new_phone).hasMatch()){
            query.prepare("UPDATE doctors SET phone = :phone WHERE id = :id;");
            query.bindValue(":phone", new_phone);
            query.bindValue(":id", user_id);
            query.exec();
        }
    }
    if(new_adres.size()){
        query.prepare("UPDATE doctors SET adress = :adress WHERE id = :id;");
        query.bindValue(":adress", new_adres);
        query.bindValue(":id", user_id);
        query.exec();
    }
    if(new_username.size()){
        query.prepare("SELECT name FROM users;");
        bool contains = false;
        query.exec();
        while (query.next()) {
            if(query.value(0).toString() == new_username){
                contains = true;
                break;
            }
        }

        if(!contains){
            query.prepare("UPDATE users SET username = :username WHERE id = :id;");
            query.bindValue(":username", user_id);
            query.bindValue(":id", user_id);
            query.exec();
        }
        else{
            QMessageBox messageBox;
            messageBox.critical(0, "Error", "This username is already in use!");
            messageBox.setFixedSize(800,200);
        }
    }

    update_labels();
}

