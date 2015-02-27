/*
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

#include "GpsPosition.h"

#include <QtCore/QDateTime>

GpsPosition::GpsPosition(double latitude, double longitude, double altitude, QDateTime *dataHota) {
    this->latitude = latitude;
    this->longitude = longitude;
    this->altitude = altitude;
    this->dataHoraSegmento = dataHota;
}

GpsPosition::~GpsPosition(){
    delete dataHoraSegmento;
}

int GpsPosition::getAno() {
    return dataHoraSegmento->date().year();
}

int GpsPosition::getMes() {
    return dataHoraSegmento->date().month();
}

int GpsPosition::getDia() {
    return dataHoraSegmento->date().day();
}

int GpsPosition::getHora() {
    return dataHoraSegmento->time().hour();
}

int GpsPosition::getMinuto() {
    return dataHoraSegmento->time().minute();
}

int GpsPosition::getSegundo() {
    return dataHoraSegmento->time().second();
}

double GpsPosition::getLatitude() {
    return latitude;
}

double GpsPosition::getLongitude() {
    return longitude;
}

double GpsPosition::getAltitude() {
    return altitude;
}

QDateTime *GpsPosition::getDataHora(){
    return dataHoraSegmento;
}
