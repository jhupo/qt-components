INCLUDEPATH             += $$top_srcdir/components/

win32{
QMAKE_CXXFLAGS          += /MP
LIBS                    += $$top_builddir/bin/components.lib
}else{
LIBS                    += $$top_builddir/bin/components.so
}
