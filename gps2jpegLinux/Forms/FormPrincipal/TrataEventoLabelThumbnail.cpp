/* 
 * File:   TrataEventoLabelThumbnail.cpp
 * Author: Adonai Silveira Canez
 * 
 * Created on 27 de Outubro de 2009, 03:32
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

#include "TrataEventoLabelThumbnail.h"

TrataEventoLabelThumbnail::TrataEventoLabelThumbnail(QWidget *parent = 0) : QLabel(parent) {

}

TrataEventoLabelThumbnail::~TrataEventoLabelThumbnail() {

}

void TrataEventoLabelThumbnail::mouseDoubleClickEvent(QMouseEvent *event){
   Q_UNUSED(event);
    emit duploClick();
}
