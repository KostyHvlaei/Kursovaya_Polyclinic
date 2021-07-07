#ifndef SETTINGSFORM_H
#define SETTINGSFORM_H

#include <QWidget>

namespace Ui {
class SettingsForm;
}

class SettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsForm(QWidget *parent = nullptr);
    ~SettingsForm();

    void set_userid(int ID);

    void update_labels();

signals:
    void finished();

private slots:
    void on_pushButton_Back_clicked();

    void on_pushButton_PasswOk_clicked();

    void on_pushButton_Submit_clicked();

private:
    int user_id = -1;

    Ui::SettingsForm *ui;
};

#endif // SETTINGSFORM_H
