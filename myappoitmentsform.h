#ifndef MYAPPOITMENTSFORM_H
#define MYAPPOITMENTSFORM_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class MyAppoitmentsForm;
}

class MyAppoitmentsForm : public QWidget
{
    Q_OBJECT

public:
    explicit MyAppoitmentsForm(QWidget *parent = nullptr);
    ~MyAppoitmentsForm();

    void set_user_id(int ID);
    void setup_model();
signals:
    void finished();

private slots:
    void on_pushButton_Back_clicked();

    void on_pushButton_Apply_clicked();

private:

    bool has_filter = false;

    int user_id;

    QSqlTableModel* table_model;

    Ui::MyAppoitmentsForm *ui;
};

#endif // MYAPPOITMENTSFORM_H
