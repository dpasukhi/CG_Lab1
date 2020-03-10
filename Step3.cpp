#include <iostream>
#include "Step3.h"
#include "Step1.h"
#include <algorithm>
inline QPixmap Dilation(QLabel* Picture, const QString& path)
{
QImage* im = new QImage(path);
const int x=im->width();
const int y=im->height();
QRgb Red,Blue,Green;
//QRgb pix;
double matrix[3][3];
 matrix[0][0]=0;
 matrix[0][1]=1;
 matrix[0][2]=0;

 matrix[1][0]=1;
 matrix[1][1]=1;
 matrix[1][2]=1;

 matrix [2][0]=0;
 matrix [2][1]=1;
 matrix [2][2]=0;



int idX,idY;
for(int i=0;i<x;++i)

for(int j=0;j<y;++j)
{
    Red=0;Green=0;Blue=0;
    for(int l=-1;l<=1;++l)
        for(int k=-1;k<=1;++k){
            int radiusX = 1;
            int radiusY = 1;
            int Max = 0;
            QRgb ResultColor = qRgb(0,0,0);
            //одна из вариации как сделать черный, до этого была: QColor(Qt::black).rgb();
            for (int l = -radiusY; l <= radiusY; l++)
            {
                for (int k = -radiusX; k <= radiusX; k++)
                {
                    if (matrix[k + radiusX] [l + radiusY] > 0)
                    {
                         idX =std::clamp(x + k, 0, im->width() - 1);
                        idY = std::clamp(y + l, 0, im->height() - 1);

                        QRgb NeighborColor = im->pixel(idX, idY);
                     //УЗНАТЬ ПРО ГЕТПИКСЕЛЬ(правильно ли заменил)
                        int Intensity = (int)(0.36 *  qRed(NeighborColor) + 0.53 * qGreen(NeighborColor) + 0.11 * qBlue(NeighborColor));
                        //Исправить эту строку. Нужно брать точку ResultColor или NeighbourColor исходная строчка: int Intensity = (int)(0.36 * NeighborColor.R + 0.53 * NeighborColor.G + 0.11 * NeighborColor.B);
                        if (Intensity > Max)
                        {
                            Max = Intensity;
                            ResultColor = NeighborColor;
                        }
                    }
                }
                im->setPixel(i,j,qRgb(std::clamp(int(Red),0,255),std::clamp(int(Green),0,255),std::clamp(int(Blue),0,255)));
            }

            QPixmap Pixmap=QPixmap::fromImage(*im);
            delete im;
            Picture->setPixmap(Pixmap);
            return Pixmap;
        }
}
}
