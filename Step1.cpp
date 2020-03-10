#include "Step1.h"
inline QPixmap GrayWorld(QLabel* Picture, const QString& path)
{
    QImage* im = new QImage(path);
    unsigned int x=im->width();
    unsigned long int vRed=0,vGreen=0, vBlue=0,Avg=0;
    unsigned int Red,Blue,Green;
    unsigned int y=im->height();
    QRgb pix;

    for(unsigned int i=0;i<x;++i)
        for(unsigned int j=0;j<y;++j)
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
    for(unsigned int i=0;i<x;++i)
        for(unsigned int j=0;j<y;++j)
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
inline QPixmap MedFilter(QLabel* Picture, const QString& path)
{
    QImage* im = new QImage(path);
    unsigned int x=im->width();
    unsigned int y=im->height();
    QRgb pix[9];
    for(unsigned int i=1;i<x-1;++i)
        for(unsigned int j=1;j<y-1;++j)
        {
            pix[0]=im->pixel(i-1,j-1);
            pix[1]=im->pixel(i,j-1);
            pix[2]=im->pixel(i+1,j-1);
            pix[3]=im->pixel(i-1,j);
            pix[4]=im->pixel(i,j);
            pix[5]=im->pixel(i+1,j);
            pix[6]=im->pixel(i-1,j+1);
            pix[7]=im->pixel(i,j+1);
            pix[8]=im->pixel(i+1,j+1);
            std::sort(pix,pix+9);
            im->setPixel(i,j,pix[4]);
        }
    QPixmap Pixmap=QPixmap::fromImage(*im);
    delete  im;
    Picture->setPixmap(Pixmap);
    return Pixmap;
}
inline QPixmap Glass(QLabel *Picture, const QString &path)
{
    QImage* im = new QImage(path);
    QImage im2(*im);
    unsigned int x=im->width();
    unsigned int y=im->height();
    QRandomGenerator gn;
    for(unsigned int i=0;i<x;++i)
        for(unsigned int j=0;j<y;++j)
        {
            im2.setPixel(i,j,im->pixel(i+(gn.generateDouble()*1.0)*10,j+(gn.generateDouble()*1.0)*10));
        }

    QPixmap Pixmap=QPixmap::fromImage(im2);
    delete  im;
    Picture->setPixmap(Pixmap);
    return Pixmap;
}
inline QPixmap Motion_blur(QLabel *Picture, const QString &path)
{
    QImage* im = new QImage(path);
    const int x=im->width();
    const int y=im->height();
    QRgb Red,Blue,Green;
    QRgb pix;
    double matrix[10][10];

    for(int indM_X=0;indM_X<10;indM_X++)
    for(int indM_Y=0;indM_Y<10;indM_Y++)
    {
        if(indM_X==indM_Y)
            matrix[indM_X][indM_Y]=0.1;
        else matrix[indM_X][indM_Y]=0;

    }
    int idX,idY;
    for(int i=0;i<x;++i)
        for(int j=0;j<y;++j)
        {
            Red=0;Green=0;Blue=0;
            for(int l=-5;l<=5;++l)
                for(int k=-5;k<=5;++k){
                    idX=std::clamp(int(i+k),0,int(x-1));
                    idY=std::clamp(int(j+l),0,int(y-1));
                    pix=im->pixel(idX,idY);
                    Red+=(qRed(pix)*matrix[k+4][l+4]);
                    Green+=(qGreen(pix)*matrix[k+4][l+4]);
                    Blue+=(qBlue(pix)*matrix[k+4][l+4]);
                }
            im->setPixel(i,j,qRgb(std::clamp(int(Red),0,255),std::clamp(int(Green),0,255),std::clamp(int(Blue),0,255)));
        }

    QPixmap Pixmap=QPixmap::fromImage(*im);
    delete  im;
    Picture->setPixmap(Pixmap);
    return Pixmap;
}

QImage Convert_to_binary(const QString &path)
{
    QImage im(path);
    QVector<QRgb> color(2);
    color[0] = QColor(Qt::white).rgb();
    color[1] = QColor(Qt::black).rgb();
    im=im.convertToFormat(QImage::Format_Mono,color);
    return im;
}
