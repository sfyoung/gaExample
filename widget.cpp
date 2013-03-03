/****************************************************************************** 
 * Copyright (C) 2013 gaExample of Shuf Young 
 * shufyoung@gmail.com 
 * 
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU Lesser General Public 
 * License as published by the Free Software Foundation; either 
 * version 2.1 of the License, or (at your option) any later version. 
 * 
 * This program is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
 * Lesser General Public License for more details. 
 * 
 * You should have received a copy of the GNU Lesser General Public 
 * License along with this library; if not, write to the Free Software 
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA 
 * ***************************************************************************/ 
#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    firefox.load(QString(":/img/white.png"));
    memberImage.load(QString(":/img/white.png"));
    count = 0;

    beginOrStop = false;

    resize(200, 100);
    setMinimumSize(200, 100);
}

void Widget::slotSet(int n, int r, int m)
{
    if (n < 100 || n > 200)
        n = 100;
    sizeOfPopulation = n;

    for (int i = 0; i < sizeOfPopulation; ++i) {
        Member m;
        calFitness(m);
        Population << m;
    }

    if (r >= n)
        r = 10;
    reserved = r;

    if (m <= 0 || m >= 100)
        m = 25;
    mutateRate = m;

    beginOrStop = true;
    count = 0;
    update();
}

void Widget::drawMember(Member member)
{
    QPainter p(&memberImage);
    QList<int> danlist = member.dnalist(100, 10);

    for (int i = 0; i < 1000; i += 10) {
        QPainterPath path;
        path.moveTo(danlist.at(i), danlist.at(i + 1));
        path.lineTo(danlist.at(i + 2), danlist.at(i + 3));
        path.lineTo(danlist.at(i + 4), danlist.at(i + 5));
        path.lineTo(danlist.at(i), danlist.at(i + 1));

        QBrush brush(QColor(danlist.at(i + 6), danlist.at(i + 7), danlist.at(i + 8), danlist.at(i + 9)));

        p.fillPath(path, brush);
    }
}

void Widget::calFitness(Member &member)
{
    memberImage.load(":/img/white.png");
    drawMember(member);

    int dif = 0;

    for(int i = 0; i < 100; ++i)
        for(int j = 0; j < 100; ++j) {
            QRgb rgbFirefox, rgbMemberImage;
            rgbFirefox = firefox.pixel(i, j);
            rgbMemberImage = memberImage.pixel(i, j);
            int red = qRed(rgbMemberImage) - qRed(rgbFirefox);
            int green = qGreen(rgbMemberImage) - qGreen(rgbFirefox);
            int blue = qBlue(rgbMemberImage) - qBlue(rgbFirefox);

            if(red > 0)
                dif += red;
            else
                dif -= red;

            if(green > 0)
                dif += green;
            else
                dif -= green;

            if(blue > 0)
                dif += blue;
            else
                dif -= blue;
        }

    member.setFitness(dif);
}

Member Widget::fittestMember()
{
    return Population.at(0);
}

void Widget::sortListMember(QList<Member> &P, int r)
{
    if (r > 50)
        r = 10;//the reserved parents are too much

    for (int i = P.size() - 1; i > P.size() - r - 1; --i) {
        for (int j = P.size() - 2; j > P.size() - i - 2; --j) {
            Member memberJ, memberJPlusOne;
            memberJ = P.at(j);
            memberJPlusOne = P.at(j + 1);
            if (memberJ.outputFitness() > memberJPlusOne.outputFitness()) {
                P.swap(j, j + 1);
            }
        }
    }
}

void Widget::crossover(QList <Member> &P)
{
    QList<Member> Temp;
    for (int i = 0; i < 10; i++) {
        Temp << P[i];
    }

    QList<Member>::iterator begin, end;
    begin = P.begin() + 10;
    end = P.end();
    P.erase(begin, end);

    for (int i = 0; i < 9; ++i) {
        for (int j = i + 1; j < 10; ++j) {
            int r = qrand() % 100;

            Member temp1 = Temp[i];
            Member temp2 = Temp[j];

            if (r <100 - mutateRate) {
                temp1.crossover(temp2);
                calFitness(temp1);
                calFitness(temp2);

                P << temp1;
                P << temp2;
            } else {
                temp1.mutate();
                temp2.mutate();
                calFitness(temp1);
                calFitness(temp2);

                P << temp1;
                P << temp2;
            }
        }
    }
}

Widget::~Widget()
{
    
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    if(!firefox.isNull())
        p.drawImage(0, 0, firefox);
    p.drawImage(100, 0, memberImage);

    if(beginOrStop)
        drawNew();
}

void Widget::drawNew()
{
    sortListMember(Population, reserved);
    crossover(Population);
    count++;

    Member m = fittestMember();
    QString s;
    s  = QString("This is the %1th genration, the fitness function of fittest one: %2").arg(count).arg(m.outputFitness());
    emit showMessage(s);

    memberImage.load(":/img/white.png");
    drawMember(m);

    update();
}

void Widget::end()
{
    beginOrStop = false;
    update();
}

void Widget::slotSetImg(QString s)
{
    firefox.load(s);
    update();
}
