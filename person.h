#ifndef PERSON_H
#define PERSON_H

#include <QString>
#include <QWidget>

class Person
{
public:
    Person();
    Person(QString, QString, QString);
    //setters
    void setFName(QString);
    void setLName(QString);
    void setEmail(QString);
    void setPhone(QString); //validate numeric
    void setAge(QString);   //validate numeric
    //getters
    QString getFName();
    QString getLName();
    QString getEmail();
    QString getPhone();
    QString getAge();
private:
    QString m_firstName;
    QString m_lastName;
    QString m_emailAddress;
    //optional fields
    QString m_phoneNumber;
    QString m_age;
};

#endif // PERSON_H
