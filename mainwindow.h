#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QTranslator>
#include <QFileDialog>
#include <QLabel>
#include <QImage>
#include <QRgb>
#include <QColor>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void slotLoad();
    void slotSave();
    void slotGray_World();
    void slotMedian();
    void slotGlass();
    void slotMotion_blur();
    void slot_Dilation();
    void slot_Erosion();
    void slot_Opening();
    void slot_Closing();
private:
    Ui::MainWindow *ui;
    QString path;
    bool IsCreate;
};

#endif // MAINWINDOW_H

