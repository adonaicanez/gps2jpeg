# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release_Windows/MinGWLinux-Linux-x86
TARGET = gps2jpegLinux
VERSION = 3.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
QT = core gui network
SOURCES += PeriodoMes.cpp Forms/TelaPrincipal.cpp Forms/ExibeFoto/GraphicsView.cpp main.cpp PeriodoTracklog.cpp GpsPosition.cpp threadExif/ThreadPositionImages.cpp ReadFileGps.cpp ManipulaExifFotos.cpp Forms/ExibeFoto.cpp PeriodoDia.cpp threadExif/ThreadRemoveExifDatas.cpp Forms/ExibeFoto/GraphicsScene.cpp PeriodoAno.cpp DadosArquivoGps.cpp Forms/TrataEventoLabelPaypal.cpp threadExif/ThreadLoadExifDatas.cpp Forms/VerificarAtualizacoes.cpp Forms/TrataEventoLabelThumbnail.cpp
HEADERS += Forms/TrataEventoLabelPaypal.h Forms/TrataEventoLabelFoto.h threadExif/ThreadPositionImages.h ReadFileGps.h Forms/TelaPrincipal.h PeriodoAno.h Forms/TrataEventoLabelThumbnail.h GpsPosition.h threadExif/ThreadRemoveExifDatas.h Forms/ExibeFoto/GraphicsView.h PeriodoDia.h Forms/VerificarAtualizacoes.h DadosArquivoGps.h threadExif/ThreadLoadExifDatas.h PeriodoMes.h PeriodoTracklog.h Forms/ExibeFoto.h Forms/ExibeFoto/GraphicsScene.h ManipulaExifFotos.h
FORMS += Forms/TelaPrincipal.ui Forms/ExibeFoto.ui Forms/VerificarAtualizacoes.ui
RESOURCES += translations/translations.qrc resources/resourcesIcon.qrc
TRANSLATIONS += translations/linguagem_es.ts translations/linguagem_en_US.ts
OBJECTS_DIR = build/Release_Windows/MinGWLinux-Linux-x86
MOC_DIR = ./temp
RCC_DIR = ./temp
UI_DIR = ./temp
QMAKE_CC = i686-pc-mingw32-gcc
QMAKE_CXX = i686-pc-mingw32-g++
DEFINES += 
INCLUDEPATH += temp Forms . 
LIBS += -lexiv2  
TRANSLATIONS = translations/linguagem_en.ts
CODECFORSRC = UTF-8
