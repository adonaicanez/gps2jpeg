#############################################################################
# Makefile for building: gps2jpegWindows
# Generated by qmake (2.01a) (Qt 4.8.3) on: dom 18. nov 18:27:26 2012
# Project:  nbproject/qt-Debug.pro
# Template: app
# Command: c:/Qt/4.8.3/bin/qmake.exe -spec c:/Qt/4.8.3/mkspecs/win32-g++ VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc.exe
CXX           = g++.exe
DEFINES       = -DUNICODE -DQT_LARGEFILE_SUPPORT -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_NETWORK_LIB -DQT_CORE_LIB -DQT_THREAD_SUPPORT -DQT_NEEDS_QMAIN -DQT_NO_DYNAMIC_CAST
CFLAGS        = -O2 -Wall -Wextra $(DEFINES)
CXXFLAGS      = -O2 -Wall -Wextra -fno-rtti $(DEFINES)
INCPATH       = -I'c:/Qt/4.8.3/include/QtCore' -I'c:/Qt/4.8.3/include/QtNetwork' -I'c:/Qt/4.8.3/include/QtGui' -I'c:/Qt/4.8.3/include' -I'../gps2jpegLinux' -I'../gps2jpegLinux/Forms' -I'temp' -I'c:/Qt/4.8.3/include/ActiveQt' -I'temp' -I'temp' -I'.' -I'c:/Qt/4.8.3/mkspecs/win32-g++'
LINK        =        g++
LFLAGS        =        -Wl,-s -Wl,-subsystem,windows
LIBS        =        -L'./lib' -L'c:/Qt/4.8.3/lib' -lmingw32 -lqtmain build/Debug/MinGW_4.6.2-Windows/iconWindows_res.o -lexiv2 -lQtGui -lQtNetwork -lgdi32 -lcomdlg32 -loleaut32 -limm32 -lwinmm -lwinspool -lmsimg32 -lQtCore -lole32 -luuid -lws2_32 -ladvapi32 -lshell32 -luser32 -lkernel32 
QMAKE         = c:/Qt/4.8.3/bin/qmake.exe
IDC           = c:/Qt/4.8.3/bin/idc.exe
IDL           = midl
ZIP           = zip -r -9
DEF_FILE      = 
RES_FILE      = build/Debug/MinGW_4.6.2-Windows/iconWindows_res.o
COPY          = cp
SED           = 
COPY_FILE     = $(COPY)
COPY_DIR      = cp -r
DEL_FILE      = rm
DEL_DIR       = rmdir
MOVE          = mv
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
INSTALL_FILE    = $(COPY_FILE)
INSTALL_PROGRAM = $(COPY_FILE)
INSTALL_DIR     = $(COPY_DIR)

####### Output directory

OBJECTS_DIR   = build/Debug/MinGW_4.6.2-Windows/

####### Files

SOURCES       = ../gps2jpegLinux/ReadFileGps.cpp \
		../gps2jpegLinux/Forms/ExibeFoto/GraphicsScene.cpp \
		../gps2jpegLinux/DadosArquivoGps.cpp \
		../gps2jpegLinux/Forms/FormPrincipal/TelaPrincipal.cpp \
		../gps2jpegLinux/PeriodoMes.cpp \
		../gps2jpegLinux/Forms/ExibeFoto.cpp \
		../gps2jpegLinux/main.cpp \
		../gps2jpegLinux/Forms/FormPrincipal/TrataEventoLabelPaypal.cpp \
		../gps2jpegLinux/Forms/FormPrincipal/TrataEventoTableWidgetJpeg.cpp \
		../gps2jpegLinux/threadExif/ThreadLoadExifDatas.cpp \
		../gps2jpegLinux/GpsPosition.cpp \
		../gps2jpegLinux/PeriodoDia.cpp \
		../gps2jpegLinux/Forms/ExibeFoto/GraphicsView.cpp \
		../gps2jpegLinux/Forms/FormPrincipal/TrataEventoLabelThumbnail.cpp \
		../gps2jpegLinux/Forms/VerificarAtualizacoes.cpp \
		../gps2jpegLinux/PeriodoTracklog.cpp \
		../gps2jpegLinux/threadExif/ThreadRemoveExifDatas.cpp \
		../gps2jpegLinux/threadExif/ThreadPositionImages.cpp \
		../gps2jpegLinux/threadExif/ThreadRemoveImagesGeoref.cpp \
		../gps2jpegLinux/threadExif/ThreadRemoveFileNoDate.cpp \
		../gps2jpegLinux/Forms/AddMetadata/AddMetadata.cpp \
		../gps2jpegLinux/PeriodoAno.cpp temp/moc_TelaPrincipal.cpp \
		temp/moc_ThreadPositionImages.cpp \
		temp/moc_VerificarAtualizacoes.cpp \
		temp/moc_ThreadRemoveImagesGeoref.cpp \
		temp/moc_ThreadRemoveExifDatas.cpp \
		temp/moc_TrataEventoTableWidgetJpeg.cpp \
		temp/moc_GraphicsView.cpp \
		temp/moc_ExibeFoto.cpp \
		temp/moc_AddMetadata.cpp \
		temp/moc_ThreadLoadExifDatas.cpp \
		temp/moc_GraphicsScene.cpp \
		temp/moc_TrataEventoLabelThumbnail.cpp \
		temp/moc_TrataEventoLabelPaypal.cpp \
		temp/qrc_resourcesIcon.cpp \
		temp/qrc_translations.cpp
OBJECTS       = build/Debug/MinGW_4.6.2-Windows/ReadFileGps.o \
		build/Debug/MinGW_4.6.2-Windows/GraphicsScene.o \
		build/Debug/MinGW_4.6.2-Windows/DadosArquivoGps.o \
		build/Debug/MinGW_4.6.2-Windows/TelaPrincipal.o \
		build/Debug/MinGW_4.6.2-Windows/PeriodoMes.o \
		build/Debug/MinGW_4.6.2-Windows/ExibeFoto.o \
		build/Debug/MinGW_4.6.2-Windows/main.o \
		build/Debug/MinGW_4.6.2-Windows/TrataEventoLabelPaypal.o \
		build/Debug/MinGW_4.6.2-Windows/TrataEventoTableWidgetJpeg.o \
		build/Debug/MinGW_4.6.2-Windows/ThreadLoadExifDatas.o \
		build/Debug/MinGW_4.6.2-Windows/GpsPosition.o \
		build/Debug/MinGW_4.6.2-Windows/PeriodoDia.o \
		build/Debug/MinGW_4.6.2-Windows/GraphicsView.o \
		build/Debug/MinGW_4.6.2-Windows/TrataEventoLabelThumbnail.o \
		build/Debug/MinGW_4.6.2-Windows/VerificarAtualizacoes.o \
		build/Debug/MinGW_4.6.2-Windows/PeriodoTracklog.o \
		build/Debug/MinGW_4.6.2-Windows/ThreadRemoveExifDatas.o \
		build/Debug/MinGW_4.6.2-Windows/ThreadPositionImages.o \
		build/Debug/MinGW_4.6.2-Windows/ThreadRemoveImagesGeoref.o \
		build/Debug/MinGW_4.6.2-Windows/ThreadRemoveFileNoDate.o \
		build/Debug/MinGW_4.6.2-Windows/AddMetadata.o \
		build/Debug/MinGW_4.6.2-Windows/PeriodoAno.o \
		build/Debug/MinGW_4.6.2-Windows/moc_TelaPrincipal.o \
		build/Debug/MinGW_4.6.2-Windows/moc_ThreadPositionImages.o \
		build/Debug/MinGW_4.6.2-Windows/moc_VerificarAtualizacoes.o \
		build/Debug/MinGW_4.6.2-Windows/moc_ThreadRemoveImagesGeoref.o \
		build/Debug/MinGW_4.6.2-Windows/moc_ThreadRemoveExifDatas.o \
		build/Debug/MinGW_4.6.2-Windows/moc_TrataEventoTableWidgetJpeg.o \
		build/Debug/MinGW_4.6.2-Windows/moc_GraphicsView.o \
		build/Debug/MinGW_4.6.2-Windows/moc_ExibeFoto.o \
		build/Debug/MinGW_4.6.2-Windows/moc_AddMetadata.o \
		build/Debug/MinGW_4.6.2-Windows/moc_ThreadLoadExifDatas.o \
		build/Debug/MinGW_4.6.2-Windows/moc_GraphicsScene.o \
		build/Debug/MinGW_4.6.2-Windows/moc_TrataEventoLabelThumbnail.o \
		build/Debug/MinGW_4.6.2-Windows/moc_TrataEventoLabelPaypal.o \
		build/Debug/MinGW_4.6.2-Windows/qrc_resourcesIcon.o \
		build/Debug/MinGW_4.6.2-Windows/qrc_translations.o
DIST          = 
QMAKE_TARGET  = gps2jpegWindows
DESTDIR        = dist/Debug/MinGW_4.6.2-Windows/ #avoid trailing-slash linebreak
TARGET         = gps2jpegWindows.exe
DESTDIR_TARGET = dist/Debug/MinGW_4.6.2-Windows/gps2jpegWindows.exe

####### Implicit rules

.SUFFIXES: .cpp .cc .cxx .c

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

####### Build rules

first: all
all: qttmp-Debug.mk  $(DESTDIR_TARGET)

$(DESTDIR_TARGET): temp/ui_VerificarAtualizacoes.h temp/ui_ExibeFoto.h temp/ui_TelaPrincipal.h temp/ui_AddMetadata.h $(OBJECTS) build/Debug/MinGW_4.6.2-Windows/iconWindows_res.o
	$(LINK) $(LFLAGS) -o $(DESTDIR_TARGET) object_script.gps2jpegWindows  $(LIBS)

build/Debug/MinGW_4.6.2-Windows/iconWindows_res.o: iconWindows.rc
	windres -i iconWindows.rc -o build/Debug/MinGW_4.6.2-Windows/iconWindows_res.o --include-dir=. $(DEFINES)

qttmp-Debug.mk: nbproject/qt-Debug.pro  c:/Qt/4.8.3/mkspecs/win32-g++/qmake.conf c:/Qt/4.8.3/mkspecs/features/device_config.prf \
		c:/Qt/4.8.3/mkspecs/features/qt_functions.prf \
		c:/Qt/4.8.3/mkspecs/features/qt_config.prf \
		c:/Qt/4.8.3/mkspecs/features/exclusive_builds.prf \
		c:/Qt/4.8.3/mkspecs/features/default_pre.prf \
		c:/Qt/4.8.3/mkspecs/features/win32/default_pre.prf \
		c:/Qt/4.8.3/mkspecs/features/release.prf \
		c:/Qt/4.8.3/mkspecs/features/default_post.prf \
		c:/Qt/4.8.3/mkspecs/features/win32/default_post.prf \
		c:/Qt/4.8.3/mkspecs/features/warn_on.prf \
		c:/Qt/4.8.3/mkspecs/features/qt.prf \
		c:/Qt/4.8.3/mkspecs/features/win32/thread.prf \
		c:/Qt/4.8.3/mkspecs/features/moc.prf \
		c:/Qt/4.8.3/mkspecs/features/win32/windows.prf \
		c:/Qt/4.8.3/mkspecs/features/win32/stl_off.prf \
		c:/Qt/4.8.3/mkspecs/features/win32/exceptions_off.prf \
		c:/Qt/4.8.3/mkspecs/features/win32/rtti_off.prf \
		c:/Qt/4.8.3/mkspecs/features/resources.prf \
		c:/Qt/4.8.3/mkspecs/features/uic.prf \
		c:/Qt/4.8.3/mkspecs/features/yacc.prf \
		c:/Qt/4.8.3/mkspecs/features/lex.prf \
		c:/Qt/4.8.3/lib/qtmain.prl \
		c:/Qt/4.8.3/lib/QtGui.prl \
		c:/Qt/4.8.3/lib/QtNetwork.prl \
		c:/Qt/4.8.3/lib/QtCore.prl
	$(QMAKE) -spec c:/Qt/4.8.3/mkspecs/win32-g++ VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro
c:/Qt/4.8.3/mkspecs/features/device_config.prf:
c:/Qt/4.8.3/mkspecs/features/qt_functions.prf:
c:/Qt/4.8.3/mkspecs/features/qt_config.prf:
c:/Qt/4.8.3/mkspecs/features/exclusive_builds.prf:
c:/Qt/4.8.3/mkspecs/features/default_pre.prf:
c:/Qt/4.8.3/mkspecs/features/win32/default_pre.prf:
c:/Qt/4.8.3/mkspecs/features/release.prf:
c:/Qt/4.8.3/mkspecs/features/default_post.prf:
c:/Qt/4.8.3/mkspecs/features/win32/default_post.prf:
c:/Qt/4.8.3/mkspecs/features/warn_on.prf:
c:/Qt/4.8.3/mkspecs/features/qt.prf:
c:/Qt/4.8.3/mkspecs/features/win32/thread.prf:
c:/Qt/4.8.3/mkspecs/features/moc.prf:
c:/Qt/4.8.3/mkspecs/features/win32/windows.prf:
c:/Qt/4.8.3/mkspecs/features/win32/stl_off.prf:
c:/Qt/4.8.3/mkspecs/features/win32/exceptions_off.prf:
c:/Qt/4.8.3/mkspecs/features/win32/rtti_off.prf:
c:/Qt/4.8.3/mkspecs/features/resources.prf:
c:/Qt/4.8.3/mkspecs/features/uic.prf:
c:/Qt/4.8.3/mkspecs/features/yacc.prf:
c:/Qt/4.8.3/mkspecs/features/lex.prf:
c:\Qt\4.8.3\lib\qtmain.prl:
c:\Qt\4.8.3\lib\QtGui.prl:
c:\Qt\4.8.3\lib\QtNetwork.prl:
c:\Qt\4.8.3\lib\QtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec c:/Qt/4.8.3/mkspecs/win32-g++ VPATH=. -o qttmp-Debug.mk nbproject/qt-Debug.pro

dist:
	$(ZIP) gps2jpegWindows.zip $(SOURCES) $(DIST) nbproject/nbproject/qt-Debug.pro c:/Qt/4.8.3/mkspecs/features/device_config.prf c:/Qt/4.8.3/mkspecs/features/qt_functions.prf c:/Qt/4.8.3/mkspecs/features/qt_config.prf c:/Qt/4.8.3/mkspecs/features/exclusive_builds.prf c:/Qt/4.8.3/mkspecs/features/default_pre.prf c:/Qt/4.8.3/mkspecs/features/win32/default_pre.prf c:/Qt/4.8.3/mkspecs/features/release.prf c:/Qt/4.8.3/mkspecs/features/default_post.prf c:/Qt/4.8.3/mkspecs/features/win32/default_post.prf c:/Qt/4.8.3/mkspecs/features/warn_on.prf c:/Qt/4.8.3/mkspecs/features/qt.prf c:/Qt/4.8.3/mkspecs/features/win32/thread.prf c:/Qt/4.8.3/mkspecs/features/moc.prf c:/Qt/4.8.3/mkspecs/features/win32/windows.prf c:/Qt/4.8.3/mkspecs/features/win32/stl_off.prf c:/Qt/4.8.3/mkspecs/features/win32/exceptions_off.prf c:/Qt/4.8.3/mkspecs/features/win32/rtti_off.prf c:/Qt/4.8.3/mkspecs/features/resources.prf c:/Qt/4.8.3/mkspecs/features/uic.prf c:/Qt/4.8.3/mkspecs/features/yacc.prf c:/Qt/4.8.3/mkspecs/features/lex.prf c:\Qt\4.8.3\lib\qtmain.prl c:\Qt\4.8.3\lib\QtGui.prl c:\Qt\4.8.3\lib\QtNetwork.prl c:\Qt\4.8.3\lib\QtCore.prl ..\gps2jpegLinux\translations\linguagem_en_US.ts ..\gps2jpegLinux\translations\linguagem_es.ts ..\gps2jpegLinux\translations\linguagem_en_US.ts ..\gps2jpegLinux\translations\linguagem_es.ts HEADERS RESOURCES IMAGES SOURCES OBJECTIVE_SOURCES FORMS YACCSOURCES YACCSOURCES LEXSOURCES 

clean: compiler_clean 
	-$(DEL_FILE) build/Debug/MinGW_4.6.2-Windows/ReadFileGps.o build/Debug/MinGW_4.6.2-Windows/GraphicsScene.o build/Debug/MinGW_4.6.2-Windows/DadosArquivoGps.o build/Debug/MinGW_4.6.2-Windows/TelaPrincipal.o build/Debug/MinGW_4.6.2-Windows/PeriodoMes.o build/Debug/MinGW_4.6.2-Windows/ExibeFoto.o build/Debug/MinGW_4.6.2-Windows/main.o build/Debug/MinGW_4.6.2-Windows/TrataEventoLabelPaypal.o build/Debug/MinGW_4.6.2-Windows/TrataEventoTableWidgetJpeg.o build/Debug/MinGW_4.6.2-Windows/ThreadLoadExifDatas.o build/Debug/MinGW_4.6.2-Windows/GpsPosition.o build/Debug/MinGW_4.6.2-Windows/PeriodoDia.o build/Debug/MinGW_4.6.2-Windows/GraphicsView.o build/Debug/MinGW_4.6.2-Windows/TrataEventoLabelThumbnail.o build/Debug/MinGW_4.6.2-Windows/VerificarAtualizacoes.o build/Debug/MinGW_4.6.2-Windows/PeriodoTracklog.o build/Debug/MinGW_4.6.2-Windows/ThreadRemoveExifDatas.o build/Debug/MinGW_4.6.2-Windows/ThreadPositionImages.o build/Debug/MinGW_4.6.2-Windows/ThreadRemoveImagesGeoref.o build/Debug/MinGW_4.6.2-Windows/ThreadRemoveFileNoDate.o build/Debug/MinGW_4.6.2-Windows/AddMetadata.o build/Debug/MinGW_4.6.2-Windows/PeriodoAno.o build/Debug/MinGW_4.6.2-Windows/moc_TelaPrincipal.o build/Debug/MinGW_4.6.2-Windows/moc_ThreadPositionImages.o build/Debug/MinGW_4.6.2-Windows/moc_VerificarAtualizacoes.o build/Debug/MinGW_4.6.2-Windows/moc_ThreadRemoveImagesGeoref.o build/Debug/MinGW_4.6.2-Windows/moc_ThreadRemoveExifDatas.o build/Debug/MinGW_4.6.2-Windows/moc_TrataEventoTableWidgetJpeg.o build/Debug/MinGW_4.6.2-Windows/moc_GraphicsView.o build/Debug/MinGW_4.6.2-Windows/moc_ExibeFoto.o build/Debug/MinGW_4.6.2-Windows/moc_AddMetadata.o build/Debug/MinGW_4.6.2-Windows/moc_ThreadLoadExifDatas.o build/Debug/MinGW_4.6.2-Windows/moc_GraphicsScene.o build/Debug/MinGW_4.6.2-Windows/moc_TrataEventoLabelThumbnail.o build/Debug/MinGW_4.6.2-Windows/moc_TrataEventoLabelPaypal.o build/Debug/MinGW_4.6.2-Windows/qrc_resourcesIcon.o build/Debug/MinGW_4.6.2-Windows/qrc_translations.o
	-$(DEL_FILE) build/Debug/MinGW_4.6.2-Windows/iconWindows_res.o

distclean: clean
	-$(DEL_FILE) $(DESTDIR_TARGET)
	-$(DEL_FILE) qttmp-Debug.mk

check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: temp/moc_TelaPrincipal.cpp temp/moc_ThreadPositionImages.cpp temp/moc_VerificarAtualizacoes.cpp temp/moc_ThreadRemoveImagesGeoref.cpp temp/moc_ThreadRemoveExifDatas.cpp temp/moc_TrataEventoTableWidgetJpeg.cpp temp/moc_GraphicsView.cpp temp/moc_ExibeFoto.cpp temp/moc_AddMetadata.cpp temp/moc_ThreadLoadExifDatas.cpp temp/moc_GraphicsScene.cpp temp/moc_TrataEventoLabelThumbnail.cpp temp/moc_TrataEventoLabelPaypal.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) temp/moc_TelaPrincipal.cpp temp/moc_ThreadPositionImages.cpp temp/moc_VerificarAtualizacoes.cpp temp/moc_ThreadRemoveImagesGeoref.cpp temp/moc_ThreadRemoveExifDatas.cpp temp/moc_TrataEventoTableWidgetJpeg.cpp temp/moc_GraphicsView.cpp temp/moc_ExibeFoto.cpp temp/moc_AddMetadata.cpp temp/moc_ThreadLoadExifDatas.cpp temp/moc_GraphicsScene.cpp temp/moc_TrataEventoLabelThumbnail.cpp temp/moc_TrataEventoLabelPaypal.cpp
temp/moc_TelaPrincipal.cpp: temp/ui_TelaPrincipal.h \
		../gps2jpegLinux/Forms/FormPrincipal/TelaPrincipal.h
	C:/Qt/4.8.3/bin/moc.exe $(DEFINES) $(INCPATH) -D__GNUC__ -DWIN32 ../gps2jpegLinux/Forms/FormPrincipal/TelaPrincipal.h -o temp/moc_TelaPrincipal.cpp

temp/moc_ThreadPositionImages.cpp: ../gps2jpegLinux/threadExif/ThreadLoadExifDatas.h \
		../gps2jpegLinux/threadExif/ThreadPositionImages.h
	C:/Qt/4.8.3/bin/moc.exe $(DEFINES) $(INCPATH) -D__GNUC__ -DWIN32 ../gps2jpegLinux/threadExif/ThreadPositionImages.h -o temp/moc_ThreadPositionImages.cpp

temp/moc_VerificarAtualizacoes.cpp: temp/ui_VerificarAtualizacoes.h \
		../gps2jpegLinux/Forms/VerificarAtualizacoes.h
	C:/Qt/4.8.3/bin/moc.exe $(DEFINES) $(INCPATH) -D__GNUC__ -DWIN32 ../gps2jpegLinux/Forms/VerificarAtualizacoes.h -o temp/moc_VerificarAtualizacoes.cpp

temp/moc_ThreadRemoveImagesGeoref.cpp: ../gps2jpegLinux/threadExif/ThreadRemoveImagesGeoref.h
	C:/Qt/4.8.3/bin/moc.exe $(DEFINES) $(INCPATH) -D__GNUC__ -DWIN32 ../gps2jpegLinux/threadExif/ThreadRemoveImagesGeoref.h -o temp/moc_ThreadRemoveImagesGeoref.cpp

temp/moc_ThreadRemoveExifDatas.cpp: ../gps2jpegLinux/threadExif/ThreadRemoveExifDatas.h
	C:/Qt/4.8.3/bin/moc.exe $(DEFINES) $(INCPATH) -D__GNUC__ -DWIN32 ../gps2jpegLinux/threadExif/ThreadRemoveExifDatas.h -o temp/moc_ThreadRemoveExifDatas.cpp

temp/moc_TrataEventoTableWidgetJpeg.cpp: ../gps2jpegLinux/Forms/FormPrincipal/TrataEventoTableWidgetJpeg.h
	C:/Qt/4.8.3/bin/moc.exe $(DEFINES) $(INCPATH) -D__GNUC__ -DWIN32 ../gps2jpegLinux/Forms/FormPrincipal/TrataEventoTableWidgetJpeg.h -o temp/moc_TrataEventoTableWidgetJpeg.cpp

temp/moc_GraphicsView.cpp: ../gps2jpegLinux/Forms/ExibeFoto/GraphicsScene.h \
		../gps2jpegLinux/Forms/ExibeFoto/GraphicsView.h
	C:/Qt/4.8.3/bin/moc.exe $(DEFINES) $(INCPATH) -D__GNUC__ -DWIN32 ../gps2jpegLinux/Forms/ExibeFoto/GraphicsView.h -o temp/moc_GraphicsView.cpp

temp/moc_ExibeFoto.cpp: temp/ui_ExibeFoto.h \
		../gps2jpegLinux/Forms/ExibeFoto/GraphicsScene.h \
		../gps2jpegLinux/Forms/ExibeFoto.h
	C:/Qt/4.8.3/bin/moc.exe $(DEFINES) $(INCPATH) -D__GNUC__ -DWIN32 ../gps2jpegLinux/Forms/ExibeFoto.h -o temp/moc_ExibeFoto.cpp

temp/moc_AddMetadata.cpp: temp/ui_AddMetadata.h \
		../gps2jpegLinux/Forms/AddMetadata/AddMetadata.h
	C:/Qt/4.8.3/bin/moc.exe $(DEFINES) $(INCPATH) -D__GNUC__ -DWIN32 ../gps2jpegLinux/Forms/AddMetadata/AddMetadata.h -o temp/moc_AddMetadata.cpp

temp/moc_ThreadLoadExifDatas.cpp: ../gps2jpegLinux/threadExif/ThreadLoadExifDatas.h
	C:/Qt/4.8.3/bin/moc.exe $(DEFINES) $(INCPATH) -D__GNUC__ -DWIN32 ../gps2jpegLinux/threadExif/ThreadLoadExifDatas.h -o temp/moc_ThreadLoadExifDatas.cpp

temp/moc_GraphicsScene.cpp: ../gps2jpegLinux/Forms/ExibeFoto/GraphicsScene.h
	C:/Qt/4.8.3/bin/moc.exe $(DEFINES) $(INCPATH) -D__GNUC__ -DWIN32 ../gps2jpegLinux/Forms/ExibeFoto/GraphicsScene.h -o temp/moc_GraphicsScene.cpp

temp/moc_TrataEventoLabelThumbnail.cpp: ../gps2jpegLinux/Forms/FormPrincipal/TrataEventoLabelThumbnail.h
	C:/Qt/4.8.3/bin/moc.exe $(DEFINES) $(INCPATH) -D__GNUC__ -DWIN32 ../gps2jpegLinux/Forms/FormPrincipal/TrataEventoLabelThumbnail.h -o temp/moc_TrataEventoLabelThumbnail.cpp

temp/moc_TrataEventoLabelPaypal.cpp: ../gps2jpegLinux/Forms/FormPrincipal/TrataEventoLabelPaypal.h
	C:/Qt/4.8.3/bin/moc.exe $(DEFINES) $(INCPATH) -D__GNUC__ -DWIN32 ../gps2jpegLinux/Forms/FormPrincipal/TrataEventoLabelPaypal.h -o temp/moc_TrataEventoLabelPaypal.cpp

compiler_rcc_make_all: temp/qrc_resourcesIcon.cpp temp/qrc_translations.cpp
compiler_rcc_clean:
	-$(DEL_FILE) temp/qrc_resourcesIcon.cpp temp/qrc_translations.cpp
temp/qrc_resourcesIcon.cpp: ../gps2jpegLinux/resources/resourcesIcon.qrc
	c:/Qt/4.8.3/bin/rcc.exe -name resourcesIcon ../gps2jpegLinux/resources/resourcesIcon.qrc -o temp/qrc_resourcesIcon.cpp

temp/qrc_translations.cpp: ../gps2jpegLinux/translations/translations.qrc
	c:/Qt/4.8.3/bin/rcc.exe -name translations ../gps2jpegLinux/translations/translations.qrc -o temp/qrc_translations.cpp

compiler_image_collection_make_all: temp/qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) temp/qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: temp/ui_VerificarAtualizacoes.h temp/ui_ExibeFoto.h temp/ui_TelaPrincipal.h temp/ui_AddMetadata.h
compiler_uic_clean:
	-$(DEL_FILE) temp/ui_VerificarAtualizacoes.h temp/ui_ExibeFoto.h temp/ui_TelaPrincipal.h temp/ui_AddMetadata.h
temp/ui_VerificarAtualizacoes.h: ../gps2jpegLinux/Forms/VerificarAtualizacoes.ui
	c:/Qt/4.8.3/bin/uic.exe ../gps2jpegLinux/Forms/VerificarAtualizacoes.ui -o temp/ui_VerificarAtualizacoes.h

temp/ui_ExibeFoto.h: ../gps2jpegLinux/Forms/ExibeFoto.ui
	c:/Qt/4.8.3/bin/uic.exe ../gps2jpegLinux/Forms/ExibeFoto.ui -o temp/ui_ExibeFoto.h

temp/ui_TelaPrincipal.h: ../gps2jpegLinux/Forms/FormPrincipal/TelaPrincipal.ui
	c:/Qt/4.8.3/bin/uic.exe ../gps2jpegLinux/Forms/FormPrincipal/TelaPrincipal.ui -o temp/ui_TelaPrincipal.h

temp/ui_AddMetadata.h: ../gps2jpegLinux/Forms/AddMetadata/AddMetadata.ui
	c:/Qt/4.8.3/bin/uic.exe ../gps2jpegLinux/Forms/AddMetadata/AddMetadata.ui -o temp/ui_AddMetadata.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 



####### Compile

build/Debug/MinGW_4.6.2-Windows/ReadFileGps.o: ../gps2jpegLinux/ReadFileGps.cpp ../gps2jpegLinux/ReadFileGps.h \
		../gps2jpegLinux/DadosArquivoGps.h \
		../gps2jpegLinux/PeriodoTracklog.h \
		../gps2jpegLinux/GpsPosition.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/ReadFileGps.o ../gps2jpegLinux/ReadFileGps.cpp

build/Debug/MinGW_4.6.2-Windows/GraphicsScene.o: ../gps2jpegLinux/Forms/ExibeFoto/GraphicsScene.cpp ../gps2jpegLinux/Forms/ExibeFoto/GraphicsScene.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/GraphicsScene.o ../gps2jpegLinux/Forms/ExibeFoto/GraphicsScene.cpp

build/Debug/MinGW_4.6.2-Windows/DadosArquivoGps.o: ../gps2jpegLinux/DadosArquivoGps.cpp ../gps2jpegLinux/DadosArquivoGps.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/DadosArquivoGps.o ../gps2jpegLinux/DadosArquivoGps.cpp

build/Debug/MinGW_4.6.2-Windows/TelaPrincipal.o: ../gps2jpegLinux/Forms/FormPrincipal/TelaPrincipal.cpp ../gps2jpegLinux/Forms/FormPrincipal/TelaPrincipal.h \
		temp/ui_TelaPrincipal.h \
		../gps2jpegLinux/Forms/FormPrincipal/TrataEventoLabelThumbnail.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/TelaPrincipal.o ../gps2jpegLinux/Forms/FormPrincipal/TelaPrincipal.cpp

build/Debug/MinGW_4.6.2-Windows/PeriodoMes.o: ../gps2jpegLinux/PeriodoMes.cpp ../gps2jpegLinux/PeriodoMes.h \
		../gps2jpegLinux/GpsPosition.h \
		../gps2jpegLinux/PeriodoDia.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/PeriodoMes.o ../gps2jpegLinux/PeriodoMes.cpp

build/Debug/MinGW_4.6.2-Windows/ExibeFoto.o: ../gps2jpegLinux/Forms/ExibeFoto.cpp ../gps2jpegLinux/Forms/ExibeFoto.h \
		temp/ui_ExibeFoto.h \
		../gps2jpegLinux/Forms/ExibeFoto/GraphicsScene.h \
		../gps2jpegLinux/Forms/AddMetadata/AddMetadata.h \
		temp/ui_AddMetadata.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/ExibeFoto.o ../gps2jpegLinux/Forms/ExibeFoto.cpp

build/Debug/MinGW_4.6.2-Windows/main.o: ../gps2jpegLinux/main.cpp ../gps2jpegLinux/Forms/FormPrincipal/TelaPrincipal.h \
		temp/ui_TelaPrincipal.h \
		../gps2jpegLinux/DadosArquivoGps.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/main.o ../gps2jpegLinux/main.cpp

build/Debug/MinGW_4.6.2-Windows/TrataEventoLabelPaypal.o: ../gps2jpegLinux/Forms/FormPrincipal/TrataEventoLabelPaypal.cpp ../gps2jpegLinux/Forms/FormPrincipal/TrataEventoLabelPaypal.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/TrataEventoLabelPaypal.o ../gps2jpegLinux/Forms/FormPrincipal/TrataEventoLabelPaypal.cpp

build/Debug/MinGW_4.6.2-Windows/TrataEventoTableWidgetJpeg.o: ../gps2jpegLinux/Forms/FormPrincipal/TrataEventoTableWidgetJpeg.cpp ../gps2jpegLinux/Forms/FormPrincipal/TrataEventoTableWidgetJpeg.h \
		../gps2jpegLinux/Forms/FormPrincipal/TelaPrincipal.h \
		temp/ui_TelaPrincipal.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/TrataEventoTableWidgetJpeg.o ../gps2jpegLinux/Forms/FormPrincipal/TrataEventoTableWidgetJpeg.cpp

build/Debug/MinGW_4.6.2-Windows/ThreadLoadExifDatas.o: ../gps2jpegLinux/threadExif/ThreadLoadExifDatas.cpp ../gps2jpegLinux/threadExif/ThreadLoadExifDatas.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/ThreadLoadExifDatas.o ../gps2jpegLinux/threadExif/ThreadLoadExifDatas.cpp

build/Debug/MinGW_4.6.2-Windows/GpsPosition.o: ../gps2jpegLinux/GpsPosition.cpp ../gps2jpegLinux/GpsPosition.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/GpsPosition.o ../gps2jpegLinux/GpsPosition.cpp

build/Debug/MinGW_4.6.2-Windows/PeriodoDia.o: ../gps2jpegLinux/PeriodoDia.cpp ../gps2jpegLinux/PeriodoDia.h \
		../gps2jpegLinux/GpsPosition.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/PeriodoDia.o ../gps2jpegLinux/PeriodoDia.cpp

build/Debug/MinGW_4.6.2-Windows/GraphicsView.o: ../gps2jpegLinux/Forms/ExibeFoto/GraphicsView.cpp ../gps2jpegLinux/Forms/ExibeFoto/GraphicsView.h \
		../gps2jpegLinux/Forms/ExibeFoto/GraphicsScene.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/GraphicsView.o ../gps2jpegLinux/Forms/ExibeFoto/GraphicsView.cpp

build/Debug/MinGW_4.6.2-Windows/TrataEventoLabelThumbnail.o: ../gps2jpegLinux/Forms/FormPrincipal/TrataEventoLabelThumbnail.cpp ../gps2jpegLinux/Forms/FormPrincipal/TrataEventoLabelThumbnail.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/TrataEventoLabelThumbnail.o ../gps2jpegLinux/Forms/FormPrincipal/TrataEventoLabelThumbnail.cpp

build/Debug/MinGW_4.6.2-Windows/VerificarAtualizacoes.o: ../gps2jpegLinux/Forms/VerificarAtualizacoes.cpp ../gps2jpegLinux/Forms/VerificarAtualizacoes.h \
		temp/ui_VerificarAtualizacoes.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/VerificarAtualizacoes.o ../gps2jpegLinux/Forms/VerificarAtualizacoes.cpp

build/Debug/MinGW_4.6.2-Windows/PeriodoTracklog.o: ../gps2jpegLinux/PeriodoTracklog.cpp ../gps2jpegLinux/PeriodoTracklog.h \
		../gps2jpegLinux/GpsPosition.h \
		../gps2jpegLinux/PeriodoAno.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/PeriodoTracklog.o ../gps2jpegLinux/PeriodoTracklog.cpp

build/Debug/MinGW_4.6.2-Windows/ThreadRemoveExifDatas.o: ../gps2jpegLinux/threadExif/ThreadRemoveExifDatas.cpp ../gps2jpegLinux/threadExif/ThreadRemoveExifDatas.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/ThreadRemoveExifDatas.o ../gps2jpegLinux/threadExif/ThreadRemoveExifDatas.cpp

build/Debug/MinGW_4.6.2-Windows/ThreadPositionImages.o: ../gps2jpegLinux/threadExif/ThreadPositionImages.cpp ../gps2jpegLinux/threadExif/ThreadPositionImages.h \
		../gps2jpegLinux/threadExif/ThreadLoadExifDatas.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/ThreadPositionImages.o ../gps2jpegLinux/threadExif/ThreadPositionImages.cpp

build/Debug/MinGW_4.6.2-Windows/ThreadRemoveImagesGeoref.o: ../gps2jpegLinux/threadExif/ThreadRemoveImagesGeoref.cpp ../gps2jpegLinux/threadExif/ThreadRemoveImagesGeoref.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/ThreadRemoveImagesGeoref.o ../gps2jpegLinux/threadExif/ThreadRemoveImagesGeoref.cpp

build/Debug/MinGW_4.6.2-Windows/ThreadRemoveFileNoDate.o: ../gps2jpegLinux/threadExif/ThreadRemoveFileNoDate.cpp ../gps2jpegLinux/threadExif/ThreadRemoveFileNoDate.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/ThreadRemoveFileNoDate.o ../gps2jpegLinux/threadExif/ThreadRemoveFileNoDate.cpp

build/Debug/MinGW_4.6.2-Windows/AddMetadata.o: ../gps2jpegLinux/Forms/AddMetadata/AddMetadata.cpp ../gps2jpegLinux/Forms/AddMetadata/AddMetadata.h \
		temp/ui_AddMetadata.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/AddMetadata.o ../gps2jpegLinux/Forms/AddMetadata/AddMetadata.cpp

build/Debug/MinGW_4.6.2-Windows/PeriodoAno.o: ../gps2jpegLinux/PeriodoAno.cpp ../gps2jpegLinux/PeriodoAno.h \
		../gps2jpegLinux/GpsPosition.h \
		../gps2jpegLinux/PeriodoMes.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/PeriodoAno.o ../gps2jpegLinux/PeriodoAno.cpp

build/Debug/MinGW_4.6.2-Windows/moc_TelaPrincipal.o: temp/moc_TelaPrincipal.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/moc_TelaPrincipal.o temp/moc_TelaPrincipal.cpp

build/Debug/MinGW_4.6.2-Windows/moc_ThreadPositionImages.o: temp/moc_ThreadPositionImages.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/moc_ThreadPositionImages.o temp/moc_ThreadPositionImages.cpp

build/Debug/MinGW_4.6.2-Windows/moc_VerificarAtualizacoes.o: temp/moc_VerificarAtualizacoes.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/moc_VerificarAtualizacoes.o temp/moc_VerificarAtualizacoes.cpp

build/Debug/MinGW_4.6.2-Windows/moc_ThreadRemoveImagesGeoref.o: temp/moc_ThreadRemoveImagesGeoref.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/moc_ThreadRemoveImagesGeoref.o temp/moc_ThreadRemoveImagesGeoref.cpp

build/Debug/MinGW_4.6.2-Windows/moc_ThreadRemoveExifDatas.o: temp/moc_ThreadRemoveExifDatas.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/moc_ThreadRemoveExifDatas.o temp/moc_ThreadRemoveExifDatas.cpp

build/Debug/MinGW_4.6.2-Windows/moc_TrataEventoTableWidgetJpeg.o: temp/moc_TrataEventoTableWidgetJpeg.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/moc_TrataEventoTableWidgetJpeg.o temp/moc_TrataEventoTableWidgetJpeg.cpp

build/Debug/MinGW_4.6.2-Windows/moc_GraphicsView.o: temp/moc_GraphicsView.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/moc_GraphicsView.o temp/moc_GraphicsView.cpp

build/Debug/MinGW_4.6.2-Windows/moc_ExibeFoto.o: temp/moc_ExibeFoto.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/moc_ExibeFoto.o temp/moc_ExibeFoto.cpp

build/Debug/MinGW_4.6.2-Windows/moc_AddMetadata.o: temp/moc_AddMetadata.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/moc_AddMetadata.o temp/moc_AddMetadata.cpp

build/Debug/MinGW_4.6.2-Windows/moc_ThreadLoadExifDatas.o: temp/moc_ThreadLoadExifDatas.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/moc_ThreadLoadExifDatas.o temp/moc_ThreadLoadExifDatas.cpp

build/Debug/MinGW_4.6.2-Windows/moc_GraphicsScene.o: temp/moc_GraphicsScene.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/moc_GraphicsScene.o temp/moc_GraphicsScene.cpp

build/Debug/MinGW_4.6.2-Windows/moc_TrataEventoLabelThumbnail.o: temp/moc_TrataEventoLabelThumbnail.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/moc_TrataEventoLabelThumbnail.o temp/moc_TrataEventoLabelThumbnail.cpp

build/Debug/MinGW_4.6.2-Windows/moc_TrataEventoLabelPaypal.o: temp/moc_TrataEventoLabelPaypal.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/moc_TrataEventoLabelPaypal.o temp/moc_TrataEventoLabelPaypal.cpp

build/Debug/MinGW_4.6.2-Windows/qrc_resourcesIcon.o: temp/qrc_resourcesIcon.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/qrc_resourcesIcon.o temp/qrc_resourcesIcon.cpp

build/Debug/MinGW_4.6.2-Windows/qrc_translations.o: temp/qrc_translations.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o build/Debug/MinGW_4.6.2-Windows/qrc_translations.o temp/qrc_translations.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

