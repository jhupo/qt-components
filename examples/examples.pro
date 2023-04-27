include($$top_srcdir/library.pri)
include($$top_srcdir/components.pri)

QT                      +=      core gui widgets svg xml network
TARGET                   =      examples
TEMPLATE                 =      app
DESTDIR                  =      $$top_builddir/bin
MOC_DIR                 +=      $$top_builddir/examples/moc
UI_DIR                  +=      $$top_builddir/examples/uic
RCC_DIR                 +=      $$top_builddir/examples/rcc
OBJECTS_DIR             +=      $$top_builddir/examples/obj
CONFIG                  -=      debug_and_release
DEFINES                 +=
QMAKE_CXXFLAGS_RELEASE   =      $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
QMAKE_LFLAGS_RELEASE     =      $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO

SRC_DIR = $$top_srcdir/examples

for(var, SRC_DIR){
    SOURCES         += $$files($$join(var, , , /*.cpp) , true)
    SOURCES         += $$files($$join(var, , , /*.c)   , true)
    HEADERS         += $$files($$join(var, , , /*.h)   , true)
    FORMS           += $$files($$join(var, , , /*.ui)  , true)
    RESOURCES       += $$files($$join(var, , , /*.qrc) , true)
    TRANSLATIONS    += $$files($$join(var, , , /*.ts)  , true)
}
