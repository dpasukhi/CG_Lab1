#include "Step3.h"

inline QPixmap Dilation_Bin(QLabel* Picture,QProgressBar& pb, const QString& path)
{
    pb.show();
    pb.setValue(0);
    QImage im(path);
    const int x=im.width();
    const int y=im.height();
    double num=y*2/100;
    for(int i=0;i<y;i++)
    {
        if(i%static_cast<int>(num)==0&&i!=0)
            pb.setValue(pb.value()+1);
        for(int j=0;j<x;j++)
        {
            if(QRgb(im.pixel(j,i)<qRgb(127,127,127)))
            {
                im.setPixel(j,i,qRgb(0,0,0)) ;
            }
            else im.setPixel(j,i,qRgb(255,255,255));
        }
    }
    int mKernelRadius =1;
    QImage result(im);

    bool matrix[3][3];

    matrix[0][0]=false;
    matrix[0][1]=true;
    matrix[0][2]=false;

    matrix[1][0]=true;
    matrix[1][1]=true;
    matrix[1][2]=true;

    matrix [2][0]=false;
    matrix [2][1]=true;
    matrix [2][2]=false;

    int idX,idY;
    for(int j=0;j<y;++j){
        if(j%static_cast<int>(num)==0&&j!=0)
            pb.setValue(pb.value()+1);
        for(int i=0;i<x;++i)
        {
            int max=0;
            for(int l=-mKernelRadius;l<=mKernelRadius;++l)
                for(int k=-mKernelRadius;k<=mKernelRadius;++k){
                    idX=std::clamp(int(i+k),0,int(x-1));
                    idY=std::clamp(int(j+l),0,int(y-1));
                    if(matrix[l][k]&&qRed(im.pixel(idX,idY))>max)
                    {
                        max=qRed(im.pixel(idX,idY));
                    }
                }
            if(max>200)
                result.setPixel(i,j,qRgb(255,255,255));
            else
                result.setPixel(i,j,qRgb(0,0,0));
        }
    }

    QPixmap Pixmap=QPixmap::fromImage(result);
    Picture->setPixmap(Pixmap);
    pb.setValue(100);
    pb.hide();
    return Pixmap;
}
inline QPixmap Dilation(QLabel* Picture,QProgressBar& pb, const QString& path)
{
    pb.show();
    pb.setValue(0);
    QImage im(path);
    const int x=im.width();
    const int y=im.height();
    double num=y/100;
    int mKernelRadius =1;
    QImage result(im);

    bool matrix[3][3];

    matrix[0][0]=false;
    matrix[0][1]=true;
    matrix[0][2]=false;

    matrix[1][0]=true;
    matrix[1][1]=true;
    matrix[1][2]=true;

    matrix [2][0]=false;
    matrix [2][1]=true;
    matrix [2][2]=false;

    int idX,idY;
    for(int j=0;j<y;++j){
        if(j%static_cast<int>(num)==0&&j!=0)
            pb.setValue(pb.value()+1);
        for(int i=0;i<x;++i)
        {
            QRgb max=qRgb(0,0,0);
            for(int l=-mKernelRadius;l<=mKernelRadius;++l)
                for(int k=-mKernelRadius;k<=mKernelRadius;++k){
                    idX=std::clamp(int(i+k),0,int(x-1));
                    idY=std::clamp(int(j+l),0,int(y-1));
                    if(matrix[l][k]&&im.pixel(idX,idY)>max)
                    {
                        max=im.pixel(idX,idY);
                    }
                }
            result.setPixel(i,j,max);
        }
    }

    QPixmap Pixmap=QPixmap::fromImage(result);
    Picture->setPixmap(Pixmap);
    pb.setValue(100);
    pb.hide();
    return Pixmap;
}
inline QPixmap Erosion(QLabel* Picture,QProgressBar& pb, const QString& path)
{
    pb.show();
    pb.setValue(0);
    QImage im(path);
    const int x=im.width();
    const int y=im.height();
    double num=y/100;
    int mKernelRadius =1;
    QImage result(im);

    bool matrix[3][3];

    matrix[0][0]=false;
    matrix[0][1]=true;
    matrix[0][2]=false;

    matrix[1][0]=true;
    matrix[1][1]=true;
    matrix[1][2]=true;

    matrix [2][0]=false;
    matrix [2][1]=true;
    matrix [2][2]=false;

    int idX,idY;
    for(int j=0;j<y;++j)
    {
        if(j%static_cast<int>(num)==0&&j!=0)
            pb.setValue(pb.value()+1);
        for(int i=0;i<x;++i)
        {
            QRgb max(qRgb(255,255,255));
            for(int l=-mKernelRadius;l<=mKernelRadius;++l)
                for(int k=-mKernelRadius;k<=mKernelRadius;++k){
                    idX=std::clamp(int(i+k),0,int(x-1));
                    idY=std::clamp(int(j+l),0,int(y-1));
                    if(matrix[l][k]&&im.pixel(idX,idY)<max)
                    {
                        max=im.pixel(idX,idY);
                    }
                }
            result.setPixel(i,j,max);
        }
    }

    QPixmap Pixmap=QPixmap::fromImage(result);
    Picture->setPixmap(Pixmap);
    pb.setValue(100);
    pb.hide();
    return Pixmap;
}
inline QPixmap Erosion_Bin(QLabel* Picture,QProgressBar& pb, const QString& path)
{
    pb.show();
    pb.setValue(0);
    QImage im(path);
    const int x=im.width();
    const int y=im.height();
    double num=y*2/100;
    for(int i=0;i<y;i++){
        if(i%static_cast<int>(num)==0&&i!=0)
            pb.setValue(pb.value()+1);
        for(int j=0;j<x;j++)
        {
            if(QRgb(im.pixel(j,i)<qRgb(127,127,127)))
            {
                im.setPixel(j,i,qRgb(0,0,0)) ;
            }
            else im.setPixel(j,i,qRgb(255,255,255));
        }
    }
    int mKernelRadius =1;
    QImage result(im);

    bool matrix[3][3];

    matrix[0][0]=false;
    matrix[0][1]=true;
    matrix[0][2]=false;

    matrix[1][0]=true;
    matrix[1][1]=true;
    matrix[1][2]=true;

    matrix [2][0]=false;
    matrix [2][1]=true;
    matrix [2][2]=false;

    int idX,idY;
    for(int j=0;j<y;++j){
        if(j%static_cast<int>(num)==0&&j!=0)
            pb.setValue(pb.value()+1);
        for(int i=0;i<x;++i)
        {
            int min=255;
            for(int l=-mKernelRadius;l<=mKernelRadius;++l)
                for(int k=-mKernelRadius;k<=mKernelRadius;++k){
                    idX=std::clamp(int(i+k),0,int(x-1));
                    idY=std::clamp(int(j+l),0,int(y-1));
                    if(matrix[l][k]&&qRed(im.pixel(idX,idY))<min)
                    {
                        min=qRed(im.pixel(idX,idY));
                    }
                }
            if(min>200)
                result.setPixel(i,j,qRgb(255,255,255));
            else
                result.setPixel(i,j,qRgb(0,0,0));
        }
    }

    QPixmap Pixmap=QPixmap::fromImage(result);
    Picture->setPixmap(Pixmap);
    pb.setValue(100);
    pb.hide();
    return Pixmap;
}

inline QPixmap Dilation_Bin(QPixmap pm)
{
    QImage im(pm.toImage());
    const int x=im.width();
    const int y=im.height();
    for(int i=0;i<y;i++)
        for(int j=0;j<x;j++)
        {
            if(QRgb(im.pixel(j,i)<qRgb(127,127,127)))
            {
                im.setPixel(j,i,qRgb(0,0,0)) ;
            }
            else im.setPixel(j,i,qRgb(255,255,255));
        }

    int mKernelRadius =1;
    QImage result(im);

    bool matrix[3][3];

    matrix[0][0]=false;
    matrix[0][1]=true;
    matrix[0][2]=false;

    matrix[1][0]=true;
    matrix[1][1]=true;
    matrix[1][2]=true;

    matrix [2][0]=false;
    matrix [2][1]=true;
    matrix [2][2]=false;

    int idX,idY;
    for(int j=0;j<y;++j)
        for(int i=0;i<x;++i)
        {
            int max=0;
            for(int l=-mKernelRadius;l<=mKernelRadius;++l)
                for(int k=-mKernelRadius;k<=mKernelRadius;++k){
                    idX=std::clamp(int(i+k),0,int(x-1));
                    idY=std::clamp(int(j+l),0,int(y-1));
                    if(matrix[l][k]&&qRed(im.pixel(idX,idY))>max)
                    {
                        max=qRed(im.pixel(idX,idY));
                    }
                }
            if(max>200)
                result.setPixel(i,j,qRgb(255,255,255));
            else
                result.setPixel(i,j,qRgb(0,0,0));
        }

    QPixmap Pixmap=QPixmap::fromImage(result);
    return Pixmap;
}
inline QPixmap Dilation(QPixmap pm)
{
    QImage im(pm.toImage());
    const int x=im.width();
    const int y=im.height();

    int mKernelRadius =1;
    QImage result(im);

    bool matrix[3][3];

    matrix[0][0]=false;
    matrix[0][1]=true;
    matrix[0][2]=false;

    matrix[1][0]=true;
    matrix[1][1]=true;
    matrix[1][2]=true;

    matrix [2][0]=false;
    matrix [2][1]=true;
    matrix [2][2]=false;

    int idX,idY;
    for(int j=0;j<y;++j)
        for(int i=0;i<x;++i)
        {
            QRgb max=qRgb(0,0,0);
            for(int l=-mKernelRadius;l<=mKernelRadius;++l)
                for(int k=-mKernelRadius;k<=mKernelRadius;++k){
                    idX=std::clamp(int(i+k),0,int(x-1));
                    idY=std::clamp(int(j+l),0,int(y-1));
                    if(matrix[l][k]&&im.pixel(idX,idY)>max)
                    {
                        max=im.pixel(idX,idY);
                    }
                }
            result.setPixel(i,j,max);
        }

    QPixmap Pixmap=QPixmap::fromImage(result);
    return Pixmap;
}
inline QPixmap Erosion(QPixmap px)
{
    QImage im(px.toImage());
    const int x=im.width();
    const int y=im.height();

    int mKernelRadius =1;
    QImage result(im);

    bool matrix[3][3];

    matrix[0][0]=false;
    matrix[0][1]=true;
    matrix[0][2]=false;

    matrix[1][0]=true;
    matrix[1][1]=true;
    matrix[1][2]=true;

    matrix [2][0]=false;
    matrix [2][1]=true;
    matrix [2][2]=false;

    int idX,idY;
    for(int j=0;j<y;++j)
        for(int i=0;i<x;++i)
        {
            QRgb max(qRgb(255,255,255));
            for(int l=-mKernelRadius;l<=mKernelRadius;++l)
                for(int k=-mKernelRadius;k<=mKernelRadius;++k){
                    idX=std::clamp(int(i+k),0,int(x-1));
                    idY=std::clamp(int(j+l),0,int(y-1));
                    if(matrix[l][k]&&im.pixel(idX,idY)<max)
                    {
                        max=im.pixel(idX,idY);
                    }
                }
            result.setPixel(i,j,max);
        }

    QPixmap Pixmap=QPixmap::fromImage(result);
    return Pixmap;
}
inline QPixmap Erosion_Bin(QPixmap px)
{
    QImage im(px.toImage());
    const int x=im.width();
    const int y=im.height();
    for(int i=0;i<y;i++)
        for(int j=0;j<x;j++)
        {
            if(QRgb(im.pixel(j,i)<qRgb(127,127,127)))
            {
                im.setPixel(j,i,qRgb(0,0,0)) ;
            }
            else im.setPixel(j,i,qRgb(255,255,255));
        }

    int mKernelRadius =1;
    QImage result(im);

    bool matrix[3][3];

    matrix[0][0]=false;
    matrix[0][1]=true;
    matrix[0][2]=false;

    matrix[1][0]=true;
    matrix[1][1]=true;
    matrix[1][2]=true;

    matrix [2][0]=false;
    matrix [2][1]=true;
    matrix [2][2]=false;

    int idX,idY;
    for(int j=0;j<y;++j)
        for(int i=0;i<x;++i)
        {
            int min=255;
            for(int l=-mKernelRadius;l<=mKernelRadius;++l)
                for(int k=-mKernelRadius;k<=mKernelRadius;++k){
                    idX=std::clamp(int(i+k),0,int(x-1));
                    idY=std::clamp(int(j+l),0,int(y-1));
                    if(matrix[l][k]&&qRed(im.pixel(idX,idY))<min)
                    {
                        min=qRed(im.pixel(idX,idY));
                    }
                }
            if(min>200)
                result.setPixel(i,j,qRgb(255,255,255));
            else
                result.setPixel(i,j,qRgb(0,0,0));
        }

    QPixmap Pixmap=QPixmap::fromImage(result);
    return Pixmap;
}


QPixmap Closing(QLabel *Picture, const QString &path)
{
    QPixmap res=Dilation(QPixmap(path));
    res=Erosion(res);
    Picture->setPixmap(res);
    return  res;

}

QPixmap Opening(QLabel *Picture, const QString &path)
{
    QPixmap res=Erosion(QPixmap(path));
    res=Dilation(res);
    Picture->setPixmap(res);
    return  res;
}
QPixmap Closing_Bin(QLabel *Picture, const QString &path)
{
    QPixmap res=Dilation_Bin(QPixmap(path));
    res=Erosion_Bin(res);
    Picture->setPixmap(res);
    return  res;

}

QPixmap Opening_Bin(QLabel *Picture, const QString &path)
{
    QPixmap res=Erosion_Bin(QPixmap(path));
    res=Dilation_Bin(res);
    Picture->setPixmap(res);
    return  res;
}
