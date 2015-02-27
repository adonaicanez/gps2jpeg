/* 
 * File:   PeriodoAnos.cpp
 * Author: Adonai Silveira Canez
 * 
 * Created on 8 de Agosto de 2009, 23:07
 *
 * Copyright (C) Adonai Silveira Canez 2009, 2010 <adonaicanez@gmail.com>
 *
 * This file is part of gps2jpeg.
 *
 * gps2jpeg is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License.
 *
 * gps2jpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with gps2jpeg.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "PeriodoAno.h"
#include "GpsPosition.h"
#include "PeriodoMes.h"

PeriodoAno::PeriodoAno(int ano) {
    this->ano = ano;
}

PeriodoAno::~PeriodoAno(){
    for(int i=0; i<listaPeriodoMes.size();i++){
        delete listaPeriodoMes.at(i);
    }
}

void PeriodoAno::insereGpsPosition(GpsPosition *gpsPosition) {
    int i;
    PeriodoMes *periodoMes;
    if (listaPeriodoMes.empty()) {
        periodoMes = new PeriodoMes(gpsPosition->getMes());
        periodoMes->insereGpsPosition(gpsPosition);
        listaPeriodoMes.push_back(periodoMes);
    }
    else {
        for (i = 0; i < listaPeriodoMes.size(); i++) {
            if (listaPeriodoMes.at(i)->getMes() == gpsPosition->getMes()) {
                break;
            }
        }
        if (i == listaPeriodoMes.size()) {
            periodoMes = new PeriodoMes(gpsPosition->getMes());
            periodoMes->insereGpsPosition(gpsPosition);
            listaPeriodoMes.push_back(periodoMes);
        }
        else {
            listaPeriodoMes.at(i)->insereGpsPosition(gpsPosition);
        }
    }
}

GpsPosition *PeriodoAno::procuraGpsPosition(QDateTime dataHora, uint segundosTolerancia, uint &menorTolerancia, int &status) {
    int i, mes;
 //   int mes, dia, hora, minuto, segundo;

    mes = dataHora.date().month();
//    dia = dataHora.date().day();
//    hora = dataHora.time().hour();
//    minuto = dataHora.time().minute();
//    segundo = dataHora.time().second();

    for (i = 0; i < listaPeriodoMes.size(); i++) {
        if (listaPeriodoMes.at(i)->getMes() == mes) {
            return listaPeriodoMes.at(i)->procuraGpsPosition(dataHora, segundosTolerancia, menorTolerancia, status);
        }
    }
    return NULL;
}

int PeriodoAno::getAno() {
    return ano;
}
