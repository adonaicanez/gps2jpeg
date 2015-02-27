/* 
 * File:   ThreadRemoveFileNoDate.cpp
 * Author: Adonai S. Canez
 * 
 * Created on 5 de Abril de 2011, 00:52
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

#include "ThreadRemoveFileNoDate.h"

#include <QtGui/QTableWidget>

ThreadRemoveFileNoDate::ThreadRemoveFileNoDate(QObject *parent) : QThread(parent) {
}

void ThreadRemoveFileNoDate::setTableWidget(QTableWidget *tableWidgetJpeg, QProgressBar *progressBar) {
    this->tableWidgetJpeg = tableWidgetJpeg;
    this->progressBar = progressBar;
}

void ThreadRemoveFileNoDate::run() {
    for (int i = 0; i < tableWidgetJpeg->rowCount(); i++) {
        if (tableWidgetJpeg->item(i, 2) == 0) {
            for (int j = 0; j < tableWidgetJpeg->columnCount(); j++) {
                delete tableWidgetJpeg->item(i, j);
            }
            tableWidgetJpeg->removeRow(i);
            i--;
        }
    }
}