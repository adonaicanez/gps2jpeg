/* 
 * File:   TrataEventoLabelPaypal.h
 * Author: Adonai Silveira Canez
 *
 * Created on 3 de Fevereiro de 2010, 03:31
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

#ifndef _TRATAEVENTOLABELPAYPAL_H
#define	_TRATAEVENTOLABELPAYPAL_H

#include <QtWidgets/QLabel>

class TrataEventoLabelPaypal : public QLabel {
    Q_OBJECT
public:
    TrataEventoLabelPaypal(QWidget *parent);
    virtual ~TrataEventoLabelPaypal();
private:
    void mousePressEvent(QMouseEvent *event);
};

#endif	/* _TRATAEVENTOLABELPAYPAL_H */

