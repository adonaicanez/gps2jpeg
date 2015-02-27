# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/MinGW_4.9.1-Windows
TARGET = gps2jpegWindows
VERSION = 5.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
PKGCONFIG +=
QT = core gui network
SOURCES += ../gps2jpegLinux/DadosArquivoGps.cpp ../gps2jpegLinux/Forms/AddMetadata/AddMetadata.cpp ../gps2jpegLinux/Forms/ExibeFoto.cpp ../gps2jpegLinux/Forms/ExibeFoto/GraphicsScene.cpp ../gps2jpegLinux/Forms/ExibeFoto/GraphicsView.cpp ../gps2jpegLinux/Forms/FormPrincipal/TelaPrincipal.cpp ../gps2jpegLinux/Forms/FormPrincipal/TrataEventoLabelPaypal.cpp ../gps2jpegLinux/Forms/FormPrincipal/TrataEventoLabelThumbnail.cpp ../gps2jpegLinux/Forms/FormPrincipal/TrataEventoTableWidgetJpeg.cpp ../gps2jpegLinux/Forms/VerificarAtualizacoes.cpp ../gps2jpegLinux/GpsPosition.cpp ../gps2jpegLinux/PeriodoAno.cpp ../gps2jpegLinux/PeriodoDia.cpp ../gps2jpegLinux/PeriodoMes.cpp ../gps2jpegLinux/PeriodoTracklog.cpp ../gps2jpegLinux/ReadFileGps.cpp ../gps2jpegLinux/main.cpp ../gps2jpegLinux/threadExif/ThreadLoadExifDatas.cpp ../gps2jpegLinux/threadExif/ThreadPositionImages.cpp ../gps2jpegLinux/threadExif/ThreadRemoveExifDatas.cpp ../gps2jpegLinux/threadExif/ThreadRemoveFileNoDate.cpp ../gps2jpegLinux/threadExif/ThreadRemoveImagesGeoref.cpp
HEADERS += ../gps2jpegLinux/DadosArquivoGps.h ../gps2jpegLinux/Forms/AddMetadata/AddMetadata.h ../gps2jpegLinux/Forms/ExibeFoto.h ../gps2jpegLinux/Forms/ExibeFoto/GraphicsScene.h ../gps2jpegLinux/Forms/ExibeFoto/GraphicsView.h ../gps2jpegLinux/Forms/FormPrincipal/TelaPrincipal.h ../gps2jpegLinux/Forms/FormPrincipal/TrataEventoLabelPaypal.h ../gps2jpegLinux/Forms/FormPrincipal/TrataEventoLabelThumbnail.h ../gps2jpegLinux/Forms/FormPrincipal/TrataEventoTableWidgetJpeg.h ../gps2jpegLinux/Forms/VerificarAtualizacoes.h ../gps2jpegLinux/GpsPosition.h ../gps2jpegLinux/PeriodoAno.h ../gps2jpegLinux/PeriodoDia.h ../gps2jpegLinux/PeriodoMes.h ../gps2jpegLinux/PeriodoTracklog.h ../gps2jpegLinux/ReadFileGps.h ../gps2jpegLinux/threadExif/ThreadLoadExifDatas.h ../gps2jpegLinux/threadExif/ThreadPositionImages.h ../gps2jpegLinux/threadExif/ThreadRemoveExifDatas.h ../gps2jpegLinux/threadExif/ThreadRemoveFileNoDate.h ../gps2jpegLinux/threadExif/ThreadRemoveImagesGeoref.h
FORMS += ../gps2jpegLinux/Forms/AddMetadata/AddMetadata.ui ../gps2jpegLinux/Forms/ExibeFoto.ui ../gps2jpegLinux/Forms/FormPrincipal/TelaPrincipal.ui ../gps2jpegLinux/Forms/VerificarAtualizacoes.ui
RESOURCES += ../gps2jpegLinux/resources/resourcesIcon.qrc ../gps2jpegLinux/translations/translations.qrc
TRANSLATIONS += ../gps2jpegLinux/translations/linguagem_en_US.ts ../gps2jpegLinux/translations/linguagem_es.ts
OBJECTS_DIR = build/Release/MinGW_4.9.1-Windows
MOC_DIR = ./temp
RCC_DIR = ./temp
UI_DIR = ./temp
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += ../gps2jpegLinux ../gps2jpegLinux/Forms temp /C/msys/1.0/local/include /C/Qt/4.8.3/src /C/msys/1.0/include 
LIBS += -lexiv2  
"RC_FILE = ../iconWindows.rc"
