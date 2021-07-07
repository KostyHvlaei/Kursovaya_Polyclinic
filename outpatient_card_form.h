#ifndef OUTPATIENT_CARD_FORM_H
#define OUTPATIENT_CARD_FORM_H

#include <QWidget>
#include <QSqlTableModel>

namespace Ui {
class outpatient_card_form;
}

class outpatient_card_form : public QWidget
{
    Q_OBJECT

public:
    explicit outpatient_card_form(QWidget *parent = nullptr);
    ~outpatient_card_form();

signals:
    void finished();

private slots:
    void on_pushButton_Back_clicked();

    void on_pushButton_GetCard_clicked();

    void on_lineEdit_Name_textEdited(const QString &arg1);

private:
    void setup_model();

    QSqlTableModel* model;

    Ui::outpatient_card_form *ui;
};

#endif // OUTPATIENT_CARD_FORM_H
