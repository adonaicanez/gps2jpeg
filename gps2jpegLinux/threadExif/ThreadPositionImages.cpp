/*
 * File:   ThreadLoadExifDatas.h
 * Author: Adonai Silveira Canez
 *
 * Created on 2 de Março de 2010, 16:56
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

#include "ThreadPositionImages.h"

#include "GpsPosition.h"
#include "PeriodoTracklog.h"
#include "DadosArquivoGps.h"

#include <QtCore/QDir>
#include <QtCore/QFileInfo>
#include <QtCore/QString>
#include <QtGui/QApplication>
#include <QtGui/QTableWidget>
#include <QtGui/QProgressBar>
#include <QtGui/QLineEdit>
#include <QtGui/QCheckBox>

#include <cassert>
#include <math.h>
#include <exiv2/image.hpp>
#include <exiv2/exif.hpp>

ThreadPositionImages::ThreadPositionImages(QObject *parent) : QThread(parent) {
}

void ThreadPositionImages::run() {
    QTableWidgetItem *item;
    QDateTime dataHoraCorrigida, dataHoraCorrigidaGMT;
    QString itemLatitude, itemLongitude, itemAltitude, itemStatus;
    GpsPosition *posicaoLocalizada;
    uint menorTolerancia;
    int status;
    QVector<QString> listErrorRemoveFile;
    QVector<int> listErrorRemoveFilePosition;

    connect(this, SIGNAL(progressBarValue(int)), progressBar, SLOT(setValue(int)));
    connect(this, SIGNAL(progressBarSetVisible(bool)), progressBar, SLOT(setVisible(bool)));
    emit progressBarSetVisible(true);
    progressBar->setRange(0, tableWidgetJpeg->rowCount());

    for (int i = 0; i < tableWidgetJpeg->rowCount(); i++) {
        bool dateOk = false;
        emit progressBarValue(i);
        //      usleep(50000);
        if (tableWidgetJpeg->item(i, 2) != 0) {
            dataHoraCorrigida = QDateTime::fromString(tableWidgetJpeg->item(i, 2)->text(), "dd/MM/yyyy hh:mm:ss");
            dateOk = true;
        }
        if (dateOk) {
            try {
                Exiv2::Image::AutoPtr image;
                dataHoraCorrigidaGMT = convertLocalTimeToGmt(dataHoraCorrigida);
                posicaoLocalizada = periodoTrackLog->procuraGpsPosition(dataHoraCorrigidaGMT, segundosTolerancia, menorTolerancia, status);
                if (posicaoLocalizada != NULL) {
                    image = Exiv2::ImageFactory::open(tableWidgetJpeg->item(i, 7)->text().toStdString().c_str());
                    assert(image.get() != 0);
                    image->readMetadata();
                    Exiv2::ExifData &exifData = image->exifData();

                    QString latitudeExif, latitudeExifRef, longitudeExif, longitudeExifRef, timeStampExif;
                    convertLatitudeGrausToExifFormat(posicaoLocalizada->getLatitude(), latitudeExif, latitudeExifRef);
                    convertLongitudeGrausToExifFormat(posicaoLocalizada->getLongitude(), longitudeExif, longitudeExifRef);

                    exifData["Exif.GPSInfo.GPSLatitude"] = latitudeExif.toStdString();
                    exifData["Exif.GPSInfo.GPSLatitudeRef"] = latitudeExifRef.toStdString();
                    exifData["Exif.GPSInfo.GPSLongitude"] = longitudeExif.toStdString();
                    exifData["Exif.GPSInfo.GPSLongitudeRef"] = longitudeExifRef.toStdString();

                    QDateTime dateTimeGps = convertGmtTimeToLocal(*posicaoLocalizada->getDataHora());
                    QString timeRational;
                    timeRational = QString::number(dateTimeGps.time().hour());
                    timeRational.append("/1 ");
                    timeRational.append(QString::number(dateTimeGps.time().minute()));
                    timeRational.append("/1 ");
                    timeRational.append(QString::number(dateTimeGps.time().second()));
                    timeRational.append("/1");
                    exifData["Exif.GPSInfo.GPSTimeStamp"] = timeRational.toStdString();

                    QString dateRational;
                    dateRational = QString::number(dateTimeGps.date().year());
                    dateRational.append(":");
                    if (dateTimeGps.date().month() < 10) {
                        dateRational.append("0");
                        dateRational.append(QString::number(dateTimeGps.date().month()));
                    } else {
                        dateRational.append(QString::number(dateTimeGps.date().month()));
                    }
                    dateRational.append(":");
                    if (dateTimeGps.date().day() < 10) {
                        dateRational.append("0");
                        dateRational.append(QString::number(dateTimeGps.date().day()));
                    } else {
                        dateRational.append(QString::number(dateTimeGps.date().day()));
                    }
                    exifData["Exif.GPSInfo.GPSDateStamp"] = dateRational.toStdString();

                    QString softwareTag = QApplication::applicationName();
                    softwareTag += " ";
                    softwareTag += QApplication::applicationVersion();
                    exifData["Exif.Image.Software"] = softwareTag.toStdString();

                    exifData["Exif.GPSInfo.GPSVersionID"] = "2 2 0 0";
                    exifData["Exif.GPSInfo.GPSMapDatum"] = "WGS-84";

                    if (posicaoLocalizada->getAltitude() < 0) {
                        exifData["Exif.GPSInfo.GPSAltitudeRef"] = "1";
                    } else {
                        exifData["Exif.GPSInfo.GPSAltitudeRef"] = "0";
                    }
                    exifData["Exif.GPSInfo.GPSAltitude"] = Exiv2::floatToRationalCast(posicaoLocalizada->getAltitude());
                   
                    itemLatitude = QVariant(posicaoLocalizada->getLatitude()).toString();
                    itemLongitude = QVariant(posicaoLocalizada->getLongitude()).toString();
                    itemAltitude = QVariant(posicaoLocalizada->getAltitude()).toString();
                    itemStatus = QString::fromUtf8("OK - ") + QString::fromUtf8("proximidade: ") + QVariant(menorTolerancia).toString() + QString::fromUtf8(" seg.");
                    QTableWidgetItem *item;
                    item = new QTableWidgetItem();
                    item->setText(itemLatitude);
                    tableWidgetJpeg->setItem(i, 3, item);
                    item = new QTableWidgetItem();
                    item->setText(itemLongitude);
                    tableWidgetJpeg->setItem(i, 4, item);
                    item = new QTableWidgetItem();
                    item->setText(itemAltitude);
                    tableWidgetJpeg->setItem(i, 5, item);
                    item = new QTableWidgetItem();
                    item->setText(itemStatus);
                    tableWidgetJpeg->setItem(i, 6, item);
                    image->writeMetadata();
                } else {
                    if (status == 1) {
                        itemStatus = QString::fromUtf8("Ponto mais próximo: ") + QVariant(menorTolerancia).toString() + QString::fromUtf8(" seg.");
                    } else {
                        itemStatus = QString::fromUtf8("Fora do periodo do tracklog");
                    }
                    item = new QTableWidgetItem();
                    item->setText(itemStatus);
                    tableWidgetJpeg->setItem(i, 6, item);
                }
            }
            catch (Exiv2::AnyError& e) {
                switch (e.code()) {
                    case 2:
                        itemStatus = QString::fromUtf8("Erro ao Remover Arquivo");
                        listErrorRemoveFile.push_back(tableWidgetJpeg->item(i, 7)->text());
                        listErrorRemoveFilePosition.push_back(i);
                        break;
                    case 9:
                        itemStatus = QString::fromUtf8("Arquivo Não Existe");
                        break;
                    case 10:
                        itemStatus = QString::fromUtf8("Arquivo Somente Leitura");
                        break;
                    case 11:
                        itemStatus = QString::fromUtf8("Arquivo Inválido");
                        break;
                }
                item = new QTableWidgetItem();
                item->setForeground(QColor(255, 0, 0));
                item->setText(itemStatus);
                tableWidgetJpeg->setItem(i, 6, item);
            }
        } else {
            itemStatus = QString::fromUtf8("Sem Dados para Posicionar");
            item = new QTableWidgetItem();
            item->setText(itemStatus);
            tableWidgetJpeg->setItem(i, 6, item);
        }
    }

    for (int i = 0; i < listErrorRemoveFile.size(); i++) {
        //precisa pesquisar no disco se tem outro arquivo com o nome igual mas com a estensão diferente
        // se achar, tem que remover o atual e renomear o outro arquivo.
        QString fileName;
        QString filePath;
        int pos;

        pos = listErrorRemoveFile.at(i).lastIndexOf("/");
        fileName.operator =(QString::fromUtf8(listErrorRemoveFile.at(i).right(listErrorRemoveFile.at(i).size() - pos - 1).toStdString().c_str()));
        filePath = listErrorRemoveFile.at(i).left(pos);
        QDir directory(filePath);
        QStringList filesOnDirectory = directory.entryList(QDir::Files);
        QString regularExpression(fileName);
        regularExpression.append("[0-9]{1,4}");
        QRegExp fileRegExp(regularExpression, Qt::CaseSensitive, QRegExp::RegExp);
        QStringList filesLocated = filesOnDirectory.filter(fileRegExp);
        for (int j = 0; j < filesLocated.size(); j++) {
            itemStatus = QString::fromUtf8("Não Foi Possível Corrigir o Arquivo, Verifique Manualmente");
            QFileInfo fileTemp(directory, filesLocated.at(j));
            QFileInfo fileCurrent(directory, fileName);
            if (fileTemp.size() > fileCurrent.size()) {
                if (directory.remove(fileName)) {
                    if (directory.rename(filesLocated.at(j), fileName)) {
                        itemStatus = QString::fromUtf8("O Erro no Arquivo foi Corrigido");
                        //       delete tableWidgetJpeg->takeItem(listErrorRemoveFilePosition.at(i), 3);
                        //       delete tableWidgetJpeg->takeItem(listErrorRemoveFilePosition.at(i), 4);
                        //      delete tableWidgetJpeg->takeItem(listErrorRemoveFilePosition.at(i), 5);
                    }
                }
            } else {
                if (directory.remove(filesLocated.at(j)))
                    itemStatus = QString::fromUtf8("O Erro no Arquivo foi Corrigido");
            }
            item = new QTableWidgetItem();
            item->setForeground(QColor(0, 110, 0));
            item->setText(itemStatus);
            tableWidgetJpeg->setItem(listErrorRemoveFilePosition.at(i), 6, item);
        }
    }

    emit progressBarValue(tableWidgetJpeg->rowCount());
    sleep(1);
    emit progressBarSetVisible(false);
}

void ThreadPositionImages::setThreadPositionImages(PeriodoTracklog *periodoTracklog, QTableWidget *tableWidgetJpeg, QProgressBar *progressBar,
        uint segundosTolerancia, QLineEdit *lineEditFusoHorario, QCheckBox *checkBoxHorarioDeVerao) {
    this->tableWidgetJpeg = tableWidgetJpeg;
    this->progressBar = progressBar;
    this->periodoTrackLog = periodoTracklog;
    this->segundosTolerancia = segundosTolerancia;
    this->lineEditFusoHorario = lineEditFusoHorario;
    this->checkBoxHorarioDeVerao = checkBoxHorarioDeVerao;
}

void ThreadPositionImages::convertLatitudeGrausToExifFormat(double graus, QString &coordenadas, QString &referencia) {
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

void ThreadPositionImages::convertLongitudeGrausToExifFormat(double graus, QString &coordenadas, QString &referencia) {
    double parteFracionaria, temp;
    double grausConvertidos, minutosConvertidos, segundosConvertidos;

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

QDateTime ThreadPositionImages::convertGmtTimeToLocal(QDateTime horaOriginal) {
    QString fusoHorario = lineEditFusoHorario->text();
    int hora, min, segundosCorrecao;

    hora = atoi(fusoHorario.toStdString().substr(0, fusoHorario.indexOf(":")).c_str());
    segundosCorrecao = hora * 3600;
    min = atoi(fusoHorario.toStdString().substr(fusoHorario.indexOf(":") + 1, fusoHorario.size()).c_str());
    if (hora < 0) {
        segundosCorrecao -= min * 60;
    } else {
        segundosCorrecao += min * 60;
    }
    if (checkBoxHorarioDeVerao->isChecked()) {
        segundosCorrecao += 3600;
    }

    QDateTime dataHoraCorrigido(horaOriginal.addSecs(segundosCorrecao));
    return dataHoraCorrigido;
}

QDateTime ThreadPositionImages::convertLocalTimeToGmt(QDateTime horaOriginal) {
    QString fusoHorario = lineEditFusoHorario->text();
    int hora, min, segundosCorrecao;

    hora = atoi(fusoHorario.toStdString().substr(0, fusoHorario.indexOf(":")).c_str());
    segundosCorrecao = hora * 3600;
    min = atoi(fusoHorario.toStdString().substr(fusoHorario.indexOf(":") + 1, fusoHorario.size()).c_str());
    if (hora < 0) {
        segundosCorrecao -= min * 60;
    } else {
        segundosCorrecao += min * 60;
    }

    if (checkBoxHorarioDeVerao->isChecked()) {
        segundosCorrecao += 3600;
    }
    QDateTime dataHoraCorrigido(horaOriginal.addSecs(-segundosCorrecao));
    return dataHoraCorrigido;
}
