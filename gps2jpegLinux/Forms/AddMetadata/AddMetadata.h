/* 
 * File:   AddMetadata.h
 * Author: Adonai Silveira Canez
 *
 * Created on 5 de Outubro de 2010, 20:54
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


#ifndef _ADDMETADATA_H
#define	_ADDMETADATA_H

#include "ui_AddMetadata.h"

class AddMetadata : public QMainWindow {
    Q_OBJECT
public:
    AddMetadata(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    virtual ~AddMetadata();
private:
    Ui::AddMetadata widget;

    void saveAllMetadatas();

private slots:
    void botaoClicado(QAbstractButton *botao);

signals:
    void fechaMetadata();
};

#endif	/* _ADDMETADATA_H */
