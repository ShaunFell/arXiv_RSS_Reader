DESTDIR = ./build

QT       += core gui widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG -= release
CONFIG += debug         

BUILDPATH = build

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Qt/PreferencesDialog.cpp \
    Qt/mainwindow.cpp \
    main.cpp \
    web/Reader.cpp

HEADERS += \
    DB/container.h \
    Preferences.h \
    Qt/PreferencesDialog.h \
    Qt/mainwindow.h \
    web/Reader.h

FORMS += \
    mainwindow.ui

OTHER_FILES += \
    logo.ico

RC_ICONS = icon.ico

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc


TARGET = arxiv-rss-reader

release: DESTDIR = $${BUILDPATH}/release
        debug:   DESTDIR = $${BUILDPATH}/debug

# Release directory
OBJECTS_DIR = $${DESTDIR}/.obj
MOC_DIR = $${DESTDIR}/.moc
RCC_DIR = $${DESTDIR}/.rcc
UI_DIR = $${DESTDIR}/.ui

CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT       
    message($${DEFINES})
}