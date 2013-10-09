#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete qcd;

}

void MainWindow::on_sp_progress_bar_valueChanged(int value)
{

}

void MainWindow::on_detect_bot_button_clicked()
{
    qcd = new QColorDialog();
    qcd->show();
}
