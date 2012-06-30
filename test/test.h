#ifndef TEST_H
#define TEST_H

#include <QDialog>
#include <QPaintEvent>
#include <QWidget>
#include <QPainter>
#include <QPicture>
#include <QPixmap>
#include <QTimer>
#include <QLabel>
#include <QFrame>
#include <QPalette>
#include <QResizeEvent>
#include <QBrush>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_legend.h>
#include <qwt_series_data.h>
#include <QVector>
#include <ctime>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <cmath>

class QLabel;

class Test : public QDialog
{
    Q_OBJECT

public:
    Test(QWidget *parent = 0);

    int init();
    void read_info();
    QImage backgroundImage;
    int i;
    int left_speed;
    char buf[4];
    char temperature[4];
    void setFixedSize(int w, int h);

protected:
    void paintEvent(QPaintEvent * event);
    void resizeEvent(QResizeEvent *event);
    int m_nTimerId;

private:
    QLabel *tempretureShowed;
    QLabel *showedText;
    QTimer *timer;
    QwtPlotCurve *temperatureCurve;
    QwtPlot *temperaturePlot;
    QVector <double> timeUsed;
    QVector <double> randomGet;
    int times;
    int rands;
};

#endif // TEST_H
