/* 
 * File:   PeriodoDias.cpp
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

#include "PeriodoDia.h"

#include "GpsPosition.h"

#include <cmath>

PeriodoDia::PeriodoDia(int dia) {
    this->dia = dia;
}

PeriodoDia::~PeriodoDia() {
    for (int i = 0; i < listaPosicaoGps.size(); i++) {
        delete listaPosicaoGps.at(i);
    }
}

void PeriodoDia::insereGpsPosition(GpsPosition *gpsPosition) {
    listaPosicaoGps.push_back(gpsPosition);
}

GpsPosition *PeriodoDia::procuraGpsPosition(QDateTime dataHora, uint segundosTolerancia, uint &menorTolerancia, int &status) {
    GpsPosition *resultado;
    qulonglong resultadoSegundos,diferencaSegundos;

    diferencaSegundos = (int) fabs(dataHora.secsTo(*listaPosicaoGps.at(0)->getDataHora()));
    resultadoSegundos = diferencaSegundos;
    resultado = listaPosicaoGps.at(0);

    for (int i = 1; i < listaPosicaoGps.size(); i++) {
        diferencaSegundos = (int) fabs(dataHora.secsTo(*listaPosicaoGps.at(i)->getDataHora()));
        if (diferencaSegundos < resultadoSegundos) {
            resultadoSegundos = diferencaSegundos;
            resultado = listaPosicaoGps.at(i);
        }
    }
    menorTolerancia = resultadoSegundos;

    if (resultadoSegundos <= segundosTolerancia) {
        status = 0;
        return resultado;
    }
    status =1;
    return NULL;
}

int PeriodoDia::getDia() {
    return dia;
}
