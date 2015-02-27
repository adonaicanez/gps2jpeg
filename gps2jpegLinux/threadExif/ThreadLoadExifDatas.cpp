/* 
 * File:   ThreadLoadExifDatas.cpp
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

#include "ThreadLoadExifDatas.h"
#include "Forms/FormPrincipal/TelaPrincipal.h"
#include "DadosArquivoGps.h"

#include <QtGui/QTableWidget>
#include <QtGui/QProgressBar>

#include <cassert>
#include <math.h>
#include <exiv2/image.hpp>
#include <exiv2/exif.hpp>

ThreadLoadExifDatas::ThreadLoadExifDatas() {
}

ThreadLoadExifDatas::~ThreadLoadExifDatas() {
}

void ThreadLoadExifDatas::run() {
    int linha, tamanho, pos;
    QTableWidgetItem *item;
    int status;

    connect(this, SIGNAL(progressBarValue(int)), progressBar, SLOT(setValue(int)));
    connect(this, SIGNAL(progressBarSetVisible(bool)), progressBar, SLOT(setVisible(bool)));

    emit progressBarSetVisible(true);
    progressBar->setRange(0, listaArquivos.size());
    for (int i = 0; i < listaArquivos.size(); i++) {
        emit progressBarValue(i);
        //    usleep(50000);
        QDateTime itemDataHora;
        QString itemLatitude, itemLongitude, itemAltitude, itemMsg;
        LoadExifDatasImage(listaArquivos.at(i), itemDataHora, itemLatitude, itemLongitude, itemAltitude, itemMsg, status);

        tableWidgetJpeg->setRowCount(tableWidgetJpeg->rowCount() + 1);
        linha = tableWidgetJpeg->rowCount();
        if (status == 0) {
            // adiciona os dados da coluna 0 da tabela (nome do arquivo)
            item = new QTableWidgetItem();
            pos = listaArquivos.at(i).lastIndexOf("/");
            tamanho = listaArquivos.at(i).size();
            item->setText(listaArquivos.at(i).right(tamanho - pos - 1));
            tableWidgetJpeg->setItem(linha - 1, 0, item);
            // Adiciona os dados da coluna 7 da tabela (caminho completo do arquivo)
            item = new QTableWidgetItem();
            item->setText(listaArquivos.at(i));
            tableWidgetJpeg->setItem(linha - 1, 7, item);

            // adiciona a data da foto
            if (!itemDataHora.isNull()) {
                item = new QTableWidgetItem(itemDataHora.toString("dd/MM/yyyy hh:mm:ss"));
          //      item->
                 //    widget.tableWidgetJpeg->setContextMenuPolicy
    //  widget.tableWidgetJpeg->setContextMenuPolicy(Qt::ActionsContextMenu);
 //   widget.tableWidgetJpeg->addAction(widget.actionRemoverImagem);
//    widget.tableWidgetJpeg->addAction(widget.actionSair);




                tableWidgetJpeg->setItem(linha - 1, 1, item);
                // adiciona a data corrigida da foto
                QDateTime dataHoraFotoCorrigida(itemDataHora.addSecs(lineEditCorrecaoTempoFotos->text().toInt()));
                item = new QTableWidgetItem(dataHoraFotoCorrigida.toString("dd/MM/yyyy hh:mm:ss"));
                tableWidgetJpeg->setItem(linha - 1, 2, item);
            }
            // adiciona a latitude
            if (!itemLatitude.isNull()) {
                item = new QTableWidgetItem(itemLatitude);
                tableWidgetJpeg->setItem(linha - 1, 3, item);
            }
            // adiciona a longitude
            if (!itemLongitude.isNull()) {
                item = new QTableWidgetItem(itemLongitude);
                tableWidgetJpeg->setItem(linha - 1, 4, item);
            }
            // adiciona a altitude
            if (!itemAltitude.isNull()) {
                item = new QTableWidgetItem(itemAltitude);
                tableWidgetJpeg->setItem(linha - 1, 5, item);
            }
            // adiciona o status
            item = new QTableWidgetItem(itemMsg);
            tableWidgetJpeg->setItem(linha - 1, 6, item);
        }
        if (status >= 1) {
            // adiciona os dados da coluna 0 da tabela (nome do arquivo)
            item = new QTableWidgetItem();
            pos = listaArquivos.at(i).lastIndexOf("/");
            tamanho = listaArquivos.at(i).size();
            item->setText(listaArquivos.at(i).right(tamanho - pos - 1));
            tableWidgetJpeg->setItem(linha - 1, 0, item);
            // Adiciona os dados da coluna 7 da tabela (caminho completo do arquivo)
            item = new QTableWidgetItem();
            item->setText(listaArquivos.at(i));
            tableWidgetJpeg->setItem(linha - 1, 7, item);
            // adiciona o status
            item = new QTableWidgetItem(itemMsg);
            if (status == 2) {
                item->setForeground(QColor(255, 0, 0));
            }
            tableWidgetJpeg->setItem(linha - 1, 6, item);
        }
    }
    emit progressBarValue(listaArquivos.size());
    sleep(1);
    emit progressBarSetVisible(false);
}

void ThreadLoadExifDatas::setTableWidget(QTableWidget *tableWidgetJpeg, QLineEdit *lineEditCorrecaoTempoFotos, QProgressBar *progressBar) {
    this->tableWidgetJpeg = tableWidgetJpeg;
    this->lineEditCorrecaoTempoFotos = lineEditCorrecaoTempoFotos;
    this->progressBar = progressBar;
}

void ThreadLoadExifDatas::setListImagesFiles(const QStringList &listImagesFiles) {
    listaArquivos = listImagesFiles;
}

void ThreadLoadExifDatas::LoadExifDatasImage(QString pathArquivoJpeg, QDateTime& itemDataHora, QString& itemLatitude,
        QString& itemLongitude, QString& itemAltitude, QString& itemMsg, int &status) {

    QString tagExiv;
    int dia, mes, ano;
    int hora, minuto, segundo;
    bool latitudeNegativo, longitudeNegativo, altitudeNegativo;
    bool possuiLatitudeExif, possuiLongitudeExif, possuiAltitudeExif;

    possuiLatitudeExif = false;
    possuiLongitudeExif = false;
    possuiAltitudeExif = false;
    latitudeNegativo = false;
    longitudeNegativo = false;
    altitudeNegativo = false;
    Exiv2::Image::AutoPtr image;

    try {
#ifdef Q_WS_WIN
        image = Exiv2::ImageFactory::open(pathArquivoJpeg.toStdString().c_str());
#endif
#ifdef Q_WS_X11
        QString nomeUtf(pathArquivoJpeg.toUtf8());
        image = Exiv2::ImageFactory::open(nomeUtf.toStdString().c_str());
#endif
        assert(image.get() != 0);
        image->readMetadata();
        Exiv2::ExifData &exifData = image->exifData();

        if (exifData.empty()) {
            itemMsg = QString::fromUtf8("Sem dados Exif");
        } else {
            Exiv2::ExifData::const_iterator end = exifData.end();
            double latitude = 0, longitude = 0, altitude = 0;
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
                    possuiAltitudeExif = true;
                    int pos1, pos2;
                    double val1, val2;
                    QString posicaoAltitude = QString(i->value().toString().c_str());

                    pos1 = posicaoAltitude.indexOf('/');
                    pos2 = posicaoAltitude.size();

                    val1 = posicaoAltitude.mid(0, pos1).toDouble();
                    val2 = posicaoAltitude.mid(pos1 + 1, pos2 - pos1).toDouble();

                    altitude = (val1 / val2);


                }
                if (tagExiv.operator ==("Exif.GPSInfo.GPSAltitudeRef")) {
                    if (QString::fromStdString(i->value().toString()).operator ==("1")) {
                        altitudeNegativo = true;
                    }
                }
            }
            if (possuiLatitudeExif) {
                if (latitudeNegativo) {
                    itemLatitude = QVariant(-latitude).toString();
                } else {
                    itemLatitude = QVariant(latitude).toString();
                }
            }
            if (possuiLongitudeExif) {
                if (longitudeNegativo) {
                    itemLongitude = QVariant(-longitude).toString();
                } else {
                    itemLongitude = QVariant(longitude).toString();
                }
            }
            if (possuiAltitudeExif) {
                if (altitudeNegativo) {
                    itemAltitude = QVariant(-altitude).toString();
                } else {
                    itemAltitude = QVariant(altitude).toString();
                }
            }

            // testar se nao tem data e colocar que não tem dados de data na foto
            if (!temDataHora) {
                itemMsg = QString::fromUtf8("Sem dados Exif");
                status = 1;
            } else {
                itemMsg = QString::fromUtf8("OK");
                status = 0;
            }
        }
    }
    catch (Exiv2::AnyError& e) {
        switch (e.code()) {
            case 2:
                itemMsg = QString::fromUtf8("Erro ao Remover Arquivo - loadExifdatas.cpp");
                break;
            case 9:
                itemMsg = QString::fromUtf8("Erro de Acesso ao Arquivo - loadExifdatas.cpp");
                break;
            case 10:
                itemMsg = QString::fromUtf8("Acesso negado ao Arquivo- loadExifdatas.cpp");
                break;
            case 11:
                itemMsg = QString::fromUtf8("Arquivo Inválido- loadExifdatas.cpp");
                break;
        }
        status = 2;
    }
}