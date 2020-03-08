#include "Step1.h"
inline QPixmap GrayWorld(QLabel* Picture, const QString& path)
{
    QImage* im = new QImage(path);
    int x=im->width();
    long int vRed=0,vGreen=0, vBlue=0,Avg=0;
    int Red,Blue,Green;
    int y=im->height();
    QRgb pix;

    for(int i=0;i<x;++i)
        for(int j=0;j<y;++j)
        {
            pix=im->pixel(i,j);
            vRed+=qRed(pix);
            vGreen+=qGreen(pix);
            vBlue+=qBlue(pix);
        }
    vRed=vRed/(x*y);
    vBlue=vBlue/(x*y);
    vGreen=vGreen/(x*y);
    Avg=(vBlue+vRed+vGreen)/3;
    for(int i=0;i<x;++i)
        for(int j=0;j<y;++j)
        {
            pix=im->pixel(i,j);
            Red=(qRed(pix)*Avg)/vRed;
            Green=(qGreen(pix)*Avg)/vGreen;
            Blue=(qBlue(pix)*Avg)/vBlue;
            im->setPixel(i,j,qRgb(Red,Green,Blue));

        }
    QPixmap Pixmap=QPixmap::fromImage(*im);
    delete  im;
    Picture->setPixmap(Pixmap);
    return Pixmap;

}
