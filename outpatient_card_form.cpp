#include "outpatient_card_form.h"
#include "ui_outpatient_card_form.h"

#include <QSqlQuery>
#include <QCompleter>

#include "DataBaseConnector.h"

outpatient_card_form::outpatient_card_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::outpatient_card_form)
{
    ui->setupUi(this);
    setLayout(this->ui->gridLayout);
}

void outpatient_card_form::setup_model(){
    this->model = new QSqlTableModel();
    this->model->setTable("opinions");

    QString pacient_name = this->ui->lineEdit_Name->text();
    QDate pacient_birthdate = this->ui->dateEdit_Birhdate->date();

    int pacient_id = DataBaseConnector::get_patient_id(pacient_name, pacient_birthdate);

    this->model->setFilter("patient_id = " + QString::number(pacient_id));

    model->setHeaderData(0, Qt::Horizontal ,"patient_id");
    model->setHeaderData(1, Qt::Horizontal ,"doctor_id");
    model->setHeaderData(2, Qt::Horizontal ,"opinion");
    model->setHeaderData(3, Qt::Horizontal, "date_time");

    model->select();

    this->ui->tableView->setModel(model);

    this->ui->tableView->setColumnHidden(0, true);

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->tableView->resizeColumnsToContents();
    ui->tableView->resizeRowsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
}

outpatient_card_form::~outpatient_card_form()
{
    delete ui;
}

void outpatient_card_form::on_pushButton_Back_clicked()
{
    emit finished();
}


void outpatient_card_form::on_pushButton_GetCard_clicked()
{
    setup_model();
}


void outpatient_card_form::on_lineEdit_Name_textEdited(const QString &arg1)
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

