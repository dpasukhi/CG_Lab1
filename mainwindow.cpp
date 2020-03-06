#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->Save,SIGNAL(triggered()),SLOT(slotSave()));
    connect(ui->Load,SIGNAL(triggered()),SLOT(slotLoad()));
    connect(ui->Glass,SIGNAL(triggered()),SLOT(slotGlass()));
    connect(ui->Gray_World,SIGNAL(triggered()),SLOT(slotGray_World()));
    connect(ui->Sharpness,SIGNAL(triggered()),SLOT(slotSharpness()));
    connect(ui->Stretching,SIGNAL(triggered()),SLOT(slotStretching()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

