#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>
#include <QDebug>
#include <QFile>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    personList = new QList<Person *>;
    display = "";

    inputFName = ui->textFName;
    inputLName = ui->textLName;
    inputEmail = ui->textEmail;
    inputPhone = ui->textPhone;
    inputAge = ui->textAge;
    displayInfo = ui->displayText;

    connect(ui->buttonSubmit, SIGNAL(clicked(bool)), this, SLOT(submit()) );
    connect(ui->buttonSave, SIGNAL(clicked()), this, SLOT(save()) );
    connect(ui->buttonClearDisplay, SIGNAL(clicked()), this, SLOT(clearDisplay()) );
    connect(ui->buttonClearForm, SIGNAL(clicked()), this, SLOT(clearForm()) );
    connect(ui->buttonShowList, SIGNAL(clicked()), this, SLOT(showCurrentList()));

    //Validation Through Masks
    inputPhone->setInputMask("(000)000-0000");
    inputAge->setInputMask("000");
}

Widget::~Widget()
{
    delete ui;
    delete personList;
}

//PrivateSlots-------------------------
void Widget::submit()
{
    if(validateInfo())
    {
        //qDebug("valid info");
        saveForm();
        //qDebug("saved form");
        clearForm();
    }
}
void Widget::save()
{
    //Prompt user if they wish to submit current info, if req is filled
    bool checked = checkForm();

    if(checked)
    {
        QFile file("../CIS17B_Midterm/EventListForm.txt");  //go up one and into project folder
        //QFile file("EventListForm.txt");
        //file.open(QIODevice::WriteOnly);

        if(file.open(QFile::WriteOnly | QFile::Text))
        {
            QTextStream out(&file);

            out << printAllPersonInfo(); //print display to text file

            //Give user feedback
            displayInfo->setText("Form Saved!");
        }
        else
            QMessageBox::information(this, tr("Error"), tr("Could not write to file"), "ok");


        file.close(); //don't leak memory!
    }
}
void Widget::clearDisplay()
{
    displayInfo->clear();
}
void Widget::clearForm()
{
    resetForm();
}
void Widget::showCurrentList()
{
    displayInfo->setText(printAllPersonInfo());
}

//PublicSlots-------------------------


//Class Functions-------------------------
void Widget::resetForm()
{
    inputFName->clear();
    inputLName->clear();
    inputEmail->clear();
    inputPhone->clear();
    inputAge->clear();
}
bool Widget::requiredFormFilled()
{
    //if required form fields are filled (not empty), return true
    if(!inputFName->text().isEmpty() &&
       !inputLName->text().isEmpty() &&
       !inputEmail->text().isEmpty())
        return true;
    //otherwise
    return false;
}
void Widget::saveForm()
{
    //Required Info
    Person * personInfo = new Person(inputFName->text(), inputLName->text(), inputEmail->text());
        //Currently leaking memory if not appended to person list pointer

    //Optional Info
    if(!inputPhone->text().isEmpty())
        personInfo->setPhone(inputPhone->text());
    if(!inputAge->text().isEmpty())
        personInfo->setAge(inputAge->text());

    //Append Person to QList<Person>
    personList->append(personInfo);


    //Display Current
    //displayInfo->setText(printPersonInfo(personInfo));

    //Display All
    displayInfo->setText(printAllPersonInfo());

}
bool Widget::checkForm()
{
    //If Form has acceptable format, prompt user if they want to save first
    int ans = -1;
    if(requiredFormFilled())
    {
        ans = QMessageBox::
                          question( this, tr("Warning"),
                          "Your current form will not be saved. Would you like to save the form first?",
                          "Save", "Continue", "Edit Form",
                          0,  /* default value */
                          -1  /* value sent on "esc" or "windowclose" */ ) ;

    }

    if(ans == 0)
    {
        if(validateInfo())
        {
            saveForm();
            clearForm();
        }
        else
        {
            QMessageBox::information(this, "Warning",tr("Save Data Canceled."),"ok");
            return false;
        }
    }
    if(ans == 2)
    {
        QMessageBox::information(this, "Warning",tr("Save Data Canceled."),"ok");
        return false;
    }

    return true;
}
QString Widget::printPersonInfo(Person * p)
{
    QString print;

    print = "Name: \t" + p->getFName() + " " + p->getLName() + "\n";
    print += "Email: \t" + p->getEmail() + "\n";
    if(p->getPhone().count() == 13) //13 is the static number of characters for a number with our syntax mask
        print += "Phone: \t" + p->getPhone() + "\n";
    if(!p->getAge().isEmpty())
        print += "Age: \t" + p->getAge() + "\n";
    print += "\n";

    return print;
}
QString Widget::printAllPersonInfo()
{
    QString print;
    for(int x=0; x<personList->length(); x++)
    {
        print += (printPersonInfo(personList->at(x)));
    }

    return print;
}

bool Widget::invalidInfoPhone()
{
    int phoneDigits = inputPhone->text().count();
    if(phoneDigits > 3 && phoneDigits < 13) //user entered an incomplete number
    {
        return true;
    }
    return false;
}
bool Widget::invalidInfoAge()
{
    int age = inputAge->text().toInt();
    if(age > 122)
        return true;
    return false;
}
bool Widget::validateInfo()
{
    if(!requiredFormFilled())
    {
        QMessageBox::
                information(this, "Error Message"
                            ,tr("You must at least fill out the required fields to submit your information.")
                            ,"ok");
        return false;
    }
    if(invalidInfoPhone())
    {
        QMessageBox::
                information(this, "Error Message"
                            ,tr("You inputted an incomplete number for Phone Number.")
                            ,"ok");
        return false;
    }
    if(invalidInfoAge())
    {
        QMessageBox::
                information(this, "Error Message"
                            ,tr("You cannot enter an age higher than the oldest person to live.")
                            ,"ok");
        return false;
    }
    //otherwise
    return true;
}

