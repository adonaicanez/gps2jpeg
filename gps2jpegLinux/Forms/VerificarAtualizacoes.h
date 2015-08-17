/* 
 * File:   VerificarAtualizacoes.h
 * Author: Adonai Silveira Canez
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

#ifndef VERIFICARATUALIZACOES_H
#define VERIFICARATUALIZACOES_H

#include <QtCore/QUrl>
#include <QtCore/QFileInfo>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QProgressDialog>
#include <QtWidgets/QMessageBox>
//#include <QtNetwork/QHttp>
#include <QtNetwork/QNetworkAccessManager>

#include "ui_VerificarAtualizacoes.h"

class VerificarAtualizacoes : public QDialog {
    Q_OBJECT

public:
    VerificarAtualizacoes(QWidget *parent = 0);

private slots:
    void downloadFile();
 //   void httpRequestFinished(int requestId, bool error);
//    void readResponseHeader(const QHttpResponseHeader &responseHeader);
    void updateDataReadProgress(int bytesRead, int totalBytes);
    
private:
    Ui::VerificarAtualizacoes widget;
    QProgressDialog *progressDialog;
    QDialogButtonBox *buttonBox;
 //   QHttp *http;
    QFile *file;
    int httpGetId;
    bool httpRequestAborted;
    void lerArquivoAtualizacao();
};

#endif
