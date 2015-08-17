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

#ifndef _THREADLOADEXIFDATAS_H
#define	_THREADLOADEXIFDATAS_H

#include <QtCore/QObject>
#include <QtCore/QThread>
#include <QtCore/QDateTime>
#include <QtCore/QStringList>

class QTableWidget;
class QLineEdit;
class QProgressBar;

class ThreadLoadExifDatas : public QThread {
    Q_OBJECT
public:
    ThreadLoadExifDatas();
    ~ThreadLoadExifDatas();
    void setTableWidget(QTableWidget *tableWidgetJpeg, QLineEdit *lineEditCorrecaoTempoFotos, QProgressBar *progressBar);
    void setListImagesFiles(const QStringList &listImagesFiles);

protected:
    void run();

private:
    void LoadExifDatasImage(QString pathArquivoJpeg, QDateTime& itemDataHora, QString& itemLatitude,
            QString& itemLongitude, QString& itemAltitude, QString& itemMsg, int &status);
    QTableWidget *tableWidgetJpeg;
    QLineEdit *lineEditCorrecaoTempoFotos;
    QProgressBar *progressBar;
    QStringList listaArquivos;

signals:
    void progressBarValue(int value);
    void progressBarSetVisible(bool visible);

};

#endif	/* _THREADLOADEXIFDATAS_H */