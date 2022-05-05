QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    checkerbutton.cpp \
    clientwindow.cpp \
    main.cpp \
    mydialog.cpp \
    mydialog1.cpp \
    networkdata.cpp \
    networkserver.cpp \
    networksocket.cpp \
    rank.cpp \
    widget.cpp

HEADERS += \
    checkerbutton.h \
    clientwindow.h \
    mydialog.h \
    mydialog1.h \
    networkdata.h \
    networkserver.h \
    networksocket.h \
    rank.h \
    widget.h

FORMS += \
    clientwindow.ui \
    mydialog.ui \
    rank.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc

RC_ICONS=mapp.ico
