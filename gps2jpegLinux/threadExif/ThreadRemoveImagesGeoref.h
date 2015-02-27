/* 
 * File:   ThreadRemoveImagesGeoref.h
 * Author: Adonai Silveira Canez
 *
 * Created on 3 de Abril de 2011, 19:16
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

#ifndef THREADREMOVEIMAGESGEOREF_H
#define	THREADREMOVEIMAGESGEOREF_H

#include <QtCore/QThread>

class QTableWidget;
class QProgressBar;

class ThreadRemoveImagesGeoref : public QThread {
    Q_OBJECT
public:
    ThreadRemoveImagesGeoref(QObject *parent);
    void setTableWidget(QTableWidget *tableWidgetJpeg, QProgressBar *progressBar);

protected:
    void run();

private:
    QTableWidget *tableWidgetJpeg;
    QProgressBar *progressBar;
};

#endif	/* THREADREMOVEIMAGESGEOREF_H */

