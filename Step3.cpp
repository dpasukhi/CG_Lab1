
#include "Step3.h"
#include "Step1.h"





QPixmap Dilation(QLabel *Picture, const QString &path)
{
    QImage im (Convert_to_binary(path));
    int x=im.width();
    long int vRed=0,vGreen=0, vBlue=0,Avg=0;
    int Red,Blue,Green;
    int y=im.height();
    QRgb pix;
}
