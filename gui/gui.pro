QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../arithmetic_op.cpp \
    ../control_op.cpp \
    ../input_handler.cpp \
    ../memory_op.cpp \
    ../output_handler.cpp \
    ../qt_input.cpp \
    ../qt_output.cpp \
    ../uvsim.cpp \
    inputdialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../arithmetic_op.h \
    ../constants.h \
    ../control_op.h \
    ../input_handler.h \
    ../io_op.h \
    ../memory_op.h \
    ../output_handler.h \
    ../qt_input.h \
    ../qt_output.h \
    ../uvsim.h \
    inputdialog.h \
    mainwindow.h

FORMS += \
    inputdialog.ui \
    mainwindow.ui

TRANSLATIONS += \
    gui_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

INCLUDEPATH = ../

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    gui.pro.user
