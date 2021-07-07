#ifndef OPINIOJNFORM_H
#define OPINIOJNFORM_H

#include <QWidget>

namespace Ui {
class OpiniojnForm;
}

class OpiniojnForm : public QWidget
{
    Q_OBJECT

public:
    explicit OpiniojnForm(QWidget *parent = nullptr);
    ~OpiniojnForm();

    void set_user_id(int ID);
signals:
    void finished();
    void finished_with_need_to_make_appotmnt();

private slots:
    void on_pushButton_Apply_clicked();

    void on_pushButton_Cancel_clicked();

    void on_lineEdit_Name_textEdited(const QString &arg1);

private:
    int user_id = -1;

    Ui::OpiniojnForm *ui;
};

#endif // OPINIOJNFORM_H
