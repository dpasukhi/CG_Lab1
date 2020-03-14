#include "Step1.h"
inline QPixmap GrayWorld(QLabel* Picture,QProgressBar& pb, const QString& path)
{
    pb.show();
    pb.setValue(0);
    QImage* im = new QImage(path);
    int x=im->width();
    long int vRed=0,vGreen=0, vBlue=0,Avg=0;
    int Red,Blue,Green;
    int y=im->height();
    QRgb pix;

    double num=x*2/100;
    for(int i=0;i<x;++i)
    {
        if(i%static_cast<int>(num)==0&&i!=0)
            pb.setValue(pb.value()+1);
        for(int j=0;j<y;++j)
        {
            pix=im->pixel(i,j);
            vRed+=qRed(pix);
            vGreen+=qGreen(pix);
            vBlue+=qBlue(pix);
        }
    }
    vRed=static_cast<int>(vRed/static_cast<int>(x*y));
    vBlue=static_cast<int>(vBlue/static_cast<int>(x*y));
    vGreen=static_cast<int>(vGreen/static_cast<int>(x*y));
    Avg=static_cast<int>((vBlue+vRed+vGreen)/3);
    for(int i=0;i<x;++i)
    {
        if(i%static_cast<int>(num)==0&&i!=0)
            pb.setValue(pb.value()+1);
        for(int j=0;j<y;++j)
        {
            pix=im->pixel(i,j);
            Red=std::clamp(static_cast<int>(qRed(pix)*Avg)/static_cast<int>(vRed),0,255);
            Green=std::clamp(static_cast<int>(qGreen(pix)*Avg)/static_cast<int>(vGreen),0,255);
            pb.setValue(pb.value()+num);
            Blue=std::clamp(static_cast<int>(qBlue(pix)*Avg)/static_cast<int>(vBlue),0,255);
            if((i*j)%static_cast<int>(num))
                pb.setValue(pb.value()+1);
            im->setPixel(i,j,qRgb(Red,Green,Blue));
        }
    }
    QPixmap Pixmap=QPixmap::fromImage(*im);
    delete  im;
    Picture->setPixmap(Pixmap);
    pb.setValue(100);
    pb.hide();
    return Pixmap;
}
inline QPixmap MedFilter(QLabel* Picture,QProgressBar& pb, const QString& path)
{
    QImage* im = new QImage(path);
    pb.show();
    pb.setValue(0);
    unsigned int x=im->width();
    unsigned int y=im->height();
    QRgb pix[9];
    double num=x/100;
    for(unsigned int i=1;i<x-1;++i)
    {
        if(i%static_cast<int>(num)==0&&i!=0)
            pb.setValue(pb.value()+1);
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
    }
    QPixmap Pixmap=QPixmap::fromImage(*im);
    delete  im;
    Picture->setPixmap(Pixmap);
    pb.setValue(100);
    pb.hide();
    return Pixmap;
}
inline QPixmap Glass(QLabel* Picture,QProgressBar& pb, const QString& path)
{
    QImage* im = new QImage(path);
    QImage im2(*im);
    pb.show();
    pb.setValue(0);
    unsigned int x=im->width();
    unsigned int y=im->height();
    QRandomGenerator gn;
    double num=x/100;
    for(unsigned int i=0;i<x;++i)
    {
        if(i%static_cast<int>(num)==0&&i!=0)
            pb.setValue(pb.value()+1);
        for(unsigned int j=0;j<y;++j)
        {
            im2.setPixel(i,j,im->pixel(std::clamp(int(i+(gn.generateDouble()*1.0)*10),0,int(x-1)),std::clamp(int(j+(gn.generateDouble()*1.0)*10),0,int(y-1))));
        }
    }
    QPixmap Pixmap=QPixmap::fromImage(im2);
    delete  im;
    Picture->setPixmap(Pixmap);
    pb.setValue(100);
    pb.hide();
    return Pixmap;
}
inline QPixmap Motion_blur(QLabel* Picture,QProgressBar& pb, const QString& path)
{
    QImage* im = new QImage(path);
    const int x=im->width();
    const int y=im->height();
    pb.show();
    pb.setValue(0);
    QRgb Red,Blue,Green;
    QRgb pix;
    double matrix[10][10];
    double num=x/100;
    for(int indM_X=0;indM_X<10;indM_X++)
        for(int indM_Y=0;indM_Y<10;indM_Y++)
        {
            if(indM_X==indM_Y)
                matrix[indM_X][indM_Y]=0.1;
            else matrix[indM_X][indM_Y]=0;

        }
    int idX,idY;
    for(int i=0;i<x;++i)
    {
        if(i%static_cast<int>(num)==0&&i!=0)
            pb.setValue(pb.value()+1);
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
    }
    QPixmap Pixmap=QPixmap::fromImage(*im);
    delete  im;
    Picture->setPixmap(Pixmap);
    pb.setValue(100);
    pb.hide();
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

QPixmap Gisogram(QLabel *Picture, QProgressBar &pb, const QString &path)
{
    QImage im(path);
    const int x=im.width();
    const int y=im.height();
    pb.show();
    QColor max(0,0,0,0);
    QColor min(0,0,0,255);
    double num=x*2/100;
    pb.setValue(0);
    QImage result(im);
    for(int i=0;i<x;++i)
    {
        if(i%static_cast<int>(num)==0&&i!=0)
            pb.setValue(pb.value()+1);
        for(int j=0;j<y;++j)
        {
            QColor pix=im.pixelColor(i,j);
            if(pix.lightness()<min.lightness())
                min=pix;
            if(pix.lightness()>max.lightness())
                max=pix;
        }
    }
    for(int i=0;i<x;++i)
    {
        if(i%static_cast<int>(num)==0&&i!=0)
            pb.setValue(pb.value()+1);
        for(int j=0;j<y;++j)
        {
            QColor pix=im.pixelColor(i,j);
            //int ligt=static_cast<int>((static_cast<double>(pix.lightness()-min.lightness())/static_cast<double>(max.lightness()-min.lightness()))*255.);
            int ligt=static_cast<int>((pix.lightness()/255.)*255);
            ligt=std::clamp(ligt,0,255);
            std::cout<<pix.lightness()<<" max"<<max.lightness()<<" min"<<min.lightness()<<"ligt"<<ligt<< " New ";
            result.setPixel(i,j,pix.rgba());
            std::cout<<pix.lightness()<<std::endl;

        }
    }

    QPixmap Pixmap=QPixmap::fromImage(result);
    Picture->setPixmap(Pixmap);
    pb.setValue(100);
    pb.hide();
    return Pixmap;
}
