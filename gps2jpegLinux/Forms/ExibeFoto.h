/* 
 * File:   ExibeFoto.h
 * Author: Adonai Silveira Canez
 *
 * Created on 24 de Outubro de 2009, 21:26
 *
 * This file is part of gps2jpeg.
 *
 * gps2jpeg is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License.

 * gps2jpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with gps2jpeg.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _EXIBEFOTO_H
#define	_EXIBEFOTO_H

#include "ui_ExibeFoto.h"
#include "ExibeFoto/GraphicsScene.h"
#include <QtGui/QMainWindow>
#include <QtGui/QDialog>

class ExibeFoto : public QMainWindow {
    Q_OBJECT
public:
    ExibeFoto(QPixmap *image, QString path, QWidget *parent);
    virtual ~ExibeFoto();

private:
    Ui::ExibeFoto widget;
    GraphicsScene *scene;
    QString path;

    void readExifData();
    void readIptcData();
    void readXmpData();

private slots:
    void formEditMetadatas();
    void fechar();
    void alteraIconeExpanded(QTreeWidgetItem *item);
    void alteraIconeCollapsed(QTreeWidgetItem *item);

signals:
    void fechaExibeFoto();
};

#endif	/* _EXIBEFOTO_H */
