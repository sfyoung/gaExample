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
#include "member.h"

Member::Member()
{
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (j < 6)
                dna[i][j] = qrand() % 100;
            else if (j < 9)
                dna[i][j] = qrand() % 255;
            else
                dna[i][j] = 128;
//                dna[i][j] = 64;
        }
    }

    fitness = 0;
}

void Member::crossover(Member &m)
{
    int r = qrand() % 10;
    while (r == 0) {
        r = qrand() % 10;
    }

    QList<int> dnalistOfThis = dnalist(100, 10);
    QList<int> dnalistOfM = m.dnalist(100, 10);

    QList<int> dnalistTemp = dnalistOfThis.mid(r * 10);
    QList<int> dnalistTemp2 = dnalistOfM.mid(r * 10);

    QList<int>::iterator begin, end;
    QList<int>::iterator begin2, end2;

    begin = dnalistOfThis.begin() + r * 10;
    end = dnalistOfThis.end();
    begin2 = dnalistOfM.begin() + r * 10;
    end2 = dnalistOfM.end();

    dnalistOfThis.erase(begin, end);
    dnalistOfM.erase(begin2, end2);

    dnalistOfThis << dnalistTemp2;
    dnalistOfM << dnalistTemp;
    setDNA(dnalistOfThis);
    m.setDNA(dnalistOfM);
}

void Member::setDNA(QList<int> list)
{
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 10; ++j) {
            dna[i][j] = list[i * 10 + j];
        }
    }
}

void Member::setFitness(int f)
{
    fitness = f;
}

int Member::outputFitness()
{
    return fitness;
}

QList<int> Member::dnalist(int countOfDNA, int sizeOfDNA)
{
    QList <int> result;
    for (int i = 0; i < countOfDNA; ++i)
        for (int j = 0; j < sizeOfDNA; ++j)
            result << dna[i][j];
    return result;
}

void Member::mutate()
{
    int r = qrand() % 100;

    for (int j = 0; j < 10; ++j) {
        if (j < 6)
            dna[r][j] = qrand() % 100;
        else if (j < 9)
            dna[r][j] = qrand() % 255;
        else
            dna[r][j] = 64;
    }
}
