/* 
 * File:   ReadFileGpsTxt.h
 * Author: Adonai Silveira Canez
 *
 * Created on 21 de Agosto de 2009, 14:05
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

#ifndef _READFILEGPS_H
#define	_READFILEGPS_H

#include "DadosArquivoGps.h"

#include <QtCore/QVector>
#include <QtCore/QString>

class QDateTime;
class PeriodoTracklog;

class ReadFileGps {
public:
    ReadFileGps(PeriodoTracklog *gerenciaTrackLogs);
    virtual ~ReadFileGps();
    bool readFileGps(QString fileName, QDateTime &peridoInicial, QDateTime &peridoFinal, int &segmentosLog);
    void limpaListaArquivosLidos();
    QVector<DadosArquivoGps> getListaArquivosLidos();

private:
    PeriodoTracklog *controlaPeriodoTracklog;
    QVector<DadosArquivoGps> listaArquivosLido;

    bool readFileGpsTxt(QString fileName, QDateTime &peridoInicial, QDateTime &peridoFinal, int &segmentosLog);
    double fileTxtConverteCoordenadaGrausMinutosParaGraus(QString valorColuna);
    double fileTxtConverteCoordenadasGrausMinutosSegundosParaGraus(QString valorColuna);
    void fileTxtConverteData(QString valorColuna, int &dia, int &mes, int &ano);

    bool readFileGpsGpx(QString fileName, QDateTime &peridoInicial, QDateTime &peridoFinal, int &segmentosLog);
};

#endif	/* _READFILEGPS_H */

