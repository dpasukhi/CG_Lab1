#ifndef STEP1_H
#define STEP1_H

#include <QLabel>
#include <QImage>
#include <QRgb>
#include <QColor>
#include <algorithm>


inline QPixmap GrayWorld(QLabel* Picture, const QString& path);
inline QPixmap MedFilter(QLabel* Picture, const QString& path);
#endif // STEP1_H
