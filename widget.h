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
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPainter>
#include <QImage>
#include <QBrush>
#include <QPen>
#include <QPainterPath>
#include <qmath.h>
#include "member.h"

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();

    Member fittestMember();
    void drawMember(Member member);
    void calFitness(Member & member);
    void sortListMember(QList <Member> &P, int r);
    void crossover(QList <Member> &P);
    void drawNew();

protected:
    void paintEvent(QPaintEvent *);

signals:
    void showMessage(QString);

public slots:
    void end();
    void slotSet(int n, int r, int m);
    void slotSetImg(QString);

private:
    QList <Member> Population;
    QImage firefox;
    QImage memberImage;
    int count;
    bool beginOrStop;
    int sizeOfPopulation;
    int reserved;
    int mutateRate;
};

#endif // WIDGET_H
