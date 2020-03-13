#ifndef STEP3_H
#define STEP3_H
#include <Step1.h>
inline QPixmap Dilation(QLabel *Picture, const QString &path);
inline QPixmap Erosion(QLabel *Picture, const QString &path);
inline QPixmap Dilation_Bin(QLabel *Picture, const QString &path);
inline QPixmap Erosion_Bin(QLabel *Picture, const QString &path);
inline QPixmap Closing(QLabel *Picture, const QString &path);
inline QPixmap Opening(QLabel *Picture, const QString &path);
inline QPixmap Closing_Bin(QLabel *Picture, const QString &path);
inline QPixmap Opening_Bin(QLabel *Picture, const QString &path);
#endif // STEP3_H
