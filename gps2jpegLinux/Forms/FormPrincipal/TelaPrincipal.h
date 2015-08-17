/* 
 * File:   TelaPrincipal.h
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

#ifndef _TELAPRINCIPAL_H
#define	_TELAPRINCIPAL_H

#include "ui_TelaPrincipal.h"
#include "threadExif/ThreadLoadExifDatas.h"
#include "threadExif/ThreadRemoveExifDatas.h"
#include "threadExif/ThreadPositionImages.h"
#include "threadExif/ThreadRemoveImagesGeoref.h"
#include "threadExif/ThreadRemoveFileNoDate.h"

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QDateTime>
#include <QtWidgets/QMainWindow>
#include <QtCore/QTranslator>

class ReadFileGps;
class PeriodoTracklog;
class ManipulaExifFotos;
class QImage;
class QTranslator;

#ifndef QT_NO_CONCURRENT

QT_FORWARD_DECLARE_CLASS(QTableView)

class TelaPrincipal : public QMainWindow {
    Q_OBJECT
public:
    TelaPrincipal();
    virtual ~TelaPrincipal();

private:
    Ui::TelaPrincipal widget;
    PeriodoTracklog *gerenciaTrackLogs;
    QString caminhoArquivoFoto;
    QPixmap *imagemOriginal;
    ReadFileGps *leitorArquivosGps;
    QTranslator *translator;
    ThreadLoadExifDatas threadLoadExifDatas;
    ThreadRemoveExifDatas *threadRemoveExifDatas;
    ThreadPositionImages *threadPositionImages;
    ThreadRemoveImagesGeoref *threadRemoveImagesGeoref;
    ThreadRemoveFileNoDate *threadRemoveFileNoDate;

    void leListaArquivosDadosExif(const QStringList &listaArquivos);
    QDateTime converteHoraGmtParaLocal(QDateTime horaOriginal);
    QDateTime converteHoraLocalParaGmt(QDateTime horaOriginal);
    void configuraTelaPrincipal();

private slots:
    void atualizaFusoHorarioTrackLog();
    void pushButtonOpenLogGPS_Click();
    void pushButtonOpenJpeg_Click();
    void pushButtonPosicionarFotos_Click();
    void pushButtonOpenDirJpeg_Click();
    void pushButtonRemoverDadosExif_Click();
    void pushButtonLimparListaArquivos_Click();
    void pushButtonLimparListaArquivosImagens_Click();
    void pushButtonLimparListaArquivosGPS_Click();
    void pushButtonLimparArquivosGeoreferenciados_Click();
    void pushButtonLimparArquivosSemData();
    void pushButtonCorrigirHoraFotos_Click();
    void exibirAbout();

    void visitarForum();
    void verificarAtualizacoes();
    void informarBugs();
    void solicitarMelhorias();
    void visitarSiteDesenvolvedor();
    void visitarSiteProjeto();
    void fazerDoacaoAoDesenvolvedor();
    void toleranciaTempoAlterada();

    void openMenuTableWidgetJpeg();

public slots:
    void tableWidgetJpegExibirThumbnail(int row, int column);
    void removerMiniatura();
    void pushButtonExibirFoto();
    void traduzirIngles();
    void traduzirPortugues();
    void traduzirEspanhol();
};

#endif /* QT_NO_CONCURRENT */

#endif	/* _TELAPRINCIPAL_H */
