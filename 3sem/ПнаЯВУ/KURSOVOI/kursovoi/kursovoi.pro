QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    apartment.cpp \
    authorization.cpp \
    client.cpp \
    house.cpp \
    main.cpp \
    mainwindow.cpp \
    makedeal.cpp \
    menudatawidget.cpp \
    objectadding.cpp \
    objectoverview.cpp \
    office.cpp \
    realestate.cpp \
    realestatebase.cpp \
    registration.cpp

HEADERS += \
    apartment.h \
    authorization.h \
    client.h \
    defines.h \
    house.h \
    mainwindow.h \
    makedeal.h \
    menudatawidget.h \
    objectadding.h \
    objectoverview.h \
    office.h \
    realestate.h \
    realestatebase.h \
    registration.h

FORMS += \
    authorization.ui \
    mainwindow.ui \
    makedeal.ui \
    menudatawidget.ui \
    objectadding.ui \
    objectoverview.ui \
    realestatebase.ui \
    registration.ui

win32:RC_FILE = D:\BSUIR\bsuirLabs\3sem\ПнаЯВУ\KURSOVOI\build-kursovoi-Desktop_Qt_6_2_4_MinGW_64_bit-Debug\img\icon.rc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc
