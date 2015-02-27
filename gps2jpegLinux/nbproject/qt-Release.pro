# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/MinGW_4.9.1-Windows
TARGET = gps2jpegLinux
VERSION = 3.3
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui network
SOURCES += DadosArquivoGps.cpp Forms/AddMetadata/AddMetadata.cpp Forms/ExibeFoto.cpp Forms/ExibeFoto/GraphicsScene.cpp Forms/ExibeFoto/GraphicsView.cpp Forms/FormPrincipal/TelaPrincipal.cpp Forms/FormPrincipal/TrataEventoLabelPaypal.cpp Forms/FormPrincipal/TrataEventoLabelThumbnail.cpp Forms/FormPrincipal/TrataEventoTableWidgetJpeg.cpp Forms/VerificarAtualizacoes.cpp GpsPosition.cpp ManipulaExifFotos.cpp PeriodoAno.cpp PeriodoDia.cpp PeriodoMes.cpp PeriodoTracklog.cpp ReadFileGps.cpp main.cpp threadExif/ThreadLoadExifDatas.cpp threadExif/ThreadPositionImages.cpp threadExif/ThreadRemoveExifDatas.cpp threadExif/ThreadRemoveFileNoDate.cpp threadExif/ThreadRemoveImagesGeoref.cpp
HEADERS += DadosArquivoGps.h Forms/AddMetadata/AddMetadata.h Forms/ExibeFoto.h Forms/ExibeFoto/GraphicsScene.h Forms/ExibeFoto/GraphicsView.h Forms/FormPrincipal/TelaPrincipal.h Forms/FormPrincipal/TrataEventoLabelPaypal.h Forms/FormPrincipal/TrataEventoTableWidgetJpeg.h Forms/TrataEventoLabelThumbnail.h Forms/VerificarAtualizacoes.h GpsPosition.h ManipulaExifFotos.h PeriodoAno.h PeriodoDia.h PeriodoMes.h PeriodoTracklog.h ReadFileGps.h threadExif/ThreadLoadExifDatas.h threadExif/ThreadPositionImages.h threadExif/ThreadRemoveExifDatas.h threadExif/ThreadRemoveFileNoDate.h
FORMS += Forms/AddMetadata/AddMetadata.ui Forms/ExibeFoto.ui Forms/FormPrincipal/TelaPrincipal.ui Forms/VerificarAtualizacoes.ui
RESOURCES += resources/resourcesIcon.qrc translations/translations.qrc
TRANSLATIONS += translations/linguagem_en_US.ts translations/linguagem_es.ts
OBJECTS_DIR = build/Release/MinGW_4.9.1-Windows
MOC_DIR = ./temp
RCC_DIR = ./temp
UI_DIR = ./temp
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += temp Forms . 
LIBS += -lexiv2  
TRANSLATIONS = translations/linguagem_en.ts
CODECFORSRC = UTF-8
