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

#ifndef THREADPOSITIONIMAGES_H
#define	THREADPOSITIONIMAGES_H

#include <QtCore/QThread>
#include <QtCore/QDateTime>
#include <QtCore/QString>
#include <QtGui/QMainWindow>

#include "ThreadLoadExifDatas.h"

class QTableWidget;
class QProgressBar;
class PeriodoTracklog;
class QCheckBox;
class QCoreApplication;

class ThreadPositionImages : public QThread {
    Q_OBJECT
public:
    ThreadPositionImages(QObject *parent);
    void setThreadPositionImages(PeriodoTracklog *periodoTracklog, QTableWidget *tableWidgetJpeg,
            QProgressBar *progressBar, uint segundosTolerancia, QLineEdit *lineEditFusoHorario, QCheckBox *checkBoxHorarioDeVerao);

protected:
    void run();

private:
    QTableWidget *tableWidgetJpeg;
    QProgressBar *progressBar;
    PeriodoTracklog *periodoTrackLog;
    int segundosTolerancia;
    QLineEdit *lineEditFusoHorario;
    QCheckBox *checkBoxHorarioDeVerao;

    void convertLatitudeGrausToExifFormat(double graus, QString &coordenadas, QString &referencia);
    void convertLongitudeGrausToExifFormat(double graus, QString &coordenadas, QString &referencia);

    QDateTime convertGmtTimeToLocal(QDateTime horaOriginal);
    QDateTime convertLocalTimeToGmt(QDateTime horaOriginal);

signals:
    void progressBarValue(int value);
    void progressBarSetVisible(bool visible);
};

#endif	/* THREADPOSITIONIMAGES_H */
