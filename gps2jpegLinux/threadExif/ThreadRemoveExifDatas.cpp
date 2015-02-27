/* 
 * File:   ThreadRemoveExifDatas.cpp
 * Author: Adonai Silveira Canez
 * 
 * Created on 6 de Março de 2010, 23:20
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

#include "ThreadRemoveExifDatas.h"
#include "DadosArquivoGps.h"

#include <QtCore/QDir>
#include <QtGui/QApplication>
#include <QtGui/QTableWidget>
#include <QtGui/QProgressBar>

#include <cassert>
#include <math.h>
#include <exiv2/image.hpp>
#include <exiv2/exif.hpp>

ThreadRemoveExifDatas::ThreadRemoveExifDatas(QObject *parent) : QThread(parent) {
}

void ThreadRemoveExifDatas::setTableWidget(QTableWidget *tableWidgetJpeg, QProgressBar *progressBar) {
    this->tableWidgetJpeg = tableWidgetJpeg;
    this->progressBar = progressBar;
}

void ThreadRemoveExifDatas::run() {
    QTableWidgetItem *item;
 
    Exiv2::ExifData::iterator keyIteratorRemove;
    Exiv2::ExifKey *keyRemove;

    QVector<QString> listErrorRemoveFile;
    QVector<int> listErrorRemoveFilePosition;

    connect(this, SIGNAL(progressBarValue(int)), progressBar, SLOT(setValue(int)));
    connect(this, SIGNAL(progressBarSetVisible(bool)), progressBar, SLOT(setVisible(bool)));
    emit progressBarSetVisible(true);
    progressBar->setRange(0, tableWidgetJpeg->rowCount());

    for (int i = 0; i < tableWidgetJpeg->rowCount(); i++) {
        try {
            emit progressBarValue(i);
            //  usleep(50000);
            Exiv2::Image::AutoPtr image;

            image = Exiv2::ImageFactory::open(tableWidgetJpeg->item(i, 7)->text().toStdString().c_str());

            if (tableWidgetJpeg->item(i, 3) != 0 || tableWidgetJpeg->item(i, 4) != 0 || tableWidgetJpeg->item(i, 5) != 0) {
                bool exifRemovido = false;
                assert(image.get() != 0);
                image->readMetadata();
                Exiv2::ExifData &exifData = image->exifData();

                Exiv2::ExifKey keyLatitude = Exiv2::ExifKey("Exif.GPSInfo.GPSLatitude");
                keyIteratorRemove = exifData.findKey(keyLatitude);
                if (keyIteratorRemove != exifData.end()) {
                    exifData.erase(keyIteratorRemove);
                    exifRemovido = true;
                }

                keyRemove = new Exiv2::ExifKey("Exif.GPSInfo.GPSTimeStamp");
                keyIteratorRemove = exifData.findKey(*keyRemove);
                if (keyIteratorRemove != exifData.end()) {
                    exifData.erase(keyIteratorRemove);
                    exifRemovido = true;
                }

                keyRemove = new Exiv2::ExifKey("Exif.GPSInfo.GPSDateStamp");
                keyIteratorRemove = exifData.findKey(*keyRemove);
                if (keyIteratorRemove != exifData.end()) {
                    exifData.erase(keyIteratorRemove);
                    exifRemovido = true;
                }

                keyRemove = new Exiv2::ExifKey("Exif.GPSInfo.GPSVersionID");
                keyIteratorRemove = exifData.findKey(*keyRemove);
                if (keyIteratorRemove != exifData.end()) {
                    exifData.erase(keyIteratorRemove);
                    exifRemovido = true;
                }

                keyRemove = new Exiv2::ExifKey("Exif.GPSInfo.GPSMapDatum");
                keyIteratorRemove = exifData.findKey(*keyRemove);
                if (keyIteratorRemove != exifData.end()) {
                    exifData.erase(keyIteratorRemove);
                    exifRemovido = true;
                }

                keyRemove = new Exiv2::ExifKey("Exif.GPSInfo.GPSLatitudeRef");
                keyIteratorRemove = exifData.findKey(*keyRemove);
                if (keyIteratorRemove != exifData.end()) {
                    exifData.erase(keyIteratorRemove);
                }

                keyRemove = new Exiv2::ExifKey("Exif.GPSInfo.GPSLongitude");
                keyIteratorRemove = exifData.findKey(*keyRemove);
                if (keyIteratorRemove != exifData.end()) {
                    exifData.erase(keyIteratorRemove);
                    exifRemovido = true;
                }

                keyRemove = new Exiv2::ExifKey("Exif.GPSInfo.GPSLongitudeRef");
                keyIteratorRemove = exifData.findKey(*keyRemove);
                if (keyIteratorRemove != exifData.end()) {
                    exifData.erase(keyIteratorRemove);
                }

                keyRemove = new Exiv2::ExifKey("Exif.GPSInfo.GPSAltitude");
                keyIteratorRemove = exifData.findKey(*keyRemove);
                if (keyIteratorRemove != exifData.end()) {
                    exifData.erase(keyIteratorRemove);
                    exifRemovido = true;
                }

                keyRemove = new Exiv2::ExifKey("Exif.GPSInfo.GPSAltitudeRef");
                keyIteratorRemove = exifData.findKey(*keyRemove);
                if (keyIteratorRemove != exifData.end()) {
                    exifData.erase(keyIteratorRemove);
                    exifRemovido = true;
                }

                if (exifRemovido) {
                    QString softwareTag = QApplication::applicationName();
                    softwareTag += " ";
                    softwareTag += QApplication::applicationVersion();
                    exifData["Exif.Image.Software"] = softwareTag.toStdString();
                }
                image->setExifData(exifData);
                image->writeMetadata();
                QString itemStatus = QString::fromUtf8("Dados Removidos");
                item = new QTableWidgetItem();
                item->setText(itemStatus);
                delete tableWidgetJpeg->takeItem(i, 3);
                delete tableWidgetJpeg->takeItem(i, 4);
                delete tableWidgetJpeg->takeItem(i, 5);
                tableWidgetJpeg->setItem(i, 6, item);
            } else {
                QString itemStatus = QString::fromUtf8("Não Há Dados Para Remover");
                item = new QTableWidgetItem();
                item->setText(itemStatus);
                tableWidgetJpeg->setItem(i, 6, item);
            }
        }
        catch (Exiv2::AnyError& e) {
            QString itemMsg;
            switch (e.code()) {
                case 2:
                    itemMsg = QString::fromUtf8("Erro ao Remover Arquivo");
                    // Quando ocorrer erro na remoção do arquivo, ele será colocado numa lista para
                    // que ao fim da execução seja tentado mais uma vez a sua remoção.
                    listErrorRemoveFile.push_back(tableWidgetJpeg->item(i, 7)->text());
                    listErrorRemoveFilePosition.push_back(i);
                    break;
                case 9:
                    itemMsg = QString::fromUtf8("Erro de Acesso ao Arquivo");
                    break;
                case 10:
                    itemMsg = QString::fromUtf8("Arquivo Somente Leitura");
                    break;
                case 11:
                    itemMsg = QString::fromUtf8("Arquivo Inválido");
                    break;
            }
            item = new QTableWidgetItem();
            item->setForeground(QColor(255, 0, 0));
            item->setText(itemMsg);
            tableWidgetJpeg->setItem(i, 6, item);
        }
    }

    for (int i = 0; i < listErrorRemoveFile.size(); i++) {
        //precisa pesquisar no disco se tem outro arquivo com o nome igual mas com a estensão diferente
        // se achar, tem que remover o atual e renomear o outro arquivo.
        QString fileName;
        QString filePath;
        QString itemMsg;
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
            itemMsg = QString::fromUtf8("Não Foi Possível Corrigir o Arquivo, Verifique Manualmente");
            QFileInfo fileTemp(directory, filesLocated.at(j));
            QFileInfo fileCurrent(directory, fileName);
            if (fileTemp.size() > fileCurrent.size()) {
                if (directory.remove(fileName)) {
                    if (directory.rename(filesLocated.at(j), fileName)) {
                        itemMsg = QString::fromUtf8("O Erro no Arquivo foi Corrigido");
                        delete tableWidgetJpeg->takeItem(listErrorRemoveFilePosition.at(i), 3);
                        delete tableWidgetJpeg->takeItem(listErrorRemoveFilePosition.at(i), 4);
                        delete tableWidgetJpeg->takeItem(listErrorRemoveFilePosition.at(i), 5);
                    }
                }
            } else {
                if (directory.remove(filesLocated.at(j)))
                    itemMsg = QString::fromUtf8("O Erro no Arquivo foi Corrigido");
            }
            item = new QTableWidgetItem();
            item->setForeground(QColor(0, 110, 0));
            item->setText(itemMsg);
            tableWidgetJpeg->setItem(listErrorRemoveFilePosition.at(i), 6, item);
        }
    }
    emit progressBarValue(tableWidgetJpeg->rowCount());
    sleep(1);
    emit progressBarSetVisible(false);
}