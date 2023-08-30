INCLUDEPATH             += $$top_srcdir/components/

win32{
    QMAKE_CXXFLAGS          += /MP
    LIBS                    += $$top_builddir/bin/components.lib
}else{
    unix:!mac{
        LIBS                    += $$top_builddir/bin/libcomponents.so
    }else{
        LIBS                    += $$top_builddir/bin/libcomponents.dylib
    }
}

