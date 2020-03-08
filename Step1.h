#ifndef STEP1_H
#define STEP1_H

#include <QLabel>
#include <QImage>
#include <QRgb>
#include <QColor>
#include <algorithm>
#include <QRandomGenerator>



inline QPixmap GrayWorld(QLabel* Picture, const QString& path);
inline QPixmap MedFilter(QLabel* Picture, const QString& path);
inline QPixmap Glass(QLabel* Picture, const QString& path);

#endif // STEP1_H
