if(USE_FILESYSTEM_ACCESS STREQUAL "GLIB")
    pkg_check_modules(GLIB REQUIRED glib-2.0>=2.0)
    set(FILESYSTEM_INCLUDE_DIRS ${GLIB_INCLUDE_DIRS})
    set(FILESYSTEM_LIBRARIES ${GLIB_LIBRARIES})

    set(USE_FILESYSTEM_ACCESS_GLIB TRUE)
    mark_as_advanced(USE_FILESYSTEM_ACCESS_GLIB)
    set(DEB_PACKAGE_DEPENDS "${DEB_PACKAGE_DEPENDS}, libglib2.0-0 (>= 2.22.3-0ubuntu1)")
endif(USE_FILESYSTEM_ACCESS STREQUAL "GLIB")

if(USE_FILESYSTEM_ACCESS STREQUAL "POSIX")
    set(USE_FILESYSTEM_ACCESS_POSIX TRUE)
    mark_as_advanced(USE_FILESYSTEM_ACCESS_POSIX)
endif(USE_FILESYSTEM_ACCESS STREQUAL "POSIX")

if(USE_FILESYSTEM_ACCESS STREQUAL "QT")
    pkg_check_modules(QTFILE REQUIRED QtCore)
    set(FILESYSTEM_INCLUDE_DIRS ${QTFILE_INCLUDE_DIRS})
    set(FILESYSTEM_LIBRARIES ${QTFILE_LIBRARIES})

    set(USE_FILESYSTEM_ACCESS_QT TRUE)
    mark_as_advanced(USE_FILESYSTEM_ACCESS_QT)
    set(DEB_PACKAGE_DEPENDS "${DEB_PACKAGE_DEPENDS}, libqtcore4 (>= 4.5.3really4.5.2-0ubuntu1)")
endif(USE_FILESYSTEM_ACCESS STREQUAL "QT")
