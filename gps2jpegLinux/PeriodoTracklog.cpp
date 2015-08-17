/* 
 * File:   PeriodoTracklog.cpp
 * Author: Adonai Silveira Canez
 * 
 * Created on 9 de Agosto de 2009, 01:30
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

#include "PeriodoTracklog.h"

#include "PeriodoAno.h"
#include "GpsPosition.h"

void PeriodoTracklog::insereGpsPosition(GpsPosition *gpsPosition) {
    int i;
    // verificar se o ano recebido ja esta na lista
    if (listaPeridoAno.empty()) {
        PeriodoAno *periodoAno = new PeriodoAno(gpsPosition->getAno());
        periodoAno->insereGpsPosition(gpsPosition);
        listaPeridoAno.push_back(periodoAno);
    }
    else {
        // Caso ja tenha elementos na lista verifica se o ano ja foi inserido
        for (i = 0; i < listaPeridoAno.size(); i++) {
            if (listaPeridoAno.at(i)->getAno() == gpsPosition->getAno()) {
                break;
            }
        }
        if (i == listaPeridoAno.size()) {
            PeriodoAno *periodoAno = new PeriodoAno(gpsPosition->getAno());
            periodoAno->insereGpsPosition(gpsPosition);
            listaPeridoAno.push_back(periodoAno);
        }
        else {
            listaPeridoAno.at(i)->insereGpsPosition(gpsPosition);
        }
    }
}

/**
 *
 * @param dataHora
 * @param segundosTolerancia
 * @param menorTolerancia
 * @param status - 0 - caso tenha terminado ok, com o valor localizado
 *                 1 - caso tenha terminado ok, mas com o valor não localizado
 *                 10 - caso o valor esteja fora da faixa de periodo do tracklog
 * @return
 */
GpsPosition *PeriodoTracklog::procuraGpsPosition(QDateTime dataHora, int &segundosTolerancia, int &menorTolerancia, int &status){
//    int dia, mes, ano, hora, minuto, segundo;

    int ano;
//    dia = dataHora.date().day();
//    mes = dataHora.date().month();
    ano = dataHora.date().year();

//    hora = dataHora.time().hour();
//    minuto = dataHora.time().minute();
//    segundo = dataHora.time().second();

        for (int i = 0; i < listaPeridoAno.size(); i++) {
        if (listaPeridoAno.at(i)->getAno() == ano) {
           return listaPeridoAno.at(i)->procuraGpsPosition(dataHora, segundosTolerancia, menorTolerancia, status);
        }
    }
    status = 10;
    return NULL;
}

void PeriodoTracklog::LimpaListaDeTrackLogs(){
    for (int i=0; i < listaPeridoAno.size(); i++){
        delete listaPeridoAno.at(i);
    }
    listaPeridoAno.clear();
}
