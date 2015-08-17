/* 
 * File:   PosicionaFotos.cpp
 * Author: adonai
 * 
 * Created on 23 de Agosto de 2009, 01:30
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
 
#include "ManipulaExifFotos.h"
#include "PeriodoTracklog.h"

//#include <QtGui/QTableWidgetItem>
#include <QtCore/QVariant>

#include <cassert>
#include <math.h>
#include <exiv2/image.hpp>
#include <exiv2/exif.hpp>

ManipulaExifFotos::ManipulaExifFotos(PeriodoTracklog *periodoTrackLog) {
    this->periodoTrackLog = periodoTrackLog;
}

ManipulaExifFotos::~ManipulaExifFotos() {

}

bool ManipulaExifFotos::insereCoordenadasFoto(QString nomeFoto, int segundosTolerancia, QDateTime dataHoraCorrigida,
        QString &itemLatitude, QString &itemLongitude, QString &itemAltitude, QString &itemStatus) {

    QString tagExiv;

#ifdef Q_WS_WIN
    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(nomeFoto.toStdString().c_str());
#endif
//#ifdef Q_WS_X11
    QString nomeUtf(nomeFoto.toUtf8());
    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(nomeUtf.toStdString().c_str());
//#endif

    assert(image.get() != 0);
    image->readMetadata();

    Exiv2::ExifData &exifData = image->exifData();
    if (exifData.empty()) {
        return false;
    } else {
        Exiv2::ExifData::const_iterator end = exifData.end();
        for (Exiv2::ExifData::const_iterator i = exifData.begin(); i != end; ++i) {
            tagExiv = QString(i->key().c_str());
            if (tagExiv.operator ==("Exif.Photo.DateTimeOriginal")) {
                GpsPosition *posicaoLocalizada;

                int menorTolerancia, status;
                posicaoLocalizada = periodoTrackLog->procuraGpsPosition(dataHoraCorrigida, segundosTolerancia, menorTolerancia, status);

                if (posicaoLocalizada != NULL) {
                    QString latitudeExif, latitudeExifRef, longitudeExif, longitudeExifRef;
                    converteLatitudeGrausParaFormatoExif(posicaoLocalizada->getLatitude(), latitudeExif, latitudeExifRef);
                    converteLongitudeGrausParaFormatoExif(posicaoLocalizada->getLongitude(), longitudeExif, longitudeExifRef);

                    exifData["Exif.GPSInfo.GPSLatitude"] = latitudeExif.toStdString();
                    exifData["Exif.GPSInfo.GPSLatitudeRef"] = latitudeExifRef.toStdString();
                    exifData["Exif.GPSInfo.GPSLongitude"] = longitudeExif.toStdString();
                    exifData["Exif.GPSInfo.GPSLongitudeRef"] = longitudeExifRef.toStdString();

                    if (posicaoLocalizada->getAltitude() < 0) {
                        exifData["Exif.GPSInfo.GPSAltitude"] = Exiv2::floatToRationalCast(posicaoLocalizada->getAltitude());
                        exifData["Exif.GPSInfo.GPSAltitudeRef"] = "1";
                    } else {
                        exifData["Exif.GPSInfo.GPSAltitude"] = Exiv2::floatToRationalCast(posicaoLocalizada->getAltitude());
                        exifData["Exif.GPSInfo.GPSAltitudeRef"] = "0";
                    }
                    image->writeMetadata();

                    itemLatitude = QVariant(posicaoLocalizada->getLatitude()).toString();
                    itemLongitude = QVariant(posicaoLocalizada->getLongitude()).toString();
                    itemAltitude = QVariant(posicaoLocalizada->getAltitude()).toString();
                    itemStatus = QString::fromUtf8("OK - ") + QString::fromUtf8("proximidade do ponto: ") +
                            QVariant(menorTolerancia).toString() + QString::fromUtf8(" seg.");
                    return true;
                } else {
                    itemStatus = QString::fromUtf8("Ponto mais próximo: ") + QVariant(menorTolerancia).toString() + QString::fromUtf8(" seg.");
                    return false;
                }
            }
        }
    }
    itemStatus = QString::fromUtf8("Sem dados Exif");
    return false;

}

void ManipulaExifFotos::converteLatitudeGrausParaFormatoExif(double graus, QString &coordenadas, QString &referencia) {
    double parteFracionaria, temp;
    double grausConvertidos, minutosConvertidos, segundosConvertidos;

    // Calculando a Latitude
    parteFracionaria = modf(graus, &grausConvertidos);
    if (parteFracionaria < 0) {
        parteFracionaria = -parteFracionaria;
    }

    temp = 60 * parteFracionaria;
    parteFracionaria = modf(temp, &minutosConvertidos);

    temp = 60 * parteFracionaria;
    parteFracionaria = modf(temp, &segundosConvertidos);

    double parteInteira;
    int contZeros = 1;
    while (parteFracionaria != 0 && contZeros < 10000) {
        segundosConvertidos = segundosConvertidos * 10;
        parteFracionaria = modf(parteFracionaria * 10, &parteInteira);
        segundosConvertidos += parteInteira;
        contZeros *= 10;
    }

    if (grausConvertidos < 0) {
        grausConvertidos = -grausConvertidos;
        referencia = "S";
    } else {
        referencia = "N";
    }

    coordenadas = QString::number(grausConvertidos);
    coordenadas.append("/1 ");
    coordenadas.append(QString::number(minutosConvertidos));
    coordenadas.append("/1 ");
    coordenadas.append(QString::number(segundosConvertidos));
    coordenadas.append("/");
    coordenadas.append(QString::number(contZeros));
}

void ManipulaExifFotos::converteLongitudeGrausParaFormatoExif(double graus, QString &coordenadas, QString &referencia) {
    double parteFracionaria, temp;
    double grausConvertidos, minutosConvertidos, segundosConvertidos;
    // Calculando a Longitude
    parteFracionaria = modf(graus, &grausConvertidos);
    if (parteFracionaria < 0) {
        parteFracionaria = -parteFracionaria;
    }
    temp = 60 * parteFracionaria;
    parteFracionaria = modf(temp, &minutosConvertidos);
    temp = 60 * parteFracionaria;
    parteFracionaria = modf(temp, &segundosConvertidos);
    double parteInteira;
    int contZeros = 1;
    while (parteFracionaria != 0 && contZeros < 10000) {
        segundosConvertidos = segundosConvertidos * 10;
        parteFracionaria = modf(parteFracionaria * 10, &parteInteira);
        segundosConvertidos += parteInteira;
        contZeros *= 10;
    }
    if (grausConvertidos < 0) {
        grausConvertidos = -grausConvertidos;
        referencia = "W";
    } else {
        referencia = "E";
    }
    coordenadas = QString::number(grausConvertidos);
    coordenadas.append("/1 ");
    coordenadas.append(QString::number(minutosConvertidos));
    coordenadas.append("/1 ");
    coordenadas.append(QString::number(segundosConvertidos));
    coordenadas.append("/");
    coordenadas.append(QString::number(contZeros));
}

/*
void ManipulaExifFotos::lerDadosExifFoto(QString pathArquivoJpeg, QDateTime& itemDataHora, QString& itemLatitude,
        QString& itemLongitude, QString& itemAltitude, QString& itemMsg, bool &status) {

    QString tagExiv;
    int dia, mes, ano;
    int hora, minuto, segundo;
    bool latitudeNegativo, longitudeNegativo;
    bool possuiLatitudeExif, possuiLongitudeExif;

    possuiLatitudeExif = false;
    possuiLongitudeExif = false;
    latitudeNegativo = false;
    longitudeNegativo = false;

#ifdef Q_WS_WIN
    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(pathArquivoJpeg.toStdString().c_str());
#endif
#ifdef Q_WS_X11
    QString nomeUtf(pathArquivoJpeg.toUtf8());
    Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open(nomeUtf.toStdString().c_str());
#endif

    assert(image.get() != 0);
    image->readMetadata();
    Exiv2::ExifData &exifData = image->exifData();
    if (exifData.empty()) {
        itemMsg = QString("Sem dados Exif");
    } else {
        Exiv2::ExifData::const_iterator end = exifData.end();
        double latitude = 0, longitude = 0;
        bool temDataHora = false;
        for (Exiv2::ExifData::const_iterator i = exifData.begin(); i != end; ++i) {
            tagExiv = QString::fromUtf8(i->key().c_str());
            if (tagExiv.operator ==("Exif.Photo.DateTimeOriginal")) {
                temDataHora = true;
                ano = atoi(i->value().toString().substr(0, 4).c_str());
                mes = atoi(i->value().toString().substr(5, 2).c_str());
                dia = atoi(i->value().toString().substr(8, 2).c_str());

                QDate *data = new QDate();
                data->setYMD(ano, mes, dia);

                hora = atoi(i->value().toString().substr(11, 2).c_str());
                minuto = atoi(i->value().toString().substr(14, 2).c_str());
                segundo = atoi(i->value().toString().substr(17, 2).c_str());

                QTime *horaT = new QTime();
                horaT->setHMS(hora, minuto, segundo, 0);

                QDateTime *dataHoraFoto = new QDateTime();
                dataHoraFoto->setDate(*data);
                dataHoraFoto->setTime(*horaT);
                itemDataHora = *dataHoraFoto;
            }
            if (tagExiv.operator ==("Exif.GPSInfo.GPSLatitude")) {
                possuiLatitudeExif = true;
                int pos1, pos2, pos3, pos4, pos5, pos6;
                double val1, val2, val3, val4, val5, val6;
                QString posicaoLatitude = QString(i->value().toString().c_str());

                pos1 = posicaoLatitude.indexOf('/');
                pos2 = posicaoLatitude.indexOf(' ', pos1);
                pos3 = posicaoLatitude.indexOf('/', pos2);
                pos4 = posicaoLatitude.indexOf(' ', pos3);
                pos5 = posicaoLatitude.indexOf('/', pos4);
                pos6 = posicaoLatitude.size();

                val1 = posicaoLatitude.mid(0, pos1).toDouble();
                val2 = posicaoLatitude.mid(pos1 + 1, pos2 - pos1).toDouble();
                val3 = posicaoLatitude.mid(pos2, pos3 - pos2).toDouble();
                val4 = posicaoLatitude.mid(pos3 + 1, pos4 - pos3).toDouble();
                val5 = posicaoLatitude.mid(pos4, pos5 - pos4).toDouble();
                val6 = posicaoLatitude.mid(pos5 + 1, pos6 - pos5).toDouble();

                latitude = (val1 / val2);
                latitude += (val3 / val4) / 60;
                latitude += (val5 / val6) / 3600;
            }
            if (tagExiv.operator ==("Exif.GPSInfo.GPSLatitudeRef")) {
                if (QString::fromStdString(i->value().toString()).operator ==("S")) {
                    latitudeNegativo = true;
                }
            }
            if (tagExiv.operator ==("Exif.GPSInfo.GPSLongitude")) {
                possuiLongitudeExif = true;
                int pos1, pos2, pos3, pos4, pos5, pos6;
                double val1, val2, val3, val4, val5, val6;
                QString posicaoLongitude = QString(i->value().toString().c_str());

                pos1 = posicaoLongitude.indexOf('/');
                pos2 = posicaoLongitude.indexOf(' ', pos1);
                pos3 = posicaoLongitude.indexOf('/', pos2);
                pos4 = posicaoLongitude.indexOf(' ', pos3);
                pos5 = posicaoLongitude.indexOf('/', pos4);
                pos6 = posicaoLongitude.size();

                val1 = posicaoLongitude.mid(0, pos1).toDouble();
                val2 = posicaoLongitude.mid(pos1 + 1, pos2 - pos1).toDouble();
                val3 = posicaoLongitude.mid(pos2, pos3 - pos2).toDouble();
                val4 = posicaoLongitude.mid(pos3 + 1, pos4 - pos3).toDouble();
                val5 = posicaoLongitude.mid(pos4, pos5 - pos4).toDouble();
                val6 = posicaoLongitude.mid(pos5 + 1, pos6 - pos5).toDouble();

                longitude = (val1 / val2);
                longitude += (val3 / val4) / 60;
                longitude += (val5 / val6) / 3600;
            }
            if (tagExiv.operator ==("Exif.GPSInfo.GPSLongitudeRef")) {
                if (QString::fromStdString(i->value().toString()).operator ==("W")) {
                    longitudeNegativo = true;
                }
            }
            if (tagExiv.operator ==("Exif.GPSInfo.GPSAltitude")) {
                int pos1, pos2;
                double val1, val2, altitude;
                QString posicaoAltitude = QString(i->value().toString().c_str());

                pos1 = posicaoAltitude.indexOf('/');
                pos2 = posicaoAltitude.size();

                val1 = posicaoAltitude.mid(0, pos1).toDouble();
                val2 = posicaoAltitude.mid(pos1 + 1, pos2 - pos1).toDouble();

                altitude = (val1 / val2);
                if (val1 != 0 && val2 != 0) {
                    itemAltitude = QVariant(altitude).toString();
                }
            }
        }
        if (possuiLatitudeExif) {
            if (latitudeNegativo) {
                itemLatitude = QVariant(-latitude).toString();
            } else {
                itemLongitude = QVariant(latitude).toString();
            }
        }
        if (possuiLongitudeExif) {
            if (longitudeNegativo) {
                itemLongitude = QVariant(-longitude).toString();
            } else {
                itemLongitude = QVariant(longitude).toString();
            }
        }

        // testar se nao tem data e colocar que não tem dados de data d foto
        if (!temDataHora) {
            itemMsg = QString("Sem dados Exif");
            status = false;
        } else {
            itemMsg = QString("OK");
            status = true;
        }
    }
}
 */