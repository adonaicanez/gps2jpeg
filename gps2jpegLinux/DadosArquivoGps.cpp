/* 
 * File:   DadosArquivoGps.cpp
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

#include "DadosArquivoGps.h"

#include <QtCore/QString>

DadosArquivoGps::DadosArquivoGps() {
    totalDePontos = 0;
}

DadosArquivoGps::DadosArquivoGps(const DadosArquivoGps & other) {
    caminhoArquivo = other.caminhoArquivo;
    dataInicial = other.dataInicial;
    dataFinal = other.dataFinal;
    totalDePontos = other.totalDePontos;
}

DadosArquivoGps::DadosArquivoGps(QString caminhoArquivo, QDateTime dataInicial, QDateTime dataFinal, int totalDePontos) {
    this->caminhoArquivo = caminhoArquivo;
    this->dataInicial = dataInicial;
    this->dataFinal = dataFinal;
    this->totalDePontos = totalDePontos;
}

DadosArquivoGps::~DadosArquivoGps() {
}

DadosArquivoGps DadosArquivoGps::operator =(const DadosArquivoGps &other) {
    caminhoArquivo = other.caminhoArquivo;
    dataInicial = other.dataInicial;
    dataFinal = other.dataFinal;
    totalDePontos = other.totalDePontos;
    return *this;
}

bool DadosArquivoGps::operator ==(const DadosArquivoGps& other) const {
    return dataInicial == other.dataInicial && dataFinal == other.dataFinal && totalDePontos == other.totalDePontos;
}

QString DadosArquivoGps::getCaminhoArquivo() {
    return caminhoArquivo;
}

QDateTime DadosArquivoGps::getDataInicial() {
    return dataInicial;
}

QDateTime DadosArquivoGps::getDataFinal() {
    return dataFinal;
}

int DadosArquivoGps::getTotalDePontos() {
    return totalDePontos;
}

void DadosArquivoGps::setCaminhoArquivo(QString caminhoArquivo) {
    this->caminhoArquivo = caminhoArquivo;
}

void DadosArquivoGps::setDataFinal(QDateTime dataFinal) {
    this->dataFinal = dataFinal;
}

void DadosArquivoGps::setDataInicial(QDateTime dataInicial) {
    this->dataInicial = dataInicial;
}

void DadosArquivoGps::setTotalDePontos(int totalDePontos) {
    this->totalDePontos = totalDePontos;
}