# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/GNU-Linux-x86
TARGET = gps2jpegLinux
VERSION = 5.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui widgets network
SOURCES += DadosArquivoGps.cpp Forms/ExibeFoto.cpp Forms/ExibeFoto/GraphicsScene.cpp Forms/ExibeFoto/GraphicsView.cpp Forms/FormPrincipal/TelaPrincipal.cpp Forms/FormPrincipal/TrataEventoLabelPaypal.cpp Forms/FormPrincipal/TrataEventoLabelThumbnail.cpp Forms/FormPrincipal/TrataEventoTableWidgetJpeg.cpp Forms/VerificarAtualizacoes.cpp GpsPosition.cpp ManipulaExifFotos.cpp PeriodoAno.cpp PeriodoDia.cpp PeriodoMes.cpp PeriodoTracklog.cpp ReadFileGps.cpp main.cpp threadExif/ThreadLoadExifDatas.cpp threadExif/ThreadPositionImages.cpp threadExif/ThreadRemoveExifDatas.cpp threadExif/ThreadRemoveFileNoDate.cpp threadExif/ThreadRemoveImagesGeoref.cpp
HEADERS += DadosArquivoGps.h Forms/ExibeFoto.h Forms/ExibeFoto/GraphicsScene.h Forms/ExibeFoto/GraphicsView.h Forms/FormPrincipal/TelaPrincipal.h Forms/FormPrincipal/TrataEventoLabelPaypal.h Forms/FormPrincipal/TrataEventoTableWidgetJpeg.h Forms/TrataEventoLabelThumbnail.h Forms/VerificarAtualizacoes.h GpsPosition.h ManipulaExifFotos.h PeriodoAno.h PeriodoDia.h PeriodoMes.h PeriodoTracklog.h ReadFileGps.h threadExif/ThreadLoadExifDatas.h threadExif/ThreadPositionImages.h threadExif/ThreadRemoveExifDatas.h threadExif/ThreadRemoveFileNoDate.h threadExif/ThreadRemoveImagesGeoref.h
FORMS += Forms/ExibeFoto.ui Forms/FormPrincipal/TelaPrincipal.ui Forms/VerificarAtualizacoes.ui
RESOURCES += resources/resourcesIcon.qrc translations/translations.qrc
TRANSLATIONS += translations/linguagem_en_US.ts translations/linguagem_es.ts
OBJECTS_DIR = build/Release/GNU-Linux-x86
MOC_DIR = ./temp
RCC_DIR = ./temp
UI_DIR = ./temp
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += temp Forms . 
LIBS += -lexiv2 -lexiv2  
TRANSLATIONS = translations/linguagem_en.ts
CODECFORSRC = UTF-8
