#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set column count and headers
    ui->tableWidget->setColumnCount(3);
    QStringList headers;
    headers << "Column 1" << "Column 2" << "Column 3";
    ui->tableWidget->setHorizontalHeaderLabels(headers);

    // Add rows and data
    ui->tableWidget->setRowCount(3);
    ui->tableWidget->setItem(0, 0, new QTableWidgetItem("Item 0,0"));
    ui->tableWidget->setItem(0, 1, new QTableWidgetItem("Item 0,1"));
    ui->tableWidget->setItem(0, 2, new QTableWidgetItem("Item 0,2"));

    ui->tableWidget->setItem(1, 0, new QTableWidgetItem("Item 1,0"));
    ui->tableWidget->setItem(1, 1, new QTableWidgetItem("Item 1,1"));
    ui->tableWidget->setItem(1, 2, new QTableWidgetItem("Item 1,2"));

    ui->tableWidget->setItem(2, 0, new QTableWidgetItem("Item 2,0"));
    ui->tableWidget->setItem(2, 1, new QTableWidgetItem("Item 2,1"));
    ui->tableWidget->setItem(2, 2, new QTableWidgetItem("Item 2,2"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
// just testing the git commits
// testing change in main master branch
