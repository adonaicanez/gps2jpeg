/* 
 * File:   PeriodoMeses.cpp
 * Author: Adonai Silveira Canez
 * 
 * Created on 8 de Agosto de 2009, 23:21
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

#include "PeriodoMes.h"

#include "GpsPosition.h"
#include "PeriodoDia.h"

PeriodoMes::PeriodoMes(int mes) {
    this->mes = mes;
}

PeriodoMes::~PeriodoMes(){
    for(int i=0; i<listaPeriodoDia.size();i++){
        delete listaPeriodoDia.at(i);
    }
}

void PeriodoMes::insereGpsPosition(GpsPosition *gpsPosition) {
    int i;
    PeriodoDia *periodoDia;
    // verificar se o dia recebido ja esta na lista
    if (listaPeriodoDia.empty()) {
        // Caso a lista de anos esteja vazia vai criar o elemento e enserir ele
        periodoDia = new PeriodoDia(gpsPosition->getDia());
        periodoDia->insereGpsPosition(gpsPosition);
        listaPeriodoDia.push_back(periodoDia);
    }
    else {
        // Caso ja tenha elementos na lista verifica se o mes ja foi inserido
        for (i = 0; i < listaPeriodoDia.size(); i++) {
            if (listaPeriodoDia.at(i)->getDia() == gpsPosition->getDia()) {
                break;
            }
        }
        if (i == listaPeriodoDia.size()) {
            periodoDia = new PeriodoDia(gpsPosition->getDia());
            periodoDia->insereGpsPosition(gpsPosition);
            listaPeriodoDia.push_back(periodoDia);
        }
        else {
            listaPeriodoDia.at(i)->insereGpsPosition(gpsPosition);
        }
    }
}

GpsPosition *PeriodoMes::procuraGpsPosition(QDateTime dataHora, int segundosTolerancia, int &menorTolerancia, int &status) {
    int i;
    int dia; //, hora, minuto, segundo;

    dia = dataHora.date().day();
//    hora = dataHora.time().hour();
//    minuto = dataHora.time().minute();
//    segundo = dataHora.time().second();

    for(i=0; i<listaPeriodoDia.size();i++){
        if(listaPeriodoDia.at(i)->getDia() == dia){
            return listaPeriodoDia.at(i)->procuraGpsPosition(dataHora, segundosTolerancia, menorTolerancia, status);
        }
    }
    return NULL;
}

int PeriodoMes::getMes() {
    return mes;
}
