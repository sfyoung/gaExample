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
#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include "widget.h"

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);
    ~MyWidget();
    
signals:
    void beginPaint();
    void endPaint();
    void commit(int, int, int);
    void sendFileName(QString);
    
public slots:
    void outputMessage(QString);
    void setBeginButton();
    void setStopButton();
    void slotOpenFile();

private:
    Widget widget;

    QLabel mutateRateLabel;
    QLabel reservedParentsLabel;
    QLabel initialPopulationSizeLabel;

    QLineEdit mutateRateEdit;
    QLineEdit reservedParentsEdit;
    QLineEdit initialPopulationSizeEdit;

    QTextEdit outputEdit;

    QPushButton begin;
    QPushButton stop;
    QPushButton quit;
    QPushButton open;

    QHBoxLayout *hlayout;
    QVBoxLayout *blayout;
    QVBoxLayout *bEditLayout;
    QHBoxLayout *hInputLayout;
    QHBoxLayout *showLayout;
    QGridLayout *glayout;
};

#endif // MYWIDGET_H
