#include "test.h"
#include <QHBoxLayout>
#include <QGridLayout>
#include <iostream>
#include <QPalette>

using namespace std;

int fd;
struct termios opt;

Test::Test(QWidget *parent)
    :QDialog(parent)
{
    times = 0;
    rands = 0;
    temperaturePlot= new QwtPlot;
    temperaturePlot->setTitle("Temperature Condition");
    temperaturePlot->insertLegend(new QwtLegend(), QwtPlot::BottomLegend);
    temperaturePlot->setAxisTitle(QwtPlot::xBottom, "times/S");
    temperaturePlot->setAxisScale(QwtPlot::xBottom, 0.0, 50.0);
    temperaturePlot->setAxisTitle(QwtPlot::yLeft, "temperature/C");
    temperaturePlot->setAxisScale(QwtPlot::yLeft, 0.0, 100.0);
    temperatureCurve = new QwtPlotCurve("Temperature");
    temperatureCurve->attach(temperaturePlot);

    tempretureShowed = new QLabel(tr("Temperature:"));
    showedText = new QLabel(tr("0C"));
    QPalette pa;
    pa.setColor(QPalette::WindowText, Qt::white);
    tempretureShowed->setPalette(pa);
    showedText->setPalette(pa);

    this->setGeometry(0,0,1300,800);
    QHBoxLayout *tempLayout = new QHBoxLayout;
    tempLayout->addWidget(tempretureShowed);
    tempLayout->addWidget(showedText);
    QHBoxLayout *otherLayout = new QHBoxLayout;
    QGridLayout *mainLayout = new QGridLayout;
    QHBoxLayout *qwtPlotLayout = new QHBoxLayout;
    qwtPlotLayout->addWidget(temperaturePlot);
    mainLayout->addLayout(otherLayout, 0, 0, 10, 8);
    mainLayout->addLayout(tempLayout, 10, 0, 2, 1);
    mainLayout->addLayout(qwtPlotLayout, 0, 6, 7, 10);
    setLayout(mainLayout);
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(update()));
    timer->start(1000);
//    m_nTimerId = startTimer(1000);

}


void Test::resizeEvent(QResizeEvent *event)

{
    QDialog::resizeEvent(event);
    QPalette pal(palette());
    pal.setBrush(QPalette::Window,QBrush(backgroundImage.scaled(event->size(),
    Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
    setPalette(pal);
    setAutoFillBackground(true);
    backgroundImage.load("./beijing.png");
    

}

void Test::paintEvent(QPaintEvent *event){
    int tmp1;
    int tmp2;
    while(1){
        tmp1 = rand() % 180;
        tmp2 = rand() % 180;
        if(abs(tmp2 - tmp1) <= 90){
            break;
        }
    }
    int tmp3 = rand() % 100;
    QString temperature = QString::number(tmp3,10);
    times += 1;
    timeUsed.append(times);
    randomGet.append(tmp3);
    temperatureCurve->setSamples(timeUsed,randomGet);
    temperatureCurve->setPen(QPen(Qt::white));
    temperaturePlot->replot();
    sleep(1);
    double sudu1 = tmp1 * 1.0;
    double sudu2 = tmp2 * 1.0;
    showedText->setText(temperature);
    QPainter painter(this);
    QPixmap pix1, pix2;
    pix1.load("./sudu.png");
    pix2.load("./pianzhuan.png");
    painter.drawPixmap(0,0,450,450,pix1);
    painter.drawPixmap(0,250,450,450,pix2);
    painter.setRenderHint(QPainter::Antialiasing);

    int r = 100;

    painter.translate(QPoint(218,193));
    QPoint suduhand[3] = {
        QPoint(10, 8),
        QPoint(-4, -6),
        QPoint(-73, 73)
        };
    painter.setPen(Qt::NoPen);

    /*sudu*/
    painter.save();
    painter.setBrush(QColor(255,0,0,240));
    painter.rotate((double)((sudu1+sudu2)/2)*265/220);
    painter.drawConvexPolygon(suduhand, 3);timeUsed.append(times);
    painter.restore();


    painter.translate(QPoint(-3,298));
    QPoint pianzhuanhand[3] = {
        QPoint(r*0.1, r*0.1),
        QPoint(-r*0.1, r*0.1),
        QPoint(0, -r*0.9)
        };
    painter.setPen(Qt::NoPen);

        /*zhuanxiang*/
    painter.save();
    painter.setBrush(QColor(0,255,0,200));
    painter.rotate((double)(sudu2-sudu1));
    painter.drawConvexPolygon(pianzhuanhand, 3);
    painter.restore();
}



