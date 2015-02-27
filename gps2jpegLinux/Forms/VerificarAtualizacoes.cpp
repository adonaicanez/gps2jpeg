/*
 * File:   VerificarAtualizacoes.cpp
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

#include "VerificarAtualizacoes.h"

VerificarAtualizacoes::VerificarAtualizacoes(QWidget *parent) : QDialog(parent) {
    widget.setupUi(this);

    buttonBox = new QDialogButtonBox;
    progressDialog = new QProgressDialog(this);
    http = new QHttp(this);

    QString versaoInstal("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
            "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
            "p, li { white-space: pre-wrap; }"
            "</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:17pt; font-weight:400; font-style:normal;\">"
            "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
            "<span style=\" font-size:16pt; color:#0000ff;\">"
            );

    versaoInstal.append(QCoreApplication::applicationVersion());
    versaoInstal.append("</span></p></body></html>");
    widget.labelVersaoInstalada->setText(versaoInstal);

    connect(http, SIGNAL(requestFinished(int, bool)), this, SLOT(httpRequestFinished(int, bool)));
    connect(http, SIGNAL(dataReadProgress(int, int)), this, SLOT(updateDataReadProgress(int, int)));
    connect(http, SIGNAL(responseHeaderReceived(const QHttpResponseHeader &)), this, SLOT(readResponseHeader(const QHttpResponseHeader &)));
}

void VerificarAtualizacoes::downloadFile() {
    QUrl url("http://www.adonai.eti.br/gps2jpeg/gps2jpeg.txt");
    QFileInfo fileInfo(url.path());
    QString fileName = fileInfo.fileName();
    if (fileName.isEmpty())
        fileName = "index.html";

    if (QFile::exists(fileName)) {
        QFile::remove(fileName);
    }

    file = new QFile(fileName);
    if (!file->open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, QCoreApplication::applicationName() + " " + QCoreApplication::applicationVersion()
                , trUtf8("Não foi possível verificar atualizações"));
        delete file;
        file = 0;
        return;
    }

    QHttp::ConnectionMode mode = url.scheme().toLower() == "https" ? QHttp::ConnectionModeHttps : QHttp::ConnectionModeHttp;
    http->setHost(url.host(), mode, url.port() == -1 ? 0 : url.port());

    if (!url.userName().isEmpty())
        http->setUser(url.userName(), url.password());

    httpRequestAborted = false;
    QByteArray path = QUrl::toPercentEncoding(url.path(), "!$&'()*+,;=:@/");
    if (path.isEmpty())
        path = "/";
    httpGetId = http->get(path, file);

    progressDialog->setWindowTitle(QCoreApplication::applicationName() + " " + QCoreApplication::applicationVersion());
    progressDialog->setLabelText(trUtf8("Baixando."));
}

void VerificarAtualizacoes::httpRequestFinished(int requestId, bool error) {
    if (requestId != httpGetId)
        return;
    if (httpRequestAborted) {
        if (file) {
            file->close();
            file->remove();
            delete file;
            file = 0;
        }
        progressDialog->hide();
        return;
    }

    if (requestId != httpGetId)
        return;

    progressDialog->hide();
    file->close();

    if (error) {
        file->remove();
        QMessageBox::critical(this, QCoreApplication::applicationName() + " " + QCoreApplication::applicationVersion()
                , trUtf8("Não foi possível conectar ao servidor"));
    }


    lerArquivoAtualizacao();
}

void VerificarAtualizacoes::readResponseHeader(const QHttpResponseHeader &responseHeader) {
    switch (responseHeader.statusCode()) {
        case 200: // Ok
        case 301: // Moved Permanently
        case 302: // Found
        case 303: // See Other
        case 307: // Temporary Redirect
            // these are not error conditions
            break;

        default:
            QMessageBox::information(this, QCoreApplication::applicationName() + " " + QCoreApplication::applicationVersion()
                    , trUtf8("Falha no Download"));
            httpRequestAborted = true;
            progressDialog->hide();
            http->abort();
    }
}

void VerificarAtualizacoes::updateDataReadProgress(int bytesRead, int totalBytes) {
    if (httpRequestAborted)
        return;

    progressDialog->setMaximum(totalBytes);
    progressDialog->setValue(bytesRead);
}

void VerificarAtualizacoes::lerArquivoAtualizacao() {
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QString line = file->readLine();
    QString mensagem("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
            "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
            "p, li { white-space: pre-wrap; }"
            "</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:12pt; font-weight:400; font-style:normal;\">"
            "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
            "<span style=\" font-size:16pt;"
            );

    if (line.toDouble() == QCoreApplication::applicationVersion().toDouble()) {
        mensagem.append("color:#0000ff;\">");
        widget.labelLinkDownload->setText(trUtf8("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
                "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
                "p, li { white-space: pre-wrap; }"
                "</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">"
                "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
                "<span style=\" font-size:12pt; color:#0000ff;\">A sua versão já está atualizada.</span></p></body></html>"
                ));
    }
    if (line.toDouble() > QCoreApplication::applicationVersion().toDouble()) {
        mensagem.append("color:#ff0000;\">");
        widget.labelLinkDownload->setText(trUtf8("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">"
                "<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">"
                "p, li { white-space: pre-wrap; }"
                "</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">"
                "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">"
                "<span style=\" font-size:10pt; color:#ff0000;\">A sua versão está desatualizada. <br> Visite o site https://sourceforge.net/projects/gps2jpeg e baixe a última versão.</span></p></body></html>"
                ));
    }
    mensagem.append(line);
    mensagem.append("< / span>< / p>< / body>< / html > ");

    widget.labelVersaoAtual->setText(mensagem);

    file->close();
    file->remove();
    delete file;
    file = 0;
}
