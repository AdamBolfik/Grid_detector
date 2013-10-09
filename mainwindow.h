#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    

private slots:
    void on_sp_progress_bar_valueChanged(int value);

    void on_detect_bot_button_clicked();

private:
    Ui::MainWindow *ui;
    QColorDialog *qcd;

};

#endif // MAINWINDOW_H
