if(ENABLE_XSLT)
    IF(NOT WIN32)
#        pkg_check_modules(LIBXSLT REQUIRED libxslt>=1.1.7)
        set(DEB_PACKAGE_DEPENDS "${DEB_PACKAGE_DEPENDS}, libxslt1.1 (>= 1.1.24-2ubuntu2)")
    ELSE(NOT WIN32)
        ## Pkg-config under cygwin gives to cmake .a lib and we need .lib for Visual Studio projects. 
        find_path(LIB_XSLT_PATH libxslt.lib ${WINLIB_LIB_PATH})
        find_path(INC_XSLT xslt.h ${WINLIB_INC_PATH} ${WINLIB_INC_PATH}/libxslt)
        IF(NOT LIB_XSLT_PATH)
            MESSAGE(FATAL_ERROR "XSLT lib not found.  Install it to be able to compile owb.")
        ELSE(NOT LIB_XSLT_PATH)
            find_file(LIBXSLT ${LIB_XSLT_PATH}/libxslt.lib)
        ENDIF(NOT LIB_XSLT_PATH)
    ENDIF(NOT WIN32)
endif(ENABLE_XSLT)
