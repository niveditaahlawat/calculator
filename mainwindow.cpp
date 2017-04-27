#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
  // ui is a pointer to the user interface
{
    ui->setupUi(this);
    // when the button is released, it will emit a signal
    // and call a slot associated with this object
    connect(ui->pushButton_0, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_1, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_2, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_3, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_4, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_5, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_6, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_7, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_8, SIGNAL(released()), this, SLOT(digit_pressed()));
    connect(ui->pushButton_9, SIGNAL(released()), this, SLOT(digit_pressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    // associate button pressed with digit_pressed

    // qDebug is a replacement for cout
    // qDebug() << "test";


    // returns a pointer to a QObject (in this case, a QPushButton)
    // cast the result of sender() to QPushButton*
    QPushButton *button = (QPushButton*)sender();

    double labelNumber;
    QString newLabel;

    // concatenate strings and then convert to double
    labelNumber = (ui->label_display->text()+button->text()).toDouble();

    // QString has a static method called number()
    newLabel = QString::number(labelNumber, 'g', 15);


    ui->label_display->setText(newLabel);
}
