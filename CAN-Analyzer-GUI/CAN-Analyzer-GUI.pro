QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    availableboards.cpp \
    baudrateconfigurator.cpp \
    communication.cpp \
    filter.cpp \
    filter_1id32_1mask32.cpp \
    filter_2id16_2mask16.cpp \
    filter_2ids32_nomask.cpp \
    filter_4ids16_nomask.cpp \
    main.cpp \
    mainwindow.cpp \
    multibasenumber.cpp \
    receivedatatable.cpp \
    systemfilters.cpp

HEADERS += \
    ApplicationConfigurations.h \
    availableboards.h \
    baudrateconfigurator.h \
    common.h \
    communication.h \
    filter.h \
    filter_1id32_1mask32.h \
    filter_2id16_2mask16.h \
    filter_2ids32_nomask.h \
    filter_4ids16_nomask.h \
    mainwindow.h \
    multibasenumber.h \
    receivedatatable.h \
    systemfilters.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
