/* 
 * File:   main.cpp
 * Author: Adonai Silveira Canez
 *
 * Created on 8 de Agosto de 2009, 20:31
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

#include <QtGui/QApplication>
#include <QtCore/QTranslator>
#include <QtCore/QCoreApplication>
#include <QtCore/QSettings>
#include <QtGui/QMacStyle>
#include <QtGui/QMotifStyle>
#include <QtGui/QPlastiqueStyle>
#include <QtGui/QCleanlooksStyle>
#include <QtGui/QWindowsXPStyle>


#include "Forms/FormPrincipal/TelaPrincipal.h"
#include "DadosArquivoGps.h"

int main(int argc, char** argv) {
    Q_INIT_RESOURCE(resourcesIcon);
    Q_INIT_RESOURCE(translations);

    QApplication app(argc, argv);
  //  QApplication::setStyle(new QWindowsXPStyle);

    QApplication::setOrganizationName("Adonai Silveira Canez");
    QApplication::setOrganizationDomain("http://www.adonai.eti.br");
    QApplication::setApplicationName("gps2jpeg");
    QApplication::setApplicationVersion("4.1");

    QSettings settings;

    QString pathFileTxt;
    pathFileTxt.operator =(settings.value("pathFileTxt", "NO").toString());
    if (pathFileTxt.operator ==("NO")) {
        settings.setValue("pathFileTxt", "/");
    }

    QString pathFileJpeg;
    pathFileJpeg.operator =(settings.value("pathFileJpeg", "NO").toString());
    if (pathFileJpeg.operator ==("NO")) {
        settings.setValue("pathFileJpeg", "/");
    }

    QString fusoHorario;
    fusoHorario.operator=(settings.value("fusoHorario", "NO").toString());
    if (fusoHorario.operator==("NO")) {
        settings.setValue("fusoHorario", "-03:00");
    }

    QString horarioVerao;
    horarioVerao.operator=(settings.value("horarioVerao", "NO").toString());
    if (horarioVerao.operator ==("NO")) {
        settings.setValue("horarioVerao", "false");
    }

    QString toleranciaTempo;
    toleranciaTempo.operator=(settings.value("toleranciaTempo", "NO").toString());
    if (toleranciaTempo.operator ==("NO")) {
        settings.setValue("toleranciaTempo", "45");
    }

    TelaPrincipal tp;
    QString linguagem;
    linguagem.operator =(settings.value("linguagem", "NO").toString());
    if (linguagem.operator ==("NO") || linguagem.operator ==("pt_BR")) {
        settings.setValue("linguagem", "NO");
        tp.traduzirPortugues();
    } else {
        if (linguagem.operator ==("en_US")) {
            settings.setValue("linguagem", "NO");
            tp.traduzirIngles();
        }
        if (linguagem.operator ==("es")) {
            settings.setValue("linguagem", "NO");
            tp.traduzirEspanhol();
        }
    }
    tp.showMaximized();
    return app.exec();
}
