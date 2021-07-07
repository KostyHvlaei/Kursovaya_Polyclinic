#ifndef DATABASECONNECTOR_H
#define DATABASECONNECTOR_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QSqlError>
#include <QString>
#include <QFile>
#include <QVector>
#include <QDate>

class DataBaseConnector{
public:

    DataBaseConnector(){
        this->connect();
    }

    bool connect(){
        db_connection = QSqlDatabase::addDatabase("QSQLITE");
        db_connection.setDatabaseName("PolyclinicDB.db");
        if(db_connection.open()){
            qDebug() << "Data base connected!";
            if(db_connection.tables().size() < 5){
                QSqlQuery query;
                query.exec("CREATE TABLE users(id INT NOT NULL PRIMARY KEY,username TEXT NOT NULL, password TEXT NOT NULL);");
                query.exec("CREATE TABLE doctors(id INT NOT NULL, name TEXT NOT NULL, spec TEXT NOT NULL, adress TEXT NOT NULL, phone TEXT NOT NULL, FOREIGN KEY (id) REFERENCES users(id) ON DELETE CASCADE);");
                query.exec("CREATE TABLE patients(id INT NOT NULL PRIMARY KEY, name TEXT NOT NULL, adress TEXT NOT NULL, phone TEXT NOT NULL, birth_date TEXT NOT NULL);");
                query.exec("CREATE TABLE appoitments(patient_id INT NOT NULL,doctor_id INT NOT NULL, date_time TEXT NOT NULL, FOREIGN KEY (patient_id) REFERENCES patients(id) ON DELETE CASCADE, FOREIGN KEY (doctor_id) REFERENCES users(id) ON DELETE CASCADE);");
                query.exec("CREATE TABLE opinions(patient_id INT NOT NULL,doctor_id INT NOT NULL, opinion_text TEXT NOT NULL, date_time TEXT NOT NULL, FOREIGN KEY (patient_id) REFERENCES patients(id) ON DELETE CASCADE, FOREIGN KEY (doctor_id) REFERENCES users(id) ON DELETE CASCADE);");
                query.exec("INSERT INTO users VALUES(0, \"admin\", \"admin\");");
                query.exec("INSERT INTO doctors VALUES(0, \"admin\", \"admin\", \"admin\", \"admin\");");
            }
            return true;
        }
        else{
            qDebug() << "not connected";
            return false;
        }
    }

    static QVector<QString> get_exists_specs(){
        QVector<QString> specs;
        QSqlQuery query("SELECT * FROM doctors;");
        query.exec();

        while (query.next()) {
            if(!specs.contains(query.value(2).toString())){
                specs.append(query.value(2).toString());
            }
        }

        return specs;
    }

    static int get_doctor_id(QString name, QString spec){
        QSqlQuery query;
        query.prepare("SELECT id FROM doctors WHERE name = :name AND spec = :spec;");
        query.bindValue(":name", name);
        query.bindValue(":spec", spec);

        query.exec();

        return query.next() ? query.value(0).toInt() : -1;
    }

    static int get_patient_id(QString name, QDate birth_date){
        QSqlQuery query;
        query.prepare("SELECT id FROM patients WHERE name = :name AND birth_date = :birth_date");
        query.bindValue(":name", name);
        query.bindValue(":birth_date", birth_date.toString("dd.MM.yyyy"));

        query.exec();

        return query.next() ? query.value(0).toInt() : -1;
    }

    static int get_table_rows_count(QString table_name){
        QSqlQuery query("SELECT COUNT(*) FROM " + table_name + ";");
        query.exec();
        if (query.next()) {
            return query.value(0).toInt();
        }
        else{
            return 0;
        }
    }

    QString get_spec_by_id(int ID){
        QSqlQuery query;
        query.prepare("SELECT * FROM doctors WHERE id = :id;");
        query.bindValue(":id", ID);
        query.exec();
        query.next();

        return query.value(2).toString();
    }

    int auth_user_passw(QString username, QString userpassword){
        QSqlQuery query;
        query.prepare("SELECT * FROM users WHERE username = :username;");
        query.bindValue(":username", username);
        query.exec();
        if(query.next()){
             QString table_password = query.value(2).toString();
             if(table_password == userpassword){
                 return query.value(0).toInt();
             }
             else{
                 return -1;
             }
        }
        else{
            return -1;
        }
    }

private:

    QSqlDatabase db_connection;
};

#endif // DATABASECONNECTOR_H
