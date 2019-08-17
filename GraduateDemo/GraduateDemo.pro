#-------------------------------------------------
#
# Project created by QtCreator 2019-05-02T11:56:35
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraduateDemo
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    formmusic.cpp \
    formlabenviroment.cpp \
    formlabenvdynamic.cpp \
    formdevsearch.cpp \
    formmemberinfosearch.cpp \
    formborrowdevinfo.cpp \
    formremoteoperation.cpp \
    databases.cpp \
    formlogin.cpp \
    common.cpp \
    table.cpp \
    mymessagebox.cpp \
    formregister.cpp

HEADERS  += widget.h \
    formmusic.h \
    formlabenviroment.h \
    formlabenvdynamic.h \
    formdevsearch.h \
    formmemberinfosearch.h \
    formborrowdevinfo.h \
    formremoteoperation.h \
    databases.h \
    common.h \
    formlogin.h \
    table.h \
    mymessagebox.h \
    formregister.h

FORMS    += widget.ui \
    formmusic.ui \
    formlabenviroment.ui \
    formlabenvdynamic.ui \
    formdevsearch.ui \
    formmemberinfosearch.ui \
    formborrowdevinfo.ui \
    formremoteoperation.ui \
    formlogin.ui \
    mymessagebox.ui \
    formregister.ui

RESOURCES += \
    imager.qrc
