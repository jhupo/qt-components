INCLUDEPATH             += $$top_srcdir/components/

win32{
QMAKE_CXXFLAGS          += /MP
LIBS                    += $$top_builddir/builds/bin/components.lib
}else{
LIBS                    += $$top_builddir/builds/bin/components.so
}
