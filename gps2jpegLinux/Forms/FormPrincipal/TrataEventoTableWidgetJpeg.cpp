/* 
 * File:   TrataEventoTableWidgetJpeg.cpp
 * Author: Adonai Silveira Canez
 * 
 * Created on 9 de Abril de 2011, 01:50
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

#include "TrataEventoTableWidgetJpeg.h"
#include "TelaPrincipal.h"

#include <QtGui/QMouseEvent>
#include <QtWidgets/QMenu>
#include <QtWidgets/QAction>

#include <QtCore/QEventLoop>
#include <iostream>

TrataEventoTableWidgetJpeg::TrataEventoTableWidgetJpeg(QWidget *parent = 0) : QTableWidget(parent) {
}

TrataEventoTableWidgetJpeg::~TrataEventoTableWidgetJpeg() {
}

void TrataEventoTableWidgetJpeg::mousePressEvent(QMouseEvent *event) {
    QTableWidget::mousePressEvent(event);

    if (event->button() == Qt::RightButton) {
        QMenu me(this);
        connect(&me, SIGNAL(aboutToHide()), this, SLOT(fecharMenu()));

        QAction ac2(trUtf8("Exibir Foto"), this);
        connect(&ac2, SIGNAL(triggered()), this, SLOT(exibirFoto()));
        ac2.setData("1");
        me.addAction(&ac2);

        QAction ac3(trUtf8("Remover da Lista"), this);
        ac3.setData("2");
        me.addAction(&ac3);

        me.addSeparator();
        QAction ac1(QIcon(":/IconesMenu/error.png"), "Fechar", this);
        me.addAction(&ac1);

        QAction *actionSelected = me.exec(event->globalPos());
        if (actionSelected != NULL) {
            switch (actionSelected->data().toInt()) {
                case 1:
                    emit exibirFoto();
                    break;
                case 2:
                    removeRow(indexAt(event->pos()).row());
                    emit imagemRemovidaDaLista();
                    break;
            }
        }
    }
    //   event->ignore();
}