/*
 * File:   ExibeFoto.cpp
 * Author: Adonai Silveira Canez
 *
 * Created on 24 de Outubro de 2009, 21:26
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

#include "ExibeFoto.h"
#include "threadExif/ThreadPositionImages.h"
#include "AddMetadata/AddMetadata.h"
#include "DadosArquivoGps.h"

#include <QtCore/QSize>
#include <QtGui/QWidget>
#include <QtGui/QWheelEvent>
#include <QtGui/QMessageBox>

#include <cassert>
#include <math.h>
#include <exiv2/image.hpp>
#include <exiv2/exif.hpp>

ExibeFoto::ExibeFoto(QPixmap *image, QString path, QWidget *parent) : QMainWindow(parent) {
    widget.setupUi(this);
    scene = new GraphicsScene();
    scene->addPixmap(*image);
    this->path = path;
    widget.graphicsView->setScene(scene);

    readExifData();
    readIptcData();
    readXmpData();

    widget.menubar->hide();

    connect(widget.treeWidgetExif, SIGNAL(itemExpanded(QTreeWidgetItem *)), this, SLOT(alteraIconeExpanded(QTreeWidgetItem*)));
    connect(widget.treeWidgetExif, SIGNAL(itemCollapsed(QTreeWidgetItem *)), this, SLOT(alteraIconeCollapsed(QTreeWidgetItem*)));
    connect(widget.treeWidgetIptc, SIGNAL(itemExpanded(QTreeWidgetItem *)), this, SLOT(alteraIconeExpanded(QTreeWidgetItem*)));
    connect(widget.treeWidgetIptc, SIGNAL(itemCollapsed(QTreeWidgetItem *)), this, SLOT(alteraIconeCollapsed(QTreeWidgetItem*)));
    connect(widget.treeWidgetXmp, SIGNAL(itemExpanded(QTreeWidgetItem *)), this, SLOT(alteraIconeExpanded(QTreeWidgetItem*)));
    connect(widget.treeWidgetXmp, SIGNAL(itemCollapsed(QTreeWidgetItem *)), this, SLOT(alteraIconeCollapsed(QTreeWidgetItem*)));
}

ExibeFoto::~ExibeFoto() {
    delete scene;
    delete widget.graphicsView;
}

void ExibeFoto::readExifData() {
    widget.treeWidgetExif->header()->setResizeMode(QHeaderView::ResizeToContents);
    Exiv2::Image::AutoPtr imageExiv;
    try {
#ifdef Q_WS_WIN
        imageExiv = Exiv2::ImageFactory::open(path.toStdString().c_str());
#endif
#ifdef Q_WS_X11
        QString nomeUtf(path.toUtf8());
        imageExiv = Exiv2::ImageFactory::open(nomeUtf.toStdString().c_str());
#endif
        assert(imageExiv.get() != 0);
        imageExiv->readMetadata();
        Exiv2::ExifData &exifData = imageExiv->exifData();
        QString tipoAtual, tipoNovo, descricao, value;
        if (!exifData.empty()) {
            Exiv2::ExifData::const_iterator end = exifData.end();
            int posExif = 0;
            QTreeWidgetItem *treeItem, *treeItemChild;
            treeItem = NULL;
            for (Exiv2::ExifData::const_iterator i = exifData.begin(); i != end; ++i) {
                QString sKeyTree(QString::fromAscii(i->key().c_str()).midRef(5).toString());
                tipoNovo = sKeyTree.left(sKeyTree.indexOf('.'));
                descricao = sKeyTree.right(sKeyTree.size() - sKeyTree.indexOf('.') - 1);
                value = QString::fromAscii(i->value().toString().c_str());
                treeItem = widget.treeWidgetExif->findItems(tipoNovo, Qt::MatchExactly).at(0);
                if (treeItem == NULL) {
                    tipoAtual.operator =(tipoNovo);
                    treeItem = new QTreeWidgetItem(widget.treeWidgetExif);
                    treeItem->setText(0, tipoNovo);
                    treeItemChild = new QTreeWidgetItem(treeItem);
                    treeItemChild->setText(0, descricao);
                    treeItemChild->setText(1, value);
                    QIcon *icon;
                    icon = new QIcon(":/IconesMenu/blue-folder-new.png");
                    widget.treeWidgetExif->topLevelItem(posExif)->setIcon(0, *icon);
                    QColor *color = new QColor(227, 227, 227);
                    QBrush *brush = new QBrush(*color);
                    widget.treeWidgetExif->topLevelItem(posExif)->setBackground(0, *brush);
                    widget.treeWidgetExif->topLevelItem(posExif)->setBackground(1, *brush);
                    posExif++;
                } else {
                    treeItemChild = new QTreeWidgetItem(treeItem);
                    treeItemChild->setText(0, descricao);
                    treeItemChild->setText(1, value);
                }
            }
        }
    }
    catch (Exiv2::AnyError& e) {
        QString erroStatus;
        switch (e.code()) {
            case 2:
                erroStatus = QString::fromUtf8("Erro ao Remover Arquivo - exibefoto.cpp");
                break;
            case 9:
                erroStatus = QString::fromUtf8("Arquivo Não Existe - exibefoto.cpp");
                break;
            case 10:
                erroStatus = QString::fromUtf8("Arquivo Somente Leitura - exibefoto.cpp");
                break;
            case 11:
                erroStatus = QString::fromUtf8("Arquivo Inválido - exibefoto.cpp");
                break;
        }
    }
}

void ExibeFoto::readIptcData() {
    widget.treeWidgetIptc->header()->setResizeMode(QHeaderView::ResizeToContents);

    try {
#ifdef Q_WS_WIN
        Exiv2::Image::AutoPtr imageExiv = Exiv2::ImageFactory::open(path.toStdString().c_str());
#endif
#ifdef Q_WS_X11
        QString nomeUtf(path.toUtf8());
        Exiv2::Image::AutoPtr imageExiv = Exiv2::ImageFactory::open(nomeUtf.toStdString().c_str());
#endif
        assert(imageExiv.get() != 0);
        imageExiv->readMetadata();
        Exiv2::IptcData &iptcData = imageExiv->iptcData();
        QString tipoAtual, tipoNovo, descricao, value;
        if (!iptcData.empty()) {
            Exiv2::IptcData::iterator end = iptcData.end();
            int posExif = 0;
            QTreeWidgetItem *treeItem, *treeItemChild;
            treeItem = NULL;
            for (Exiv2::IptcData::iterator md = iptcData.begin(); md != end; md++) {
                QString sKeyTree(QString::fromAscii(md->key().c_str()).midRef(5).toString());
                tipoNovo = sKeyTree.left(sKeyTree.indexOf('.'));
                descricao = sKeyTree.right(sKeyTree.size() - sKeyTree.indexOf('.') - 1);
                value = QString::fromAscii(md->value().toString().c_str());
                treeItem = widget.treeWidgetIptc->findItems(tipoNovo, Qt::MatchExactly).at(0);
                if (treeItem == NULL) {
                    tipoAtual.operator =(tipoNovo);
                    treeItem = new QTreeWidgetItem(widget.treeWidgetIptc);
                    treeItem->setText(0, tipoNovo);
                    treeItemChild = new QTreeWidgetItem(treeItem);
                    treeItemChild->setText(0, descricao);
                    treeItemChild->setText(1, value);
                    QIcon *icon;
                    icon = new QIcon(":/IconesMenu/blue-folder-new.png");
                    widget.treeWidgetIptc->topLevelItem(posExif)->setIcon(0, *icon);
                    QColor *co = new QColor(227, 227, 227);
                    QBrush *bu = new QBrush(*co);
                    widget.treeWidgetIptc->topLevelItem(posExif)->setBackground(0, *bu);
                    widget.treeWidgetIptc->topLevelItem(posExif)->setBackground(1, *bu);
                    posExif++;
                } else {
                    treeItemChild = new QTreeWidgetItem(treeItem);
                    treeItemChild->setText(0, descricao);
                    treeItemChild->setText(1, value);
                }
            }
        }
    }
    catch (Exiv2::Error& e) {
        QString erroStatus;
        switch (e.code()) {
            case 2:
                erroStatus = QString::fromUtf8("Erro ao Remover Arquivo");
                break;
            case 9:
                erroStatus = QString::fromUtf8("Arquivo Não Existe");
                break;
            case 10:
                erroStatus = QString::fromUtf8("Arquivo Somente Leitura");
                break;
            case 11:
                erroStatus = QString::fromUtf8("Arquivo Inválido");
                break;
        }
       QMessageBox::critical(this, QCoreApplication::applicationName() + " " + QCoreApplication::applicationVersion()
                        , trUtf8("Ocorreu um Erro ao Ler o arquivo"), QMessageBox::Ok);
    }
}

void ExibeFoto::readXmpData() {
    widget.treeWidgetXmp->header()->setResizeMode(QHeaderView::ResizeToContents);

    try {
#ifdef Q_WS_WIN
        Exiv2::Image::AutoPtr imageXmp = Exiv2::ImageFactory::open(path.toStdString().c_str());
#endif
#ifdef Q_WS_X11
        QString nomeUtf(path.toUtf8());
        Exiv2::Image::AutoPtr imageXmp = Exiv2::ImageFactory::open(nomeUtf.toStdString().c_str());
#endif
        assert(imageXmp.get() != 0);
        imageXmp->readMetadata();
        Exiv2::XmpData &xmpData = imageXmp->xmpData();
        QString tipoAtual, tipoNovo, descricao, value;
        if (!xmpData.empty()) {
            Exiv2::XmpData::iterator end = xmpData.end();
            int posExif = 0;
            QTreeWidgetItem *treeItem, *treeItemChild;
            treeItem = NULL;
            for (Exiv2::XmpData::iterator md = xmpData.begin(); md != end; md++) {
                QString sKeyTree(QString::fromUtf8(md->key().c_str()).midRef(4).toString());
                tipoNovo = sKeyTree.left(sKeyTree.indexOf('.'));
                descricao = sKeyTree.right(sKeyTree.size() - sKeyTree.indexOf('.') - 1);
                value = QString::fromUtf8(md->value().toString().c_str());

                treeItem = widget.treeWidgetXmp->findItems(tipoNovo, Qt::MatchExactly).at(0);
                if (treeItem == NULL) {
                    tipoAtual.operator =(tipoNovo);
                    treeItem = new QTreeWidgetItem(widget.treeWidgetXmp);
                    treeItem->setText(0, tipoNovo);
                    treeItemChild = new QTreeWidgetItem(treeItem);
                    treeItemChild->setText(0, descricao);
                    treeItemChild->setText(1, value);
                    QIcon *icon;
                    icon = new QIcon(":/IconesMenu/blue-folder-new.png");
                    widget.treeWidgetXmp->topLevelItem(posExif)->setIcon(0, *icon);
                    QColor *co = new QColor(227, 227, 227);
                    QBrush *bu = new QBrush(*co);
                    widget.treeWidgetXmp->topLevelItem(posExif)->setBackground(0, *bu);
                    widget.treeWidgetXmp->topLevelItem(posExif)->setBackground(1, *bu);
                    posExif++;
                } else {
                    treeItemChild = new QTreeWidgetItem(treeItem);
                    treeItemChild->setText(0, descricao);
                    treeItemChild->setText(1, value);
                }
            }
        }
    }
    catch (Exiv2::Error& e) {
        QString erroStatus;
        switch (e.code()) {
            case 2:
                erroStatus = QString::fromUtf8("Erro ao Remover Arquivo");
                break;
            case 9:
                erroStatus = QString::fromUtf8("Arquivo Não Existe");
                break;
            case 10:
                erroStatus = QString::fromUtf8("Arquivo Somente Leitura");
                break;
            case 11:
                erroStatus = QString("Arquivo Inválido");
                break;
        }
    }
}

void ExibeFoto::formEditMetadatas() {
    AddMetadata *addMetadata = new AddMetadata(this);
    addMetadata->showMaximized();
    QEventLoop *ev = new QEventLoop();
    connect(addMetadata, SIGNAL(fechaAddMetadata()), ev, SLOT(close()));
    ev->exec(QEventLoop::DialogExec);
    delete addMetadata;
}

void ExibeFoto::fechar() {
    emit fechaExibeFoto();
}

void ExibeFoto::alteraIconeExpanded(QTreeWidgetItem* item) {
    QIcon *icon;
    icon = new QIcon(":/IconesMenu/blue-document-open.png");
    item->setIcon(0, *icon);

}

void ExibeFoto::alteraIconeCollapsed(QTreeWidgetItem* item) {
    QIcon *icon;
    icon = new QIcon(":/IconesMenu/blue-folder-new.png");
    item->setIcon(0, *icon);
}