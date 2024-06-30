#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QStandardPaths>
#include <QPushButton>
#include <QCloseEvent>
#include <QDir>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // buttons
    QPushButton *createTableButton = new QPushButton("Create Table");
    QPushButton *viewTableButton = new QPushButton("View Table");
    QPushButton *defaultTablesButton = new QPushButton("Default Tables");

    createTableButton->setMinimumSize(100, 50);
    viewTableButton->setMinimumSize(100, 50);
    defaultTablesButton->setMinimumSize(100, 50);

    // Connect buttons to slots
    connect(createTableButton, &QPushButton::clicked, this, &MainWindow::createTable);
    connect(viewTableButton, &QPushButton::clicked, this, &MainWindow::viewTable);
    connect(defaultTablesButton, &QPushButton::clicked, this, &MainWindow::defaultTables);

    // Create a layout for the buttons
    QVBoxLayout *buttonLayout = new QVBoxLayout;
    buttonLayout->addWidget(createTableButton);
    buttonLayout->addWidget(viewTableButton);
    buttonLayout->addWidget(defaultTablesButton);
    buttonLayout->addStretch(); // Add stretch to push buttons to the top

    // Create a widget for the buttons and set its size policy
    QWidget *buttonWidget = new QWidget;
    buttonWidget->setLayout(buttonLayout);
    buttonWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    buttonWidget->setMinimumWidth(150);

    // Set the table widget's size policy to expanding
    ui->tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // Create a layout and add the button widget and table widget to it
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(buttonWidget, 1); // Make the button widget occupy one-fifth of the space
    mainLayout->addWidget(ui->tableWidget, 4); // Make the table widget occupy the remaining space

    // Set the layout to the central widget
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);

    // Set column count and headers
    ui->tableWidget->setColumnCount(7);
    QStringList cheaders;
    cheaders << "9-10" << "10-11" << "11-12" << "12-1" << "1-2" << "2-3" << "3-4";
    ui->tableWidget->setHorizontalHeaderLabels(cheaders);

    // Set row count and headers
    ui->tableWidget->setRowCount(6);
    QStringList rheaders;
    rheaders << "Sunday" << "Monday" << "Tuesday" << "Wednesday" << "Thursday" << "Friday";
    ui->tableWidget->setVerticalHeaderLabels(rheaders);

    // Ensure columns and rows resize to fill the space
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    loadTableData();
}

MainWindow::~MainWindow()
{
    // Save table data when the application closes
    saveTableData();
    delete ui;
}

void MainWindow::saveTableData()
{
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + QDir::separator() + "tabledata.json";
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open save file.");
        return;
    }

    QJsonArray tableArray;
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
    {
        QJsonArray rowArray;
        for (int column = 0; column < ui->tableWidget->columnCount(); ++column)
        {
            QTableWidgetItem *item = ui->tableWidget->item(row, column);
            if (item)
                rowArray.append(item->text());
            else
                rowArray.append("");
        }
        tableArray.append(rowArray);
    }

    QJsonDocument saveDoc(tableArray);
    file.write(saveDoc.toJson());
}

void MainWindow::loadTableData()
{
    QString filePath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation) + QDir::separator() + "tabledata.json";
    QFile file(filePath);
    if (!file.exists() || !file.open(QIODevice::ReadOnly))
    {
        qWarning("Couldn't open save file.");
        return;
    }

    QByteArray saveData = file.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(saveData));
    QJsonArray tableArray = loadDoc.array();

    ui->tableWidget->setRowCount(tableArray.size());
    for (int row = 0; row < tableArray.size(); ++row)
    {
        QJsonArray rowArray = tableArray[row].toArray();
        for (int column = 0; column < rowArray.size(); ++column)
        {
            QTableWidgetItem *item = new QTableWidgetItem(rowArray[column].toString());
            ui->tableWidget->setItem(row, column, item);
        }
    }

    //  putting correct number of rows and headers after loading data
    ui->tableWidget->setRowCount(6);
    QStringList rheaders;
    rheaders << "Sunday" << "Monday" << "Tuesday" << "Wednesday" << "Thursday" << "Friday";
    ui->tableWidget->setVerticalHeaderLabels(rheaders);

    // resizing columns and rows to fill the space after loading data
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveTableData();  //saving table before closing
    QMainWindow::closeEvent(event);
}

// slots for button actions.

void MainWindow::createTable()
{
    ui->tableWidget->clearContents();
}

void MainWindow::viewTable()
{
    // table to be viewed after create table.
    loadTableData(); // recent sdata from the file
}

void MainWindow::defaultTables()
{
    // default values for table , to be loaded on default table button event.

    QStringList defaultData = {"ENGG ", "ENVE ", "COMP ", "PROJ ", "MATHS ", "DSAM "};
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row)
    {
        for (int column = 0; column < ui->tableWidget->columnCount(); ++column)
        {
            QTableWidgetItem *item = new QTableWidgetItem(defaultData.at(column % defaultData.size()));
            ui->tableWidget->setItem(row, column, item);
        }
    }
}
