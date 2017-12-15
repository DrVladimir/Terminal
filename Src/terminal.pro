greaterThan(QT_MAJOR_VERSION, 4) {
    QT       += widgets serialport core sql
} else {
    include($$QTSERIALPORT_PROJECT_ROOT/src/serialport/qt4support/serialport.prf)
}

TARGET = terminal
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    settingsdialog.cpp \
    shortcut.cpp \
    mainhandler.cpp \
    shortcutcreator.cpp \
    connection.cpp \
    filter.cpp \
    filtercreator.cpp \
    filtereditor.cpp \
    filterinfo.cpp

HEADERS += \
    mainwindow.h \
    settingsdialog.h \
    version.h \
    shortcut.h \
    mainhandler.h \
    shortcutcreator.h \
    connection.h \
    filter.h \
    filtercreator.h \
    filtereditor.h \
    filterinfo.h

FORMS += \
    mainwindow.ui \
    settingsdialog.ui \
    shortcutcreator.ui \
    filtercreator.ui \
    filtereditor.ui

RESOURCES += \
    terminal.qrc





