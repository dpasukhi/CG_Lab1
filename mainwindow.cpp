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
    connect(ui->Motion_blur,SIGNAL(triggered()),SLOT(slotMotion_blur()));
    connect(ui->Opening,SIGNAL(triggered()),SLOT(slotOpening()));
    connect(ui->Closing,SIGNAL(triggered()),SLOT(slot_Closing()));
    connect(ui->Erosion,SIGNAL(triggered()),SLOT(slot_Erosion()));
    connect(ui->Dilation,SIGNAL(triggered()),SLOT(slot_Dilation()));
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

void MainWindow::slotGlass()
{
    if(IsCreate)
        Glass(ui->Image,path);
}

void MainWindow::slotMotion_blur()
{
    if(IsCreate)
        Motion_blur(ui->Image,path);
}

void MainWindow::slot_Dilation()
{
//    if(IsCreate)
//        Dilation()(ui->Image,path);
}

void MainWindow::slot_Erosion()
{
//    if(IsCreate)
//        Erosion(ui->Image,path);
}

void MainWindow::slot_Opening()
{
//    if(IsCreate)
//        Opening(ui->Image,path);
}

void MainWindow::slot_Closing()
{
//    if(IsCreate)
//        Closing(ui->Image,path);
}

