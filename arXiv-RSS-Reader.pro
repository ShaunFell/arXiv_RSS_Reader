DESTDIR = ./build

QT += core gui widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG -= debug
CONFIG += release

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
HOME = $$system(echo $HOME)
target.path = $${HOME}/.bin
icons.path = $${HOME}/.local/share/icons
icons.files = ./images/arxiv_rss_reader.ico

desktop.path = $${HOME}/.local/share/applications
desktop.files = $$OUT_PWD/arxiv-rss-reader.desktop

# automatically generate .desktop
gen_desktop.target = arxiv-rss-reader.desktop
gen_desktop.commands = echo "[Desktop Entry]" >> arxiv-rss-reader.desktop && \
                   echo "Version=1.0" >> arxiv-rss-reader.desktop && \
                   echo "Type=Application" >> arxiv-rss-reader.desktop && \
                   echo "Terminal=false" >> arxiv-rss-reader.desktop && \
                   echo "Exec="$${HOME}"/.bin/arxiv_rss_reader" >> arxiv-rss-reader.desktop && \
                   echo "Icon="$${HOME}"/.local/share/icons/arxiv_rss_reader.ico" >> arxiv-rss-reader.desktop && \
                   echo "Name=Arxiv RSS Reader" >> arxiv-rss-reader.desktop
gen_desktop.CONFIG += no_link

#install targets
INSTALLS += target icons desktop

#add .desktop build to app build
QMAKE_EXTRA_TARGETS += gen_desktop
PRE_TARGETDEPS += arxiv-rss-reader.desktop


RESOURCES += \
    resources.qrc


TARGET = arxiv_rss_reader

release: DESTDIR = $${BUILDPATH}/release
        debug:   DESTDIR = $${BUILDPATH}/debug

# Release directory
OBJECTS_DIR = $${DESTDIR}/.obj
MOC_DIR = $${DESTDIR}/.moc
RCC_DIR = $${DESTDIR}/.rcc
UI_DIR = $${DESTDIR}/.ui

CONFIG(release, debug|release) {
    DEFINES += QT_NO_DEBUG_OUTPUT
    message($$system(echo $HOME))
}
