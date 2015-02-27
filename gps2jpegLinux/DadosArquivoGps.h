/* 
 * File:   DadosArquivoGps.h
 * Author: Adonai Silveira Canez
 *
 * Created on 9 de Dezembro de 2009, 00:15
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

#ifndef _DADOSARQUIVOGPS_H
#define	_DADOSARQUIVOGPS_H

#include <QtCore/QDateTime>

class QString;

class DadosArquivoGps {
public:
    DadosArquivoGps();
    DadosArquivoGps(const DadosArquivoGps &other);
    DadosArquivoGps(QString caminhoArquivo, QDateTime dataInicial, QDateTime dataFinal, int totalDePontos);
    ~DadosArquivoGps();
    DadosArquivoGps operator =(const DadosArquivoGps &other);
    bool operator ==(const DadosArquivoGps &other) const;

    QString getCaminhoArquivo();
    QDateTime getDataInicial();
    QDateTime getDataFinal();
    int getTotalDePontos();

    void setCaminhoArquivo(QString caminhoArquivo);
    void setDataInicial(QDateTime dataInicial);
    void setDataFinal(QDateTime dataFinal);
    void setTotalDePontos(int totalDePontos);
private:
    QString caminhoArquivo;
    QDateTime dataInicial, dataFinal;
    int totalDePontos;
};

#endif	/* _DADOSARQUIVOGPS_H */

