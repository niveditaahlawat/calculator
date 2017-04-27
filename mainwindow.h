#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

// slots execute when signals are admitted
private slots:
    void digit_pressed();
    void on_pushButton_decimal_released();
    void unary_operator_pressed();
};

#endif // MAINWINDOW_H
