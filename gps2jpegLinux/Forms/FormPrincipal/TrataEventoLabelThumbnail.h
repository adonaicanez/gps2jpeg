/* 
 * File:   TrataEventoLabelThumbnail.h
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

#ifndef _TRATAEVENTOLABELTHUMBNAIL_H
#define	_TRATAEVENTOLABELTHUMBNAIL_H

#include <QtWidgets/QLabel>

class TrataEventoLabelThumbnail : public QLabel {
    Q_OBJECT
public:
    TrataEventoLabelThumbnail(QWidget *parent);
    virtual ~TrataEventoLabelThumbnail();
private:
    void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    void duploClick();
};

#endif	/* _TRATAEVENTOLABELTHUMBNAIL_H */

