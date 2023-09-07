#include "person.h"

Person::Person()    {}
Person::Person(QString fn, QString ln, QString e)
{
    m_firstName = fn;
    m_lastName = ln;
    m_emailAddress = e;
}

//Setters
void Person::setFName(QString fn)    {m_firstName = fn;}
void Person::setLName(QString ln)    {m_lastName = ln;}
void Person::setEmail(QString e)     {m_emailAddress = e;}
void Person::setPhone(QString p)     {m_phoneNumber = p;}
void Person::setAge(QString a)       {m_age = a;}
//Getters
QString Person   ::getFName()        {return m_firstName;}
QString Person   ::getLName()        {return m_lastName;}
QString Person   ::getEmail()        {return m_emailAddress;}
QString Person   ::getPhone()        {return m_phoneNumber;}
QString Person   ::getAge()          {return m_age;}
