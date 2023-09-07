#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QList>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QString>
#include "person.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QString display;    //public for simplicity

    QString printAllPersonInfo();

public slots:

private slots:
    void submit();
    void save();
    void clearDisplay();
    void clearForm();
    void showCurrentList();

private:
    Ui::Widget * ui;
    //Person person;  //class to hold information of each person
    QList<Person *> * personList;   //list to hold information of persons

    QLineEdit * inputFName;
    QLineEdit * inputLName;
    QLineEdit * inputEmail;
    QLineEdit * inputPhone;
    QLineEdit * inputAge;
    QTextEdit * displayInfo;

    void resetForm();
    bool requiredFormFilled();
    void saveForm();
    bool checkForm();
    bool invalidInfoPhone();
    bool invalidInfoAge();
    bool validateInfo();
    QString printPersonInfo(Person *);
    void delay();

};
#endif // WIDGET_H
