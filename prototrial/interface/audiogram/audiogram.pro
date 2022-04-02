QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    audiogram.cpp

HEADERS += \
    audiogram.h

FORMS += \
    audiogram.ui

linux {
    INCLUDEPATH += /usr/include/qwt
    LIBS += -lqwt
}

win32 {
    INCLUDEPATH += C:\Qwt-6.1.6\include
    LIBS += -LC:\Qwt-6.1.6\lib -lqwt
}

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
