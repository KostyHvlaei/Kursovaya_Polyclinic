#include "myappoitmentsform.h"
#include "ui_myappoitmentsform.h"

#include <QSqlTableModel>

MyAppoitmentsForm::MyAppoitmentsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyAppoitmentsForm)
{
    ui->setupUi(this);
    setLayout(ui->gridLayout);

    this->ui->dateEdit->setDate(QDate::currentDate());

    setup_model();
}

void MyAppoitmentsForm::set_user_id(int ID){
    this->user_id = ID;
}

void MyAppoitmentsForm::setup_model(){

    this->table_model = new QSqlTableModel();
    this->table_model->setTable("appoitments");

    QDate date = ui->dateEdit->date();
    table_model->setFilter("date_time LIKE \"" + date.toString("dd.MM.yyyy") + "%\"");

    table_model->setHeaderData(0, Qt::Horizontal ,"patient_id");
    table_model->setHeaderData(1, Qt::Horizontal ,"doctor_id");
    table_model->setHeaderData(2, Qt::Horizontal ,"date_time");

    table_model->select();

    this->ui->tableView->setModel(table_model);

    this->ui->tableView->setColumnHidden(1, true);

    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

MyAppoitmentsForm::~MyAppoitmentsForm()
{
    delete ui;
}

void MyAppoitmentsForm::on_pushButton_Back_clicked()
{
    this->has_filter = false;
    emit finished();
}


void MyAppoitmentsForm::on_pushButton_Apply_clicked()
{
    this->has_filter = true;
    this->setup_model();
}
