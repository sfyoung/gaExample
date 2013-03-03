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
#include "mywidget.h"
#include <QFileDialog>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent)
{
    glayout = new QGridLayout(this);
    hlayout = new QHBoxLayout();
    hInputLayout = new QHBoxLayout();
    showLayout = new QHBoxLayout();
    blayout = new QVBoxLayout();
    bEditLayout = new QVBoxLayout();

    begin.setText("&Begin");
    begin.setEnabled(false);
    stop.setText("&Stop");
    stop.setEnabled(false);
    quit.setText("&Quit");
    open.setText("&Open");

    connect(&begin, SIGNAL(clicked()), this, SLOT(setBeginButton()));
    connect(this, SIGNAL(commit(int,int,int)), &widget, SLOT(slotSet(int,int,int)));

    connect(&stop, SIGNAL(clicked()), &widget, SLOT(end()));
    connect(&stop, SIGNAL(clicked()), this, SLOT(setStopButton()));
    connect(&quit, SIGNAL(clicked()), this, SLOT(close()));
    connect(&widget, SIGNAL(showMessage(QString)), this, SLOT(outputMessage(QString)));

    connect(&open, SIGNAL(clicked()), this, SLOT(slotOpenFile()));

    connect(this, SIGNAL(sendFileName(QString)), &widget, SLOT(slotSetImg(QString)));

    hlayout->addWidget(&begin);
    hlayout->addWidget(&stop);
    hlayout->addWidget(&quit);

    mutateRateLabel.setText("Mutate Rate(%):");
    reservedParentsLabel.setText("Total of Reserved Parents:");
    initialPopulationSizeLabel.setText("Initial Population Size:");

    blayout->addWidget(&initialPopulationSizeLabel);
    blayout->addWidget(&reservedParentsLabel);
    blayout->addWidget(&mutateRateLabel);

    initialPopulationSizeEdit.setAlignment(Qt::AlignRight);
    reservedParentsEdit.setAlignment(Qt::AlignRight);
    mutateRateEdit.setAlignment(Qt::AlignRight);

    initialPopulationSizeEdit.setText("100");
    reservedParentsEdit.setText("10");
    mutateRateEdit.setText("25");

    bEditLayout->addWidget(&initialPopulationSizeEdit);
    bEditLayout->addWidget(&reservedParentsEdit);
    bEditLayout->addWidget(&mutateRateEdit);

    hInputLayout->addLayout(blayout);
    hInputLayout->addLayout(bEditLayout);

    widget.resize(200, 100);
    showLayout->addWidget(&widget);
    showLayout->addWidget(&open);

    glayout->addLayout(showLayout, 0, 0);
    glayout->addLayout(hInputLayout, 1, 0);
    glayout->addLayout(hlayout, 2, 0);
    glayout->addWidget(&outputEdit, 3, 0);

    setLayout(glayout);
}

MyWidget::~MyWidget()
{
}

void MyWidget::outputMessage(QString s)
{
    outputEdit.setText(s);
}

void MyWidget::setBeginButton()
{
    begin.setEnabled(false);
    stop.setEnabled(true);
    int n = initialPopulationSizeEdit.text().toInt();
    if (n == 0)
        n = 100;
    int r = reservedParentsEdit.text().toInt();
    if (r == 0)
        r = 10;
    int m = mutateRateEdit.text().toInt();
    if (m == 0)
        m = 25;

    emit commit(n, r, m);
}

void MyWidget::setStopButton()
{
    stop.setEnabled(false);
    begin.setEnabled(true);
}

void MyWidget::slotOpenFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Choose an Image file", ".", "Image Files (*.png *.jpg *.bmp)");
    if (!fileName.isNull()){
        begin.setEnabled(true);
        emit sendFileName(fileName);
    }
}
