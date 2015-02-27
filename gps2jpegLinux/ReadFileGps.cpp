/* 
 * File:   ReadFileGpsTxt.cpp
 * Author: Adonai Silveira Canez
 * 
 * Created on 21 de Agosto de 2009, 14:05
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

#include "ReadFileGps.h"

#include "PeriodoTracklog.h"
#include "GpsPosition.h"

#include <QtCore/QFileInfo>
#include <QtCore/QDateTime>
#include <QtCore/QVariant>

ReadFileGps::ReadFileGps(PeriodoTracklog *gerenciaTrackLogs) {
    this->controlaPeriodoTracklog = gerenciaTrackLogs;
}

ReadFileGps::~ReadFileGps() {

}

bool ReadFileGps::readFileGps(QString fileName, QDateTime& peridoInicial, QDateTime& peridoFinal, int& segmentosLog) {
    DadosArquivoGps dadosArquivo;
    bool status = false;
    if (fileName.endsWith("txt", Qt::CaseInsensitive)) {
        status = readFileGpsTxt(fileName, peridoInicial, peridoFinal, segmentosLog);

    }
    if (fileName.endsWith("gpx", Qt::CaseInsensitive)) {
        status = readFileGpsGpx(fileName, peridoInicial, peridoFinal, segmentosLog);
    }
    if (!status){
        return false;
    }
    dadosArquivo.setCaminhoArquivo(fileName);
    dadosArquivo.setDataInicial(peridoInicial);
    dadosArquivo.setDataFinal(peridoFinal);
    dadosArquivo.setTotalDePontos(segmentosLog);
    listaArquivosLido.push_back(dadosArquivo);
    return true;
}

double ReadFileGps::fileTxtConverteCoordenadaGrausMinutosParaGraus(QString valorColuna) {
    int pos1, pos2;
    double coordenada;
    pos1 = valorColuna.indexOf(' ');
    pos2 = valorColuna.indexOf('\'');
    coordenada = valorColuna.mid(0, pos1).toDouble();

    if (coordenada < 0) {
        coordenada -= valorColuna.mid(pos1 + 1, pos2 - pos1 - 1).replace(QString("."), QString(",")).toDouble() / 60;
    } else {
        coordenada += valorColuna.mid(pos1 + 1, pos2 - pos1 - 1).replace(QString("."), QString(",")).toDouble() / 60;
    }
    return coordenada;
}

double ReadFileGps::fileTxtConverteCoordenadasGrausMinutosSegundosParaGraus(QString valorColuna) {
    int pos1, pos2, pos3;
    double coordenada;
    pos1 = valorColuna.indexOf(' ');
    pos2 = valorColuna.indexOf('\'');
    pos3 = valorColuna.indexOf('\'', pos2 + 1);
    coordenada = valorColuna.mid(0, pos1).toDouble();

    if (coordenada < 0) {
        coordenada -= valorColuna.mid(pos1 + 1, pos2 - pos1 - 1).toDouble() / 60; // minutos
        coordenada -= valorColuna.mid(pos2 + 1, pos3 - pos2 - 1).replace(QString("."), QString(",")).toDouble() / 3600;
    } else {
        coordenada += valorColuna.mid(pos1 + 1, pos2 - pos1 - 1).toDouble() / 60; // minutos
        coordenada += valorColuna.mid(pos2 + 1, pos3 - pos2 - 1).replace(QString("."), QString(",")).toDouble() / 3600;
    }
    return coordenada;
}

void ReadFileGps::fileTxtConverteData(QString valorColuna, int& dia, int& mes, int& ano) {
    int pos1, pos2, pos3;
    pos1 = valorColuna.indexOf('/');
    pos2 = valorColuna.indexOf('/', pos1 + 1);
    pos3 = valorColuna.size();

    mes = valorColuna.mid(0, pos1).toInt();
    dia = valorColuna.mid(pos1 + 1, pos2 - pos1 - 1).toInt();
    ano = valorColuna.mid(pos2 + 1, pos3 - pos2).toInt();
}

bool ReadFileGps::readFileGpsTxt(QString fileName, QDateTime &peridoInicial, QDateTime &peridoFinal, int &segmentosLog) {
    QString valorColuna;
    int pos1, pos2, posColuna;
    bool armazenarCoodenadas;
    int dia = 0, mes = 0, ano = 0, hora = 0, minuto = 0, segundo = 0;
    GpsPosition *gpsPosition;
    int totalSegmentosTrackLog, totalLinhasArquivo;
    QDateTime *dataInicial, *dataFinal;
    QDateTime *dataHora;
    dataFinal = NULL;
    dataInicial = NULL;
    bool arquivoD, arquivoDM, arquivoDMS;
    arquivoD = false;
    arquivoDM = false;
    arquivoDMS = false;

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    totalSegmentosTrackLog = 0;
    totalLinhasArquivo = 0;
    while (!file.atEnd()) {
        double latitude = 0, longitude = 0, altitude = 0;
        pos1 = 0;
        pos2 = 0;
        posColuna = 1;
        armazenarCoodenadas = false;
        totalLinhasArquivo++;
        QByteArray line = file.readLine();

        while (pos2 != -1) {
            pos2 = line.indexOf(',', pos1);
            valorColuna = QString(line.mid(pos1, pos2 - pos1));

            if (posColuna == 1 && valorColuna == "t") {
                armazenarCoodenadas = true;
                totalSegmentosTrackLog++;
            } else {
                if ((posColuna == 2 && valorColuna.operator ==("d")) || arquivoD) {
                    arquivoD = true;
                    if (posColuna == 3 && armazenarCoodenadas) {
                        latitude = valorColuna.toDouble();
                    } else if (posColuna == 4 && armazenarCoodenadas) {
                        longitude = valorColuna.toDouble();
                    } else if (posColuna == 5 && armazenarCoodenadas) {
                        fileTxtConverteData(valorColuna, dia, mes, ano);
                    } else if (posColuna == 6 && armazenarCoodenadas) {
                        hora = atoi(valorColuna.toStdString().substr(0, 2).c_str());
                        minuto = atoi(valorColuna.toStdString().substr(3, 2).c_str());
                        segundo = atoi(valorColuna.toStdString().substr(6, 2).c_str());
                    } else if (posColuna == 7 && armazenarCoodenadas) {
                        altitude = atof(valorColuna.toStdString().c_str());
                    }
                }
                if ((posColuna == 2 && valorColuna.operator ==("dm")) || arquivoDM) {
                    arquivoDM = true;
                    if (posColuna == 3 && armazenarCoodenadas) {
                        latitude = fileTxtConverteCoordenadaGrausMinutosParaGraus(valorColuna);
                    } else if (posColuna == 4 && armazenarCoodenadas) {
                        longitude = fileTxtConverteCoordenadaGrausMinutosParaGraus(valorColuna);
                    } else if (posColuna == 5 && armazenarCoodenadas) {
                        fileTxtConverteData(valorColuna, dia, mes, ano);
                    } else if (posColuna == 6 && armazenarCoodenadas) {
                        hora = atoi(valorColuna.toStdString().substr(0, 2).c_str());
                        minuto = atoi(valorColuna.toStdString().substr(3, 2).c_str());
                        segundo = atoi(valorColuna.toStdString().substr(6, 2).c_str());
                    } else if (posColuna == 7 && armazenarCoodenadas) {
                        altitude = atof(valorColuna.toStdString().c_str());
                    }
                }
                if ((posColuna == 2 && valorColuna.operator ==("dms")) || arquivoDMS) {
                    arquivoDMS = true;
                    if (posColuna == 3 && armazenarCoodenadas) {
                        latitude = fileTxtConverteCoordenadasGrausMinutosSegundosParaGraus(valorColuna);
                    } else if (posColuna == 4 && armazenarCoodenadas) {
                        longitude = fileTxtConverteCoordenadasGrausMinutosSegundosParaGraus(valorColuna);
                    } else if (posColuna == 5 && armazenarCoodenadas) {
                        fileTxtConverteData(valorColuna, dia, mes, ano);
                    } else if (posColuna == 6 && armazenarCoodenadas) {
                        hora = atoi(valorColuna.toStdString().substr(0, 2).c_str());
                        minuto = atoi(valorColuna.toStdString().substr(3, 2).c_str());
                        segundo = atoi(valorColuna.toStdString().substr(6, 2).c_str());
                    } else if (posColuna == 7 && armazenarCoodenadas) {
                        altitude = atof(valorColuna.toStdString().c_str());
                    }
                }
            }
            posColuna++;
            pos1 = pos2 + 1;
        }

        if (armazenarCoodenadas && ano != 0) {
            QDate dataSeg(ano, mes, dia);
            QTime horaSeg(hora, minuto, segundo);
            dataHora = new QDateTime(dataSeg, horaSeg);
            gpsPosition = new GpsPosition(latitude, longitude, altitude, dataHora);
            controlaPeriodoTracklog->insereGpsPosition(gpsPosition);
            if (dataFinal == NULL && dataInicial == NULL && ano != 0) {
                dataFinal = dataHora;
                dataInicial = dataHora;
            } else {
                if (dataHora->operator<(*dataInicial)) {
                    dataInicial = dataHora;
                }
                if (dataHora->operator>(*dataFinal)) {
                    dataFinal = dataHora;
                }
            }
        }
    }
    if (dataInicial != NULL && dataFinal != NULL && totalSegmentosTrackLog != 0) {
        peridoInicial.setDate(dataInicial->date());
        peridoInicial.setTime(dataInicial->time());
        peridoFinal.setDate(dataFinal->date());
        peridoFinal.setTime(dataFinal->time());
        segmentosLog = totalSegmentosTrackLog;
        return true;
    } else {
        return false;
    }
}

bool ReadFileGps::readFileGpsGpx(QString fileName, QDateTime &peridoInicial, QDateTime &peridoFinal, int &segmentosLog) {
    int totalSegmentosTrackLog, totalLinhasArquivo;
    bool posicaoOk = false, altitudeOk = false, timeOk = false;
    GpsPosition *gpsPosition;
    double latitude = 0, longitude = 0, altitude = 0;
    int dia = 0, mes = 0, ano = 0, hora = 0, minuto = 0, segundo = 0;
    bool ativaLeitura;

    QDateTime *dataInicial, *dataFinal;
    QDateTime *dataHora;
    dataFinal = NULL;
    dataInicial = NULL;

    int pos1, pos2, posInicio, posFim;
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    totalSegmentosTrackLog = 0;
    totalLinhasArquivo = 0;
    ativaLeitura = false;

    while (!file.atEnd()) {
        posInicio = posFim = -1;
        totalLinhasArquivo++;
        QByteArray line = file.readLine();
        pos1 = pos2 = 0;

        while (pos2 != -1) {
            if (!ativaLeitura) {
                posInicio = line.indexOf(QString("<trk>"), pos1);
                if (posInicio != -1) {
                    ativaLeitura = true;
                    pos1 = posInicio;
                }
            } else {
                posFim = line.indexOf(QString("</trk>"), pos1);
                if ((posFim != -1) && (posFim < pos2)) {
                    ativaLeitura = false;
                    pos1 = posFim;
                }
            }

            if (ativaLeitura) {
                pos2 = line.indexOf(QString("<trkpt"), pos1);
                if (pos2 != -1) {
                    posicaoOk = true;
                    int pos3, pos4, pos5, pos6;
                    pos3 = line.indexOf(QString("lat=\""), pos2 + 6);
                    pos4 = line.indexOf('"', pos3 + 5);
                    latitude = QString(line.mid(pos3 + 5, pos4 - pos3 - 5)).replace('.', ',').toDouble();
                    pos5 = line.indexOf(QString("lon=\""), pos4);
                    pos6 = line.indexOf('"', pos5 + 5);
                    longitude = QString(line.mid(pos5 + 5, pos6 - pos5 - 5)).replace('.', ',').toDouble();
                    pos1 = pos6;
                }
                pos2 = line.indexOf(QString("<ele>"), pos1);
                if (pos2 != -1) {
                    int pos7;
                    altitudeOk = true;
                    pos7 = line.indexOf(QString("</ele>"), pos2 + 5);
                    altitude = QString(line.mid(pos2 + 5, pos7 - pos2 - 5)).replace('.', ',').toDouble();
                    pos1 = pos7;
                }
                pos2 = line.indexOf(QString("<time>"), pos1);
                if (pos2 != -1) {
                    int pos8;
                    QString dataHoraS;
                    timeOk = true;
                    pos8 = line.indexOf(QString("</time>"), pos2 + 6);
                    dataHoraS = QString(line.mid(pos2 + 6, pos8 - pos2 - 6));
                    ano = dataHoraS.mid(0, 4).toInt();
                    mes = dataHoraS.mid(5, 2).toInt();
                    dia = dataHoraS.mid(8, 2).toInt();
                    hora = dataHoraS.mid(11, 2).toInt();
                    minuto = dataHoraS.mid(14, 2).toInt();
                    segundo = dataHoraS.mid(17, 2).toInt();
                    pos1 = pos8;
                }
            } else {
                pos2 = -1;
            }
            if (posicaoOk && altitudeOk && timeOk) {
                QDate dataSeg(ano, mes, dia);
                QTime horaSeg(hora, minuto, segundo);
                dataHora = new QDateTime(dataSeg, horaSeg);
                gpsPosition = new GpsPosition(latitude, longitude, altitude, dataHora);
                controlaPeriodoTracklog->insereGpsPosition(gpsPosition);
                if (dataFinal == NULL && dataInicial == NULL && ano != 0) {
                    dataFinal = dataHora;
                    dataInicial = dataHora;
                } else {
                    if (dataHora->operator<(*dataInicial)) {
                        dataInicial = dataHora;
                    }
                    if (dataHora->operator>(*dataFinal)) {
                        dataFinal = dataHora;
                    }
                }
                totalSegmentosTrackLog++;
                posicaoOk = altitudeOk = timeOk = false;
            }
        }
    }

    if (dataInicial != NULL && dataFinal != NULL && totalSegmentosTrackLog != 0) {
        peridoInicial.setDate(dataInicial->date());
        peridoInicial.setTime(dataInicial->time());
        peridoFinal.setDate(dataFinal->date());
        peridoFinal.setTime(dataFinal->time());
        segmentosLog = totalSegmentosTrackLog;
        return true;
    } else {
        return false;
    }
}

void ReadFileGps::limpaListaArquivosLidos() {
    listaArquivosLido.clear();
}

QVector<DadosArquivoGps> ReadFileGps::getListaArquivosLidos() {
    return listaArquivosLido;
}