#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QFileDialog>
#include <QGroupBox>
#include <QLineEdit>
#include <QLabel>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QKeyEvent>
#include "functionPreprocessing.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void find_file();
    void enter_equation();

private:
    Ui::MainWindow *ui;

//1. Title
    QGroupBox *title_group();

//2. Manual input
    QLineEdit *equation_input;
    QPushButton *confirm;
    QGroupBox *manual_input_group();
//3. Upload file
    QPushButton* upload_file;
    QGroupBox *upload_group();

    QGroupBox *final;
//6. Layout
    QVBoxLayout* main_layout;
    QVBoxLayout* top_layout;
    QWidget* steps_layoutf(vector<string>);
    QGroupBox* results_layoutf(vector<string>);
    QHBoxLayout* results_layout;


};
#endif // MAINWINDOW_H
