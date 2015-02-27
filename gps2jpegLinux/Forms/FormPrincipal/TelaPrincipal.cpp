/*
 * File:   TelaPrincipal.cpp
 * Author: Adonai Silveira Canez
 *
 * Created on 19 de Agosto de 2009, 10:05
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

#include "TelaPrincipal.h"
#include "ReadFileGps.h"
#include "PeriodoTracklog.h"
#include "ExibeFoto.h"
#include "TrataEventoLabelThumbnail.h"
#include "VerificarAtualizacoes.h"
#include "threadExif/ThreadRemoveImagesGeoref.h"

#include <QtCore/QUrl>
#include <QtCore/QDirIterator>
#include <QtCore/QTranslator>
#include <QtCore/QSettings>

#include <QtGui/QTableWidgetItem>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <QtGui/QDesktopServices>

#include <QtCore/QEventLoop>

#include <iostream>

TelaPrincipal::TelaPrincipal() {
    widget.setupUi(this);
    configuraTelaPrincipal();
    translator = NULL;
    imagemOriginal = NULL;

    threadPositionImages = new ThreadPositionImages(this);
    threadRemoveExifDatas = new ThreadRemoveExifDatas(this);
    threadRemoveImagesGeoref = new ThreadRemoveImagesGeoref(this);
    threadRemoveFileNoDate = new ThreadRemoveFileNoDate(this);
}

TelaPrincipal::~TelaPrincipal() {
    delete leitorArquivosGps;
}

void TelaPrincipal::configuraTelaPrincipal() {
    QSettings settings;
    QString fusoHorario;
    fusoHorario.operator=(settings.value("fusoHorario").toString());
    widget.lineEditFusoHorario->setText(fusoHorario);

    QString horarioVerao;
    horarioVerao.operator=(settings.value("horarioVerao").toString());
    if (horarioVerao.operator ==("true")) {
        widget.checkBoxHorarioDeVerao->setChecked(true);
    }

    QString toleranciaTempo;
    toleranciaTempo.operator=(settings.value("toleranciaTempo", "NO").toString());
    widget.lineEditToleranciaTempo->setText(toleranciaTempo);

    widget.tableWidgetJpeg->setColumnCount(8);
    widget.tableWidgetJpeg->setRowCount(0);
    QTableWidgetItem *item;
    item = new QTableWidgetItem();
    item->setText(trUtf8("Nome do Arquivo"));
    widget.tableWidgetJpeg->setHorizontalHeaderItem(0, item);
    item = new QTableWidgetItem();
    item->setText(trUtf8("Data da Foto"));
    widget.tableWidgetJpeg->setHorizontalHeaderItem(1, item);
    item = new QTableWidgetItem();
    item->setText(trUtf8("Data Corrigida"));
    widget.tableWidgetJpeg->setHorizontalHeaderItem(2, item);
    item = new QTableWidgetItem();
    item->setText(trUtf8("Latitude"));
    widget.tableWidgetJpeg->setHorizontalHeaderItem(3, item);
    item = new QTableWidgetItem();
    item->setText(trUtf8("Longitude"));
    widget.tableWidgetJpeg->setHorizontalHeaderItem(4, item);
    item = new QTableWidgetItem();
    item->setText(trUtf8("Altitude"));
    widget.tableWidgetJpeg->setHorizontalHeaderItem(5, item);
    item = new QTableWidgetItem();
    item->setText(trUtf8("Status Exif"));
    widget.tableWidgetJpeg->setHorizontalHeaderItem(6, item);
    item = new QTableWidgetItem();
    item->setText(trUtf8("Caminho"));
    widget.tableWidgetJpeg->setHorizontalHeaderItem(7, item);

    widget.tableWidgetJpeg->setColumnWidth(0, 120);
    widget.tableWidgetJpeg->setColumnWidth(1, 140);
    widget.tableWidgetJpeg->setColumnWidth(2, 140);
    widget.tableWidgetJpeg->setColumnWidth(3, 120);
    widget.tableWidgetJpeg->setColumnWidth(4, 120);
    widget.tableWidgetJpeg->setColumnWidth(5, 60);
    widget.tableWidgetJpeg->setColumnWidth(6, 150);
    widget.tableWidgetJpeg->setColumnWidth(7, 500);

    // Tabela que exibe os arquivos
    widget.tableWidgetLogGps->setColumnCount(4);
    widget.tableWidgetLogGps->setRowCount(0);
    item = new QTableWidgetItem();
    item->setText(trUtf8("Nome do Arquivo"));
    widget.tableWidgetLogGps->setHorizontalHeaderItem(0, item);
    item = new QTableWidgetItem();
    item->setText(trUtf8("Início do Tracklog"));
    widget.tableWidgetLogGps->setHorizontalHeaderItem(1, item);
    item = new QTableWidgetItem();
    item->setText(trUtf8("Final do Tracklog"));
    widget.tableWidgetLogGps->setHorizontalHeaderItem(2, item);
    item = new QTableWidgetItem();
    item->setText(trUtf8("Segmentos no Tracklog"));
    widget.tableWidgetLogGps->setHorizontalHeaderItem(3, item);

    widget.tableWidgetLogGps->setColumnWidth(0, 300);
    widget.tableWidgetLogGps->setColumnWidth(1, 150);
    widget.tableWidgetLogGps->setColumnWidth(2, 150);
    widget.tableWidgetLogGps->setColumnWidth(3, 130);

    gerenciaTrackLogs = new PeriodoTracklog();
    widget.checkBoxNaoAlteraDataArquivo->setVisible(false);
    widget.checkBoxInterpolarPontos->setVisible(false);
    widget.line2->setVisible(false);
    widget.progressBar->setVisible(false);

    leitorArquivosGps = new ReadFileGps(gerenciaTrackLogs);
    QRegExp rx("[-+][0-1][0-9]:[0-5][0-9]");
    QValidator *validator = new QRegExpValidator(rx, this);
    widget.lineEditFusoHorario->setValidator(validator);

    this->setWindowTitle(QApplication::applicationName() + " " + QApplication::applicationVersion());


    connect(widget.tableWidgetJpeg, SIGNAL(exibirFoto()), this, SLOT(pushButtonExibirFoto()));
    connect(widget.tableWidgetJpeg, SIGNAL(imagemRemovidaDaLista()), this, SLOT(removerMiniatura()));
    connect(widget.labelThumbnail, SIGNAL(duploClick()), this, SLOT(pushButtonExibirFoto()));
}

void TelaPrincipal::pushButtonOpenLogGPS_Click() {
    QSettings settings;

    QDateTime dataInicial, dataFinal;
    int totalSegmentos, tamanho, pos, linha;
    QString path;
    QTableWidgetItem *item;

    QStringList arquivosGPS = QFileDialog::getOpenFileNames(this, trUtf8("Selecione os arquivos"), settings.value("pathFileTxt").toString(),
            trUtf8("Arquivo Texto do TrackMaker (*.txt);;Arquivos GPS Exchange (*.gpx)"));
    if (arquivosGPS.size() > 0) {
        QString path;
        path = arquivosGPS.at(0).mid(0, arquivosGPS.at(0).lastIndexOf('/'));
        settings.setValue("pathFileTxt", QVariant(path));
    }

    QStringList::Iterator it = arquivosGPS.begin();

    while (it != arquivosGPS.end()) {
        path = *it;
        if (!leitorArquivosGps->readFileGps(path, dataInicial, dataFinal, totalSegmentos)) {
            QMessageBox::critical(this, QCoreApplication::applicationName() + " " + QCoreApplication::applicationVersion()
                    , trUtf8("O Arquivo Selecionado é Inválido"), QMessageBox::Ok);
            return;
        }

        widget.tableWidgetLogGps->setRowCount(widget.tableWidgetLogGps->rowCount() + 1);
        linha = widget.tableWidgetLogGps->rowCount();

        item = new QTableWidgetItem();
        pos = path.lastIndexOf("/");
        tamanho = path.size();
        item->setText(path.right(tamanho - pos - 1));
        widget.tableWidgetLogGps->setItem(linha - 1, 0, item);

        item = new QTableWidgetItem();
        QDateTime dataInicialCorrigida = converteHoraGmtParaLocal(dataInicial);
        item->setText(dataInicialCorrigida.toString("dd/MM/yyyy hh:mm:ss"));
        widget.tableWidgetLogGps->setItem(linha - 1, 1, item);

        item = new QTableWidgetItem();
        QDateTime dataFinalCorrigida = converteHoraGmtParaLocal(dataFinal);
        item->setText(dataFinalCorrigida.toString("dd/MM/yyyy hh:mm:ss"));
        widget.tableWidgetLogGps->setItem(linha - 1, 2, item);

        item = new QTableWidgetItem();
        item->setText(QString::number(totalSegmentos));
        widget.tableWidgetLogGps->setItem(linha - 1, 3, item);
        it++;
    }
}

void TelaPrincipal::pushButtonOpenJpeg_Click() {
    QSettings settings;
#ifdef Q_WS_WIN
    QStringList arquivosImagens = QFileDialog::getOpenFileNames(this, trUtf8("Selecione os arquivos"), settings.value("pathFileJpeg").toString(),
            "Imagens jpeg (*.jpeg *.jpg);;Imagens png (*.png);;Imagens tiff (*.tiff *.tif);;Imagens pgf(*.pgf);;Imagens psd(*.psd)");
#endif
#ifdef Q_WS_X11
    QStringList arquivosImagens = QFileDialog::getOpenFileNames(this, trUtf8("Selecione os arquivos"), settings.value("pathFileJpeg").toString(), trUtf8(
            "Imagens JPEG(*.JPEG *.jpeg *.JPG *.jpg);;Imagens png (*.PNG *.png);;Imagens tiff (*.TIFF *.tiff);;Imagens pgf(*.pgf *.PGF);;Imagens psd(*.psd *.PSD)"));
#endif
    if (arquivosImagens.size() > 0) {
        QString path;
        path = arquivosImagens.at(0).mid(0, arquivosImagens.at(0).lastIndexOf('/'));
        settings.setValue("pathFileJpeg", QVariant(path));
    }
    leListaArquivosDadosExif(arquivosImagens);
}

void TelaPrincipal::pushButtonPosicionarFotos_Click() {
    if (widget.tableWidgetJpeg->rowCount() != 0 && widget.tableWidgetLogGps->rowCount() != 0) {
        if (widget.tableWidgetJpeg->rowCount() != 0) {
            if (widget.tableWidgetLogGps->rowCount() != 0) {
                threadPositionImages->setThreadPositionImages(gerenciaTrackLogs, widget.tableWidgetJpeg, widget.progressBar,
                        widget.lineEditToleranciaTempo->text().toInt(), widget.lineEditFusoHorario, widget.checkBoxHorarioDeVerao);
                threadPositionImages->start(QThread::LowestPriority);

            } else {
                QMessageBox::critical(this, QCoreApplication::applicationName() + " " + QCoreApplication::applicationVersion()
                        , trUtf8("Você precisa selecionar um arquivo de tracklogs"), QMessageBox::Ok);
            }
        } else {
            QMessageBox::critical(this, QCoreApplication::applicationName() + " " + QCoreApplication::applicationVersion()
                    , trUtf8("Você precisa selecionar as fotos para serem posicionadas"), QMessageBox::Ok);
        }
    } else {
        QMessageBox::critical(this, QCoreApplication::applicationName() + " " + QCoreApplication::applicationVersion()
                , trUtf8("Você precisa selecionar as fotos e o tracklog para realizar o posicionamento"), QMessageBox::Ok);
    }
}

void TelaPrincipal::pushButtonOpenDirJpeg_Click() {
    QSettings settings;
    QString diretorio = QFileDialog::getExistingDirectory(this, trUtf8("Selecione o diretório que contêm as imagens que serão posicionadas"),
            settings.value("pathFileJpeg").toString(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!diretorio.isNull()) {
        settings.setValue("pathFileJpeg", QVariant(diretorio));
    }

    QStringList listaArquivos;
    QString arquivo;
    QDirIterator it(diretorio, widget.checkBoxInclSubdir->isChecked() ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags);
    while (it.hasNext()) {
        int pos1;
        arquivo = it.next();
        pos1 = arquivo.lastIndexOf('.');
        if ((pos1 + 1) != arquivo.size()) {
            QString extensao;
            extensao = QString(arquivo.mid(pos1 + 1, arquivo.size() - pos1)).toLower();
            if (extensao.operator ==("jpg") || extensao.operator ==("jpeg") || extensao.operator ==("tiff") || extensao.operator ==("tif")
                    || extensao.operator ==("png")) {
                listaArquivos.push_back(arquivo);
            }
        }
    }
    leListaArquivosDadosExif(listaArquivos);
}

void TelaPrincipal::pushButtonRemoverDadosExif_Click() {
    threadRemoveExifDatas->setTableWidget(widget.tableWidgetJpeg, widget.progressBar);
    threadRemoveExifDatas->start(QThread::LowestPriority);
}

void TelaPrincipal::pushButtonCorrigirHoraFotos_Click() {
    int totalFotos;
    QTableWidgetItem *item;

    totalFotos = widget.tableWidgetJpeg->rowCount();

    if (widget.tableWidgetJpeg->rowCount() != 0) {
        for (int i = 0; i < totalFotos; i++) {
            if (widget.tableWidgetJpeg->item(i, 2) != NULL) {
                item = widget.tableWidgetJpeg->item(i, 1);
                int segundosCorrecao = widget.lineEditCorrecaoTempoFotos->text().toInt();
                QDateTime dataHoraCorrigida = QDateTime::fromString(item->text(), "dd/MM/yyyy hh:mm:ss").addSecs(segundosCorrecao);
                item = new QTableWidgetItem();
                item->setText(dataHoraCorrigida.toString("dd/MM/yyyy hh:mm:ss"));
                widget.tableWidgetJpeg->setItem(i, 2, item);
                widget.tableWidgetJpeg->selectRow(i);
                widget.tableWidgetJpeg->repaint();
            }
        }
        QMessageBox::information(this, QCoreApplication::applicationName() + " " + QCoreApplication::applicationVersion()
                , trUtf8("Corrigido o horário das fotos"), QMessageBox::Ok);
    } else {
        QMessageBox::critical(this, QCoreApplication::applicationName() + " " + QCoreApplication::applicationVersion()
                , trUtf8("Você precisa selecionar as fotos"), QMessageBox::Ok);
    }
}

void TelaPrincipal::leListaArquivosDadosExif(const QStringList &listaArquivos) {
    QStringList listaCorrigida(listaArquivos);
    threadLoadExifDatas.setListImagesFiles(listaCorrigida.replaceInStrings("\\", "/"));
    threadLoadExifDatas.setTableWidget(widget.tableWidgetJpeg, widget.lineEditCorrecaoTempoFotos, widget.progressBar);
    threadLoadExifDatas.start(QThread::LowestPriority);
}

void TelaPrincipal::pushButtonLimparListaArquivosImagens_Click() {
    for (int i = 0; i < widget.tableWidgetJpeg->rowCount(); i++) {
        for (int j = 0; j < widget.tableWidgetJpeg->columnCount(); j++) {
            delete widget.tableWidgetJpeg->item(i, j);
        }
    }
    widget.tableWidgetJpeg->clearContents();
    widget.tableWidgetJpeg->setRowCount(0);
    widget.labelThumbnail->setPixmap(0);
    delete imagemOriginal;
    imagemOriginal = NULL;
}

void TelaPrincipal::pushButtonLimparArquivosGeoreferenciados_Click() {
    threadRemoveImagesGeoref->setTableWidget(widget.tableWidgetJpeg, widget.progressBar);
    threadRemoveImagesGeoref->start(QThread::LowestPriority);
}

void TelaPrincipal::pushButtonLimparArquivosSemData() {
    threadRemoveFileNoDate->setTableWidget(widget.tableWidgetJpeg, widget.progressBar);
    threadRemoveFileNoDate->start(QThread::LowestPriority);
}

void TelaPrincipal::pushButtonLimparListaArquivosGPS_Click() {

    for (int i = 0; i < widget.tableWidgetLogGps->rowCount(); i++) {
        for (int j = 0; j < widget.tableWidgetLogGps->columnCount(); j++) {
            delete widget.tableWidgetLogGps->item(i, j);
        }
    }
    widget.tableWidgetLogGps->clearContents();
    widget.tableWidgetLogGps->setRowCount(0);
    gerenciaTrackLogs->LimpaListaDeTrackLogs();
    leitorArquivosGps->limpaListaArquivosLidos();
}

void TelaPrincipal::pushButtonLimparListaArquivos_Click() {
    pushButtonLimparListaArquivosImagens_Click();
    pushButtonLimparListaArquivosGPS_Click();
}

void TelaPrincipal::exibirAbout() {
    QString msgAbout;

    msgAbout = trUtf8("Versão: ");
    msgAbout += QApplication::applicationVersion();
    msgAbout += "\n";
    msgAbout += trUtf8("Este software foi desenvolvido livre para uso pessoal.\n"
            "Site do desenvolvedor: http://www.adonai.eti.br \n"
            "Para informar bugs acesse o site do desenvolvedor ou mande um e-mail para adonai@adonai.eti.br\n\n"
            "Este software foi desenvolvido usando a biblioteca exiv2 http://www.exiv2.org para manipulação de dados Exif\n"
            "e para desenvolvimento da interface gráfica foi usado a biblioteca Qt4 http://qt.nokia.com");

    QMessageBox::about(this, trUtf8("Sobre"), msgAbout);
}

void TelaPrincipal::tableWidgetJpegExibirThumbnail(int row, int /*column*/) {
    QPixmap imagemRedimensionada;
    QSize tamanhoMiniatura(175, 125);
    caminhoArquivoFoto = widget.tableWidgetJpeg->item(row, 7)->text();
    if (imagemOriginal != NULL) {
        delete imagemOriginal;
    }
    imagemOriginal = new QPixmap();

    if (imagemOriginal->load(caminhoArquivoFoto)) {
        imagemRedimensionada = imagemOriginal->scaledToHeight(tamanhoMiniatura.height());
        widget.labelThumbnail->setPixmap(imagemRedimensionada);
    } else {
        imagemOriginal = NULL;
        widget.labelThumbnail->setPixmap(NULL);
    }
}

void TelaPrincipal::pushButtonExibirFoto() {
    if (imagemOriginal != NULL) {
        ExibeFoto *exibeFoto;
        exibeFoto = new ExibeFoto(imagemOriginal, caminhoArquivoFoto, this);
        exibeFoto->showMaximized();

        QEventLoop *ev = new QEventLoop();
        connect(exibeFoto, SIGNAL(fechaExibeFoto()), ev, SLOT(quit()));
        ev->exec(QEventLoop::DialogExec);
        delete exibeFoto;
        delete ev;
    }
}

QDateTime TelaPrincipal::converteHoraGmtParaLocal(QDateTime horaOriginal) {
    QString fusoHorario = widget.lineEditFusoHorario->text();
    int hora, min, segundosCorrecao;

    hora = atoi(fusoHorario.toStdString().substr(0, fusoHorario.indexOf(":")).c_str());
    segundosCorrecao = hora * 3600;
    min = atoi(fusoHorario.toStdString().substr(fusoHorario.indexOf(":") + 1, fusoHorario.size()).c_str());
    if (hora < 0) {
        segundosCorrecao -= min * 60;
    } else {
        segundosCorrecao += min * 60;
    }
    if (widget.checkBoxHorarioDeVerao->isChecked()) {
        segundosCorrecao += 3600;
    }

    QDateTime dataHoraCorrigido(horaOriginal.addSecs(segundosCorrecao));
    return dataHoraCorrigido;
}

QDateTime TelaPrincipal::converteHoraLocalParaGmt(QDateTime horaOriginal) {
    QString fusoHorario = widget.lineEditFusoHorario->text();
    int hora, min, segundosCorrecao;

    hora = atoi(fusoHorario.toStdString().substr(0, fusoHorario.indexOf(":")).c_str());
    segundosCorrecao = hora * 3600;
    min = atoi(fusoHorario.toStdString().substr(fusoHorario.indexOf(":") + 1, fusoHorario.size()).c_str());
    if (hora < 0) {
        segundosCorrecao -= min * 60;
    } else {
        segundosCorrecao += min * 60;
    }

    if (widget.checkBoxHorarioDeVerao->isChecked()) {
        segundosCorrecao += 3600;
    }
    QDateTime dataHoraCorrigido(horaOriginal.addSecs(-segundosCorrecao));
    return dataHoraCorrigido;
}

void TelaPrincipal::atualizaFusoHorarioTrackLog() {
    QString dataInicialS, dataFinalS;
    QDateTime dataInicialD, dataFinalD;
    QVector<DadosArquivoGps> arquivosLidos;

    QSettings settings;
    settings.setValue("horarioVerao", widget.checkBoxHorarioDeVerao->isChecked() ? "true" : "false");
    settings.setValue("fusoHorario", widget.lineEditFusoHorario->text());

    arquivosLidos = leitorArquivosGps->getListaArquivosLidos();

    for (int i = 0; i < arquivosLidos.size(); i++) {
        DadosArquivoGps arquivoLido;
        arquivoLido = arquivosLidos.at(i);
        dataInicialD = converteHoraGmtParaLocal(arquivoLido.getDataInicial());
        dataFinalD = converteHoraGmtParaLocal(arquivoLido.getDataFinal());
        dataInicialS = dataInicialD.toString("dd/MM/yyyy hh:mm:ss");
        dataFinalS = dataFinalD.toString("dd/MM/yyyy hh:mm:ss");
        widget.tableWidgetLogGps->item(i, 1)->setText(dataInicialS);
        widget.tableWidgetLogGps->item(i, 2)->setText(dataFinalS);
    }
}

void TelaPrincipal::verificarAtualizacoes() {
    VerificarAtualizacoes *formVerificaAtualizacoes = new VerificarAtualizacoes(this);
    formVerificaAtualizacoes->show();
    formVerificaAtualizacoes->exec();
}

void TelaPrincipal::visitarForum() {
    QDesktopServices::openUrl(QUrl("https://sourceforge.net/projects/gps2jpeg/forums"));
}

void TelaPrincipal::traduzirIngles() {
    QSettings settings;
    QString ling(settings.value("linguagem").toString());

    if (ling.operator !=("en_US")) {
        if (translator != NULL) {
            QApplication::removeTranslator(translator);
            delete translator;
        }
        translator = new QTranslator();
        translator->load(":/linguagem_en_US");
        QApplication::installTranslator(translator);
        widget.retranslateUi(this);
        widget.setupUi(this);
        configuraTelaPrincipal();
        settings.setValue("linguagem", "en_US");
    }
    widget.actionTraduzirEnglish->setChecked(true);
}

void TelaPrincipal::traduzirPortugues() {
    QSettings settings;
    QString ling(settings.value("linguagem").toString());

    if (ling.operator !=("pt_BR")) {
        if (translator != NULL) {
            QApplication::removeTranslator(translator);
            delete translator;
            translator = NULL;
        }
        widget.retranslateUi(this);
        widget.setupUi(this);
        configuraTelaPrincipal();
        settings.setValue("linguagem", "pt_BR");
    }
    widget.actionTraduzirPortugues->setChecked(true);
}

void TelaPrincipal::traduzirEspanhol() {
    QSettings settings;
    QString ling(settings.value("linguagem").toString());

    if (ling.operator !=("es")) {
        if (translator != NULL) {
            QApplication::removeTranslator(translator);
            delete translator;
        }
        translator = new QTranslator();
        translator->load(":/linguagem_es");
        QApplication::installTranslator(translator);
        widget.retranslateUi(this);
        widget.setupUi(this);
        configuraTelaPrincipal();
        settings.setValue("linguagem", "es");
    }
    widget.actionTraduzirSpanish->setChecked(true);
}

void TelaPrincipal::informarBugs() {
    QDesktopServices::openUrl(QUrl("http://sourceforge.net/tracker/?group_id=302607&atid=1275807"));
}

void TelaPrincipal::solicitarMelhorias() {
    QDesktopServices::openUrl(QUrl("http://sourceforge.net/tracker/?group_id=302607&atid=1275810"));
}

void TelaPrincipal::visitarSiteDesenvolvedor() {
    QDesktopServices::openUrl(QUrl("http://www.adonai.eti.br"));
}

void TelaPrincipal::visitarSiteProjeto() {
    QDesktopServices::openUrl(QUrl("http://sourceforge.net/projects/gps2jpeg/"));
}

void TelaPrincipal::fazerDoacaoAoDesenvolvedor() {
    QDesktopServices::openUrl(QUrl("http://sourceforge.net/donate/index.php?group_id=302607"));
}

void TelaPrincipal::toleranciaTempoAlterada() {
    QSettings settings;
    settings.setValue("toleranciaTempo", widget.lineEditToleranciaTempo->text());
}

void TelaPrincipal::openMenuTableWidgetJpeg() {

}

void TelaPrincipal::removerMiniatura() {
    widget.labelThumbnail->setPixmap(NULL);
}