/*
 * File:   AddMetadata.cpp
 * Author: Adonai Silveira Canez
 *
 * Created on 5 de Outubro de 2010, 20:54
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

#include "AddMetadata.h"
#include "ExibeFoto/GraphicsView.h"

AddMetadata::AddMetadata(QWidget *parent, Qt::WindowFlags flags) : QMainWindow(parent, flags) {
    widget.setupUi(this);

    connect(widget.buttonBox, SIGNAL(clicked(QAbstractButton *)), this, SLOT(botaoClicado(QAbstractButton *)));
    QList<QAbstractButton*> listButtons = widget.buttonBox->buttons();
    QIcon *icon;
    for (int i = 0; i < listButtons.size(); i++) {
        QDialogButtonBox::StandardButton button = widget.buttonBox->standardButton(listButtons.at(i));
        switch (button) {
            case QDialogButtonBox::Close:
                icon = new QIcon(":/IconesMenu/error.png");
                listButtons.at(i)->setIcon(*icon);
                emit fechaMetadata();
                break;

            case QDialogButtonBox::Ok:
                emit fechaMetadata();
                break;

            case QDialogButtonBox::SaveAll:
                icon = new QIcon(":/IconesMenu/filesaveas.png");
                listButtons.at(i)->setIcon(*icon);
                break;

            default:
                break;
        }
    }
}

AddMetadata::~AddMetadata() {
}

void AddMetadata::botaoClicado(QAbstractButton *botao) {
    QDialogButtonBox::StandardButton sb;
    sb = widget.buttonBox->standardButton(botao);

    switch (sb) {
        case QDialogButtonBox::Ok:
            saveAllMetadatas();
            close();
            break;

        case QDialogButtonBox::Close:
            close();
            break;

        case QDialogButtonBox::Save:
            saveAllMetadatas();
            break;

        default:
            break;
    }
}

void AddMetadata::saveAllMetadatas() {

}
