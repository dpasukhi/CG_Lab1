#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Strage.h"
#include "QErrorMessage"


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

void MainWindow::slotLoad()
{

   QString filePath= QFileDialog::getOpenFileName(this,tr("Open Image"),QDir::homePath(),tr("Image Files (*.png *.jpg *.bmp)"));
    ui->Image->setPixmap((QPixmap(filePath)));
    Path_To_Image=filePath;
}

void MainWindow::slotSave()
{
    QString file_name = QFileDialog::getSaveFileName(this, tr("Save File"),QDir::homePath(), tr("Images (*.png *.xpm *.jpg)"));
    if(ui->Image->pixmap()->save(file_name,"PNG"))
     QErrorMessage();
}

