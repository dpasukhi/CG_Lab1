#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QErrorMessage"
#include "Step1.cpp"
#include "Step2.cpp"
#include "Step3.cpp"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    IsCreate=false;
    ui->setupUi(this);
    connect(ui->Save,SIGNAL(triggered()),SLOT(slotSave()));
    connect(ui->Load,SIGNAL(triggered()),SLOT(slotLoad()));
    connect(ui->Glass,SIGNAL(triggered()),SLOT(slotGlass()));
    connect(ui->Gray_World,SIGNAL(triggered()),SLOT(slotGray_World()));
    connect(ui->Sharpness,SIGNAL(triggered()),SLOT(slotSharpness()));
    connect(ui->Stretching,SIGNAL(triggered()),SLOT(slotStretching()));
    connect(ui->Median,SIGNAL(triggered()),SLOT(slotMedian()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotLoad()
{

   QString filePath= QFileDialog::getOpenFileName(this,tr("Open Image"),QDir::homePath(),tr("Image Files (*.png *.jpg *.bmp)"));
   path=filePath;
    ui->Image->setPixmap((QPixmap(filePath)));
    IsCreate=true;
}

void MainWindow::slotSave()
{
    if(IsCreate){
        QString file_name = QFileDialog::getSaveFileName(this, tr("Save File"),QDir::homePath(), tr("Images (*.png *.xpm *.jpg)"));
        if(ui->Image->pixmap()->save(file_name,"PNG"))
            QErrorMessage();
    }
}

void MainWindow::slotGray_World()
{
    if(IsCreate)
        GrayWorld(ui->Image,path);
}

void MainWindow::slotMedian()
{
    if(IsCreate)
        MedFilter(ui->Image,path);
}

