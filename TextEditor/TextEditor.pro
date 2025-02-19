#-------------------------------------------------
#
# Project created by QtCreator 2025-02-13T16:20:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TextEditor
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        explorer.cpp \
        filename.cpp \
        fontedit.cpp \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        explorer.h \
        filename.h \
        fontedit.h \
        mainwindow.h

FORMS += \
        explorer.ui \
        filename.ui \
        fontedit.ui \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    resourses/bold.png \
    resourses/clear.png \
    resourses/close.png \
    resourses/copy.png \
    resourses/create.png \
    resourses/font.png \
    resourses/fontColor.png \
    resourses/fontSize.png \
    resourses/italic.png \
    resourses/open.png \
    resourses/paste.png \
    resourses/replace.png \
    resourses/save.png \
    resourses/saveAs.png \
    resourses/search.png \
    resourses/underlined.png \
    resourses/undo.png

RESOURCES += \
    icons.qrc
