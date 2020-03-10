
#include "Step3.h"
#include "Step1.h"





QPixmap Dilation(QLabel *Picture, const QString &path)
{
    QImage im (Convert_to_binary(path));



    int W =im.width();
      int H = im.height();
QImage result(W,H,QImage::Format_Mono);
      //   Bitmap resultImage = new Bitmap(W, H);

      // УСТАНОВИТЬ РАЗМЕРЫ СТРУКТУРНОГО ЭЛЕМЕНТА
      int MW = 3;
      int MH = 3;
      //bool[,] mask = new bool[MW, MH];
      int mask[3][3];

      mask[0][0] = 0;
      mask[0][1] = 1;
      mask[0][ 2] = 0;

      mask[1][0] = 1;
      mask[1][1] = 1;
      mask[1][ 2] = 1;

      mask[2][ 0] = 0;
      mask[2][ 1] = 1;
      mask[2][ 2] = 0;


      for (int y = MH / 2; y < H - MH / 2; y++)
      {
          for (int x = MW / 2; x < W - MW / 2; x++)
          {
              int max = 0;
              for (int j = -MH / 2; j <= MH / 2; j++)
              {
                  for (int i = -MW / 2; i <= MW / 2; i++)
                  {
                      //Console.WriteLine(sourceImage.GetPixel(x + i, y + j).ToString());
                      //Console.WriteLine(Color.White.ToArgb().ToString());
                      if ((mask[i + MW / 2] [j + MH / 2] == 1) && (qRed( im.pixel(x + i, y + j) )> max))
                      {
                          max = (qRed( im.pixel(x + i, y + j)));
                      }
                  }
                  result.setPixel(x, y, qRgb(255,max,max));
              }
          }
      }
      QPixmap Pixmap=QPixmap::fromImage(result);

      Picture->setPixmap(Pixmap);
      return Pixmap;
  }



