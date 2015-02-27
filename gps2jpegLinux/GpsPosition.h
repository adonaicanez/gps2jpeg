/* 
 * File:   GpsPosition.h
 * Author: Adonai Silveira Canez
 *
 * Created on 8 de Agosto de 2009, 20:57
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

#ifndef _GPSPOSITION_H
#define	_GPSPOSITION_H

class QDateTime;

class GpsPosition {
public:
    GpsPosition(double latitude, double longitude, double altitude, QDateTime *dataHota);
    ~GpsPosition();
    int getAno();
    int getMes();
    int getDia();
    int getHora();
    int getMinuto();
    int getSegundo();
    double getLatitude();
    double getLongitude();
    double getAltitude();

    QDateTime *getDataHora();
    
private:
    double latitude;
    double longitude;
    double altitude;
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
    int segundo;
    QDateTime *dataHoraSegmento;
};

#endif	/* _GPSPOSITION_H */

