/* 
 * File:   GraphicsView.cpp
 * Author: Adonai Silveira Canez
 * 
 * Created on 23 de Setembro de 2010, 09:06
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

#include "GraphicsView.h"
#include <QtGui/QWheelEvent>
#include <math.h>
#include <QGraphicsItem>

GraphicsView::GraphicsView(QWidget* parent) : QGraphicsView(parent) {
    sceneGraphic = new GraphicsScene(this);
    setScene(sceneGraphic);

    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setCursor(Qt::ArrowCursor);
    setFrameShape(QFrame::NoFrame); // evita aparecer as barras de rolagem à toa
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    setResizeAnchor(AnchorViewCenter);

    centerOn(0, 0);
    scale(1, 1);
    zoom = 0;
    estadoLista = 0;
    setMatrix(matrixImage);
}

GraphicsView::~GraphicsView() {
    delete sceneGraphic;
}

void GraphicsView::wheelEvent(QWheelEvent *event) {
    int zoomType = event->delta();
    QMatrix m = matrixImage;

    switch (zoom) {
        case -3:
            if (zoomType > 0) {
                m.scale(0.5, 0.5);
                zoom = -2;
                setMatrix(m);
            }
            break;
        case -2:
            if (zoomType < 0) {
                m.scale(0.25, 0.25);
                zoom = -3;
            } else {
                m.scale(0.75, 0.75);
                zoom = -1;
            }
            setMatrix(m);
            break;
        case -1:
            if (zoomType < 0) {
                m.scale(0.5, 0.5);
                zoom = -2;
            } else {
                m.scale(1, 1);
                zoom = 0;
            }
            setMatrix(m);
            break;
        case 0:
            if (zoomType < 0) {
                m.scale(0.75, 0.75);
                zoom = -1;
            } else {
                m.scale(1.25, 1.25);
                zoom = 1;
            }
            setMatrix(m);
            break;
        case 1:
            if (zoomType < 0) {
                m.scale(1, 1);
                zoom = 0;
            } else {
                m.scale(1.5, 1.5);
                zoom = 2;
            }
            setMatrix(m);
            break;
        case 2:
            if (zoomType < 0) {
                m.scale(1.25, 1.25);
                zoom = 1;
            } else {
                m.scale(1.75, 1.75);
                zoom = 3;
            }
            setMatrix(m);
            break;
        case 3:
            if (zoomType < 0) {
                m.scale(1.5, 1.5);
                zoom = 2;

            } else {
                m.scale(2, 2);
                zoom = 4;
            }
            setMatrix(m);
            break;
        case 4:
            if (zoomType < 0) {
                m.scale(1.75, 1.75);
                zoom = 3;
            } else {
                m.scale(2.25, 2.25);
                zoom = 5;
            }
            setMatrix(m);
            break;
        case 5:
            if (zoomType < 0) {
                m.scale(2, 2);
                zoom = 4;
                setMatrix(m);
            }
            break;
    }
}

void GraphicsView::scaleView(double scaleFactor) {
    double factor = matrix().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.3 || factor > 5)
        return;
    scale(scaleFactor, scaleFactor);
}