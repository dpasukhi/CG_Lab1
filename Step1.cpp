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
            Blue=std::clamp(static_cast<int>(qBlue(pix)*Avg)/static_cast<int>(vBlue),0,255);
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
            int ligt=static_cast<int>((static_cast<double>(pix.lightness()-min.lightness())/static_cast<double>(max.lightness()-min.lightness()))*255.);
            //int ligt=static_cast<int>((pix.lightness()/255.)*255);
            ligt=std::clamp(ligt,0,255);
            std::cout<<pix.lightness()<<" max"<<max.lightness()<<" min"<<min.lightness()<<"ligt"<<ligt<< " New ";
            pix.setHsl(pix.hue(),pix.saturation(),ligt);
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


QPixmap GrayScale(QLabel *Picture, QProgressBar &pb, const QString &path)
{
    pb.show();
    pb.setValue(0);
    QImage* im = new QImage(path);
    int x=im->width();
    int Red,Blue,Green;
    int y=im->height();
    QRgb pix;

    double num=x/100;
    for(int i=0;i<x;++i)
    {
        if(i%static_cast<int>(num)==0&&i!=0)
            pb.setValue(pb.value()+1);
        for(int j=0;j<y;++j)
        {
            pix=im->pixel(i,j);
            Red=std::clamp(static_cast<int>(qRed(pix)),0,255);
            Green=std::clamp(static_cast<int>(qGreen(pix)),0,255);
            Blue=std::clamp(static_cast<int>(qBlue(pix)),0,255);
            int intens=Red*0.299+Green*0.587+Blue*0.114;
            intens=std::clamp(intens,0,255);
            im->setPixel(i,j,qRgb(intens,intens,intens));
        }

    }        QPixmap Pixmap=QPixmap::fromImage(*im);
    Picture->setPixmap(Pixmap);
    pb.setValue(100);
    pb.hide();
    return Pixmap;
}

QPixmap Sepya(QLabel *Picture, QProgressBar &pb, const QString &path)
{
    pb.show();
    pb.setValue(0);
    QImage* im = new QImage(path);
    int x=im->width();
    int Red,Blue,Green;
    int y=im->height();
    QRgb pix;

    double num=x/100;
    for(int i=0;i<x;++i)
    {
        if(i%static_cast<int>(num)==0&&i!=0)
            pb.setValue(pb.value()+1);
        for(int j=0;j<y;++j)
        {
            pix=im->pixel(i,j);
            Red=std::clamp(static_cast<int>(qRed(pix)),0,255);
            Green=std::clamp(static_cast<int>(qGreen(pix)),0,255);
            Blue=std::clamp(static_cast<int>(qBlue(pix)),0,255);
            int intens=Red*0.299+Green*0.587+Blue*0.114;
            int k=15;
            int rRed=std::clamp(intens+2*k,0,255);
            int rGreen=std::clamp(static_cast<int>(intens+0.5*k),0,255);
            int rBlue=std::clamp(intens-k,0,255);
            intens=std::clamp(intens,0,255);
            im->setPixel(i,j,qRgb(rRed,rGreen,rBlue));
        }

    }
    QPixmap Pixmap=QPixmap::fromImage(*im);
    Picture->setPixmap(Pixmap);
    pb.setValue(100);
    pb.hide();
    return Pixmap;
}

QPixmap Lighter_Filter(QLabel *Picture, QProgressBar &pb, const QString &path)
{
    pb.show();
    pb.setValue(0);
    QImage* im = new QImage(path);
    int x=im->width();
    int Red,Blue,Green;
    int y=im->height();
    QRgb pix;

    double num=x/100;
    for(int i=0;i<x;++i)
    {
        if(i%static_cast<int>(num)==0&&i!=0)
            pb.setValue(pb.value()+1);
        for(int j=0;j<y;++j)
        {
            pix=im->pixel(i,j);
            Red=std::clamp(static_cast<int>(qRed(pix)),0,255);
            Green=std::clamp(static_cast<int>(qGreen(pix)),0,255);
            Blue=std::clamp(static_cast<int>(qBlue(pix)),0,255);
            int k=15;
            int rRed=std::clamp(Red+k,0,255);
            int rGreen=std::clamp(Green+k,0,255);
            int rBlue=std::clamp(Blue +k,0,255);
            im->setPixel(i,j,qRgb(rRed,rGreen,rBlue));
        }

    }
    QPixmap Pixmap=QPixmap::fromImage(*im);
    Picture->setPixmap(Pixmap);
    pb.setValue(100);
    pb.hide();
    return Pixmap;
}


QPixmap Sharpness(QLabel *Picture, QProgressBar &pb, const QString &path)
{

    QImage* im = new QImage(path);
    QImage result(*im);
    const int x=im->width();
    const int y=im->height();
    pb.show();
    pb.setValue(0);
    int Red,Blue,Green;
    QRgb pix;
    int matrix[3][3];
    double num=x/100;
    int mKernelRadius=1;
    matrix[0][0]=0;
    matrix[0][1]=-1;
    matrix[0][2]=0;
    matrix[1][0]=-1;
    matrix[1][1]=5;
    matrix[1][2]=-1;
    matrix[2][0]=0;
    matrix[2][1]=-1;
    matrix[2][2]=0;
    int idX=0,idY=0;
    for(int j=0;j<y;++j)
    {
        if(j%static_cast<int>(num)==0&&j!=0)
            pb.setValue(pb.value()+1);
        for(int i=0;i<x;++i)
        {
            Red=Blue=Green=0;
            for(int l=-mKernelRadius;l<=mKernelRadius;++l)
                for(int k=-mKernelRadius;k<=mKernelRadius;++k)
                {
                    idX=std::clamp(int(i+k),0,int(x-1));
                    idY=std::clamp(int(j+l),0,int(y-1));
                    pix=im->pixel(idX,idY);
                    Red+=(qRed(pix)*matrix[k+mKernelRadius][l+mKernelRadius]);
                    Green+=(qGreen(pix)*matrix[k+mKernelRadius][l+mKernelRadius]);
                    Blue+=(qBlue(pix)*matrix[k+mKernelRadius][l+mKernelRadius]);
                }
            Blue=std::clamp(Blue,0, 255);
            Red=std::clamp(Red,0,255);
            Green=std::clamp(Green,0,255);
            result.setPixel(i,j,qRgb(Red,Green,Blue));
        }
    }
    QPixmap Pixmap=QPixmap::fromImage(result);
    delete  im;
    Picture->setPixmap(Pixmap);
    pb.setValue(100);
    pb.hide();
    return Pixmap;
}

QPixmap Sobel(QLabel *Picture, QProgressBar &pb, const QString &path)
{
    int GX[3][3];
    int GY[3][3];

    GX[0][0] = -1; GX[0][1] = 0; GX[0][2] = 1;
    GX[1][0] = -2; GX[1][1] = 0; GX[1][2] = 2;
    GX[2][0] = -1; GX[2][1] = 0; GX[2][2] = 1;

    GY[0][0] =  1; GY[0][1] = 2; GY[0][2] = 1;
    GY[1][0] =  0; GY[1][1] = 0; GY[1][2] = 0;
    GY[2][0] = -1; GY[2][1] = -2; GY[2][2] = -1;

    QImage* im = new QImage(path);
    QImage result(*im);
    const int x=im->width();
    const int y=im->height();
    pb.show();
    pb.setValue(0);
    int RedX,BlueX,GreenX;
    int RedY,BlueY,GreenY;
    int RedS,BlueS,GreenS;
    QRgb pix;
    double num=x/100;
    int mKernelRadius=1;
    int idX=0,idY=0;
    int sumX,sumY;
    for(int j=0;j<y;++j)
    {
        if(j%static_cast<int>(num)==0&&j!=0)
            pb.setValue(pb.value()+1);
        for(int i=0;i<x;++i)
        {
            RedX=BlueX=GreenX=RedY=BlueY=GreenY=0;
            for(int l=-mKernelRadius;l<=mKernelRadius;++l)
                for(int k=-mKernelRadius;k<=mKernelRadius;++k)
                {
                    idX=std::clamp(int(i+k),0,int(x-1));
                    idY=std::clamp(int(j+l),0,int(y-1));
                    pix=im->pixel(idX,idY);
                    RedX+=(qRed(pix)*GX[k+mKernelRadius][l+mKernelRadius]);
                    GreenX+=(qGreen(pix)*GX[k+mKernelRadius][l+mKernelRadius]);
                    BlueX+=(qBlue(pix)*GX[k+mKernelRadius][l+mKernelRadius]);
                    RedY+=(qRed(pix)*GY[k+mKernelRadius][l+mKernelRadius]);
                    GreenY+=(qGreen(pix)*GY[k+mKernelRadius][l+mKernelRadius]);
                    BlueY+=(qBlue(pix)*GY[k+mKernelRadius][l+mKernelRadius]);
                }
            BlueS=std::clamp(BlueX+BlueY,0, 255);
            RedS=std::clamp(RedX+RedY,0,255);
            GreenS=std::clamp(GreenX+GreenY,0,255);
            result.setPixel(i,j,qRgb(RedS,GreenS,BlueS));
        }
    }
    QPixmap Pixmap=QPixmap::fromImage(result);
    delete  im;
    Picture->setPixmap(Pixmap);
    pb.setValue(100);
    pb.hide();
    return Pixmap;

}
