/* 
 * File:   PeriodoTracklog.h
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

#ifndef _PERIODOTRACKLOG_H
#define	_PERIODOTRACKLOG_H

#include <QtCore/QVector>
#include <QtCore/QDateTime>

#include "GpsPosition.h"

class PeriodoAno;

class PeriodoTracklog {
public:
    void insereGpsPosition(GpsPosition *gpsPosition);
    GpsPosition *procuraGpsPosition(QDateTime dataHora, uint segundosTolerancia, uint &menorTolerancia, int &status);
    int getTotalSegmentos();
    void LimpaListaDeTrackLogs();
    
private:
    QVector<PeriodoAno*> listaPeridoAno;
};

#endif	/* _PERIODOTRACKLOG_H */
