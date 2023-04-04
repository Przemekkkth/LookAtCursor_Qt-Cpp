greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

OBJECTS_DIR = obj
MOC_DIR     = moc
DESTDIR     = bin

SOURCES += \
    src/gamescene.cpp \
    src/main.cpp \
    src/pixmapmanager.cpp \
    src/view.cpp

HEADERS += \
    src/circle.h \
    src/gamescene.h \
    src/pixmapmanager.h \
    src/resource_holder.h \
    src/unit.h \
    src/utils.h \
    src/view.h

RESOURCES += \
    resource.qrc
