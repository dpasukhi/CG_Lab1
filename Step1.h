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
#include <QProgressBar>

inline QPixmap GrayWorld(QLabel* Picture,QProgressBar& pb, const QString& path);
inline QPixmap MedFilter(QLabel* Picture,QProgressBar& pb, const QString& path);
inline QPixmap Glass(QLabel* Picture,QProgressBar& pb, const QString& path);
inline QPixmap Motion_blur(QLabel* Picture,QProgressBar& pb, const QString& path);
inline QImage Convert_to_binary(const QString &path);
#endif // STEP1_H
