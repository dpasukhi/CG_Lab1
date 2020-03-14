#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QErrorMessage"
#include "Step1.cpp"
#include "Step3.cpp"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    IsCreate=false;
    ui->setupUi(this);
    ui->progressBar->hide();
    ui->progressBar->reset();
    connect(ui->Save,SIGNAL(triggered()),SLOT(slotSave()));
    connect(ui->Load,SIGNAL(triggered()),SLOT(slotLoad()));
    connect(ui->Glass,SIGNAL(triggered()),SLOT(slotGlass()));
    connect(ui->Gray_World,SIGNAL(triggered()),SLOT(slotGray_World()));
    connect(ui->Stretching,SIGNAL(triggered()),SLOT(slot_Gist()));
    connect(ui->Median,SIGNAL(triggered()),SLOT(slotMedian()));
    connect(ui->Motion_blur,SIGNAL(triggered()),SLOT(slotMotion_blur()));
    connect(ui->Opening_2,SIGNAL(triggered()),SLOT(slot_Opening()));
    connect(ui->Opening_Bin,SIGNAL(triggered()),SLOT(slot_Opening_Bin()));
    connect(ui->Closing_2,SIGNAL(triggered()),SLOT(slot_Closing()));
    connect(ui->Closing_Bin,SIGNAL(triggered()),SLOT(slot_Closing_Bin()));
    connect(ui->Erosion_2,SIGNAL(triggered()),SLOT(slot_Erosion()));
    connect(ui->Dilation_2,SIGNAL(triggered()),SLOT(slot_Dilation()));
    connect(ui->Erosion_Bin,SIGNAL(triggered()),SLOT(slot_Erosion_Bin()));
    connect(ui->Dilation_Bin,SIGNAL(triggered()),SLOT(slot_Dilation_Bin()));
    connect(ui->GrayScale,SIGNAL(triggered()),SLOT(slot_Gray_Scale()));
    connect(ui->Sepya,SIGNAL(triggered()),SLOT(slot_Sepya()));
    connect(ui->Lighter,SIGNAL(triggered()),SLOT(slot_Lighter()));
    connect(ui->Sharpness_2,SIGNAL(triggered()),SLOT(slot_Sharpness()));
    connect(ui->Sobel,SIGNAL(triggered()),SLOT(slot_Sobel()));
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
        GrayWorld(ui->Image,*ui->progressBar,path);
}

void MainWindow::slotMedian()
{
    if(IsCreate)
        MedFilter(ui->Image,*ui->progressBar,path);
}

void MainWindow::slotGlass()
{
    if(IsCreate)
        Glass(ui->Image,*ui->progressBar,path);
}

void MainWindow::slotMotion_blur()
{
    if(IsCreate)
        Motion_blur(ui->Image,*ui->progressBar,path);
}

void MainWindow::slot_Dilation()
{
    if(IsCreate)
        Dilation(ui->Image,*ui->progressBar,path);
}

void MainWindow::slot_Dilation_Bin()
{
    if(IsCreate)
        Dilation_Bin(ui->Image,*ui->progressBar,path);
}

void MainWindow::slot_Erosion_Bin()
{
    if(IsCreate)
        Erosion_Bin(ui->Image,*ui->progressBar,path);
}

void MainWindow::slot_Erosion()
{
    if(IsCreate)
        Erosion(ui->Image,*ui->progressBar,path);
}

void MainWindow::slot_Opening()
{
    if(IsCreate)
        Opening(ui->Image,path);
}

void MainWindow::slot_Closing()
{
    if(IsCreate)
        Closing(ui->Image,path);
}

void MainWindow::slot_Opening_Bin()
{
    if(IsCreate)
        Opening_Bin(ui->Image,path);
}

void MainWindow::slot_Gist()
{
    if(IsCreate)
        Gisogram(ui->Image,*ui->progressBar,path);
}

void MainWindow::slot_Closing_Bin()
{
    if(IsCreate)
        Closing_Bin(ui->Image,path);
}

void MainWindow::slot_Gray_Scale()
{
    if(IsCreate)
        GrayScale(ui->Image,*ui->progressBar,path);
}

void MainWindow::slot_Sepya()
{
    if(IsCreate)
        Sepya(ui->Image,*ui->progressBar,path);
}

void MainWindow::slot_Lighter()
{
    if(IsCreate)
        Lighter_Filter(ui->Image,*ui->progressBar,path);
}

void MainWindow::slot_Sharpness()
{
    if(IsCreate)
        Sharpness(ui->Image,*ui->progressBar,path);
}

void MainWindow::slot_Sobel()
{
    if(IsCreate)
        Sobel(ui->Image,*ui->progressBar,path);
}

