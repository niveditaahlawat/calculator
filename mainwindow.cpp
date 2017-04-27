#include "mainwindow.h"
#include "ui_mainwindow.h"

// global constant
double firstNum = 0.0;
bool userTypingSecondNum = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)  // ui is a pointer to the user interface
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

    connect(ui->pushButton_plusminus, SIGNAL(released()), this, SLOT(unary_operator_pressed()));
    connect(ui->pushButton_percent, SIGNAL(released()), this, SLOT(unary_operator_pressed()));

    connect(ui->pushButton_plus, SIGNAL(released()), this, SLOT(binary_operator_pressed()));
    connect(ui->pushButton_minus, SIGNAL(released()), this, SLOT(binary_operator_pressed()));
    connect(ui->pushButton_multiply, SIGNAL(released()), this, SLOT(binary_operator_pressed()));
    connect(ui->pushButton_divide, SIGNAL(released()), this, SLOT(binary_operator_pressed()));

    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed()
{
    // associate button pressed with digit_pressed

    // returns a pointer to a QObject (in this case, a QPushButton)
    // cast the result of sender() to QPushButton*
    QPushButton *button = (QPushButton*)sender();

    double labelNumber;
    QString newLabel;

    if((ui->pushButton_plus->isChecked() || ui->pushButton_minus->isChecked() ||
            ui->pushButton_multiply->isChecked() || ui->pushButton_divide->isChecked()) && (!userTypingSecondNum))
    {
        // do not append new digit to old digit
        labelNumber = button->text().toDouble();
        userTypingSecondNum = true;
        // QString has a static method called number()
        newLabel = QString::number(labelNumber, 'g', 15);
    }
    else {
        if(ui->label_display->text().contains('.') && button->text() == "0") {
            // append the new digit to the old digit without converting it to type double
            newLabel = ui->label_display->text() + button->text();
        }
        else {
            // append the new digit to the old digit and convert to double
            labelNumber = (ui->label_display->text() + button->text()).toDouble();
            // convert double back to QString
            newLabel = QString::number(labelNumber, 'g', 15);
        }
    }
    ui->label_display->setText(newLabel);
}

void MainWindow::on_pushButton_decimal_released()
{
    // append . to text in label_display if . is not already present
    bool dec_present = false;
    // ui->label_display->text().contains('.')
    for (auto &x : ui->label_display->text()) {
        if (x == ".")
            dec_present = true;
    }
    if (!dec_present)
        ui->label_display->setText(ui->label_display->text() + ".");
}

void MainWindow::unary_operator_pressed()
{
    QPushButton *button = (QPushButton*) sender();
    double labelNumber;
    QString newLabel;

    // +/- button multiplies by -1
    if (button->text() == "+/-") {
        labelNumber = ui->label_display->text().toDouble();
        labelNumber = labelNumber * (-1);
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label_display->setText(newLabel);
    }

    // % button divides by 100
    if (button->text() == "%") {
        labelNumber = ui->label_display->text().toDouble();
        labelNumber = labelNumber * (.01);
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label_display->setText(newLabel);
    }
}


void MainWindow::on_pushButton_clear_released()
{
    // clear everything
    // set checked bools to false
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_divide->setChecked(false);
    // user has not yet typed second number
    userTypingSecondNum = false;
    // reset display to 0
    ui->label_display->setText("0");
}

void MainWindow::on_pushButton_equals_released()
{
    double labelNumber = 0.0;
    // firstNum is a global variable
    double secondNum = ui->label_display->text().toDouble();
    QString newLabel;

    if (ui->pushButton_plus->isChecked())
    {
        labelNumber = firstNum + secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label_display->setText(newLabel);
        // plus button is no longer selected
        ui->pushButton_plus->setChecked(false);
    }
    else if (ui->pushButton_minus->isChecked())
    {
        labelNumber = firstNum - secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label_display->setText(newLabel);
        // minus button is no longer selected
        ui->pushButton_minus->setChecked(false);
    }
    else if (ui->pushButton_multiply->isChecked())
    {
        labelNumber = firstNum * secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label_display->setText(newLabel);
        // multiply button is no longer selected
        ui->pushButton_multiply->setChecked(false);
    }
    else if (ui->pushButton_divide->isChecked())
    {
        labelNumber = firstNum / secondNum;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label_display->setText(newLabel);
        // divide button is no longer selected
        ui->pushButton_divide->setChecked(false);
    }
    userTypingSecondNum = false;
}

void MainWindow::binary_operator_pressed()
{
    QPushButton *button = (QPushButton*) sender();
    // set the checked property of the button that was pressed to true

    firstNum = ui->label_display->text().toDouble();
    button->setChecked(true);

}
