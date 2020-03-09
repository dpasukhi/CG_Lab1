#ifndef STEP1_H
#define STEP1_H

#include <QLabel>
#include <QImage>
#include <QRgb>
#include <QColor>
#include <algorithm>
#include <QRandomGenerator>
#include <QMatrix>
#include <QGenericMatrix>
#include <QTransform>



inline QPixmap GrayWorld(QLabel* Picture, const QString& path);
inline QPixmap MedFilter(QLabel* Picture, const QString& path);
inline QPixmap Glass(QLabel* Picture, const QString& path);
inline QPixmap Motion_blur(QLabel *Picture, const QString &path);

#endif // STEP1_H
