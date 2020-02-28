##################################################
# Add definitions.                               #
##################################################
if(ENABLE_3D_CANVAS)
    add_definitions(-DENABLE_3D_CANVAS)
endif(ENABLE_3D_CANVAS)

if(ENABLE_3D_RENDERING)
    add_definitions(-DENABLE_3D_RENDERING)
    add_definitions(-DWTF_USE_ACCELERATED_COMPOSITING=1)
endif(ENABLE_3D_RENDERING)

if(ENABLE_BLOB)
    add_definitions(-DENABLE_BLOB=1)
endif(ENABLE_BLOB)

if(ENABLE_FILE_SYSTEM)
    add_definitions(-DENABLE_FILE_SYSTEM=1)
endif(ENABLE_FILE_SYSTEM)

if(ENABLE_DASHBOARD_SUPPORT)
    add_definitions(-DENABLE_DASHBOARD_SUPPORT=1)
endif(ENABLE_DASHBOARD_SUPPORT)

if(ENABLE_SQL_DATABASE)
    add_definitions(-DENABLE_SQL_DATABASE=1)
    set(DATABASE "-DENABLE_SQL_DATABASE")
else(ENABLE_SQL_DATABASE)
    add_definitions(-DENABLE_SQL_DATABASE=0)
endif(ENABLE_SQL_DATABASE)

if(ENABLE_DATAGRID)
    add_definitions(-DENABLE_DATAGRID=1)
endif(ENABLE_DATAGRID)

if(ENABLE_ICONDATABASE)
    add_definitions(-DENABLE_ICONDATABASE=1)
    set(ICONDATABASE "-DENABLE_ICONDATABASE")
else(ENABLE_ICONDATABASE)
    add_definitions(-DENABLE_ICONDATABASE=0)
endif(ENABLE_ICONDATABASE)

if(ENABLE_INDEXED_DATABASE)
    add_definitions(-DENABLE_INDEXED_DATABASE=1)
endif(ENABLE_INDEXED_DATABASE)

if(ENABLE_DOM_STORAGE)
    add_definitions(-DENABLE_DOM_STORAGE=1)
endif(ENABLE_DOM_STORAGE)

if(ENABLE_OFFLINE_WEB_APPLICATIONS)
    add_definitions(-DENABLE_OFFLINE_WEB_APPLICATIONS=1)
endif(ENABLE_OFFLINE_WEB_APPLICATIONS)

if(ENABLE_OFFLINE_DYNAMIC_ENTRIES)
    add_definitions(-DAPPLICATION_CACHE_DYNAMIC_ENTRIES=1)
endif(ENABLE_OFFLINE_DYNAMIC_ENTRIES)

if(ENABLE_INSPECTOR)
    add_definitions(-DENABLE_INSPECTOR=1)
    add_definitions(-DENABLE_JAVASCRIPT_DEBUGGER=1)
else(ENABLE_INSPECTOR)
    add_definitions(-DENABLE_INSPECTOR=0)
    add_definitions(-DENABLE_JAVASCRIPT_DEBUGGER=0)
endif(ENABLE_INSPECTOR)

if(ENABLE_FILE_READER)
    add_definitions(-DENABLE_FILE_READER=1)
endif(ENABLE_FILE_READER)

if(ENABLE_FILE_WRITER)
    add_definitions(-DENABLE_FILE_WRITER=1)
endif(ENABLE_FILE_WRITER)

if(ENABLE_GEOLOCATION)
    add_definitions(-DENABLE_GEOLOCATION=1)
    add_definitions(-DENABLE_CLIENT_BASED_GEOLOCATION=1)
endif(ENABLE_GEOLOCATION)

if(ENABLE_DEVICE_ORIENTATION)
    add_definitions(-DENABLE_DEVICE_ORIENTATION=1)
endif(ENABLE_DEVICE_ORIENTATION)

if(ENABLE_MATHML)
    add_definitions(-DENABLE_MATHML=1)
endif(ENABLE_MATHML)

if(ENABLE_NOTIFICATIONS)
    add_definitions(-DENABLE_NOTIFICATIONS=1)
endif(ENABLE_NOTIFICATIONS)

if(ENABLE_EVENTSOURCE)
    add_definitions(-DENABLE_EVENTSOURCE=1)
else(ENABLE_EVENTSOURCE)
    add_definitions(-DENABLE_EVENTSOURCE=0)
endif(ENABLE_EVENTSOURCE)

if(ENABLE_RUBY)
    add_definitions(-DENABLE_RUBY=1)
endif(ENABLE_RUBY)

if(ENABLE_SANDBOX)
    add_definitions(-DENABLE_SANDBOX=1)
endif(ENABLE_SANDBOX)

if(ENABLE_TOUCH_EVENTS)
    add_definitions(-DENABLE_TOUCH_EVENTS=1)
endif(ENABLE_TOUCH_EVENTS)

if(ENABLE_VIDEO)
    add_definitions(-DENABLE_VIDEO=1)
endif(ENABLE_VIDEO)

if(ENABLE_WEB_SOCKETS)
    add_definitions(-DENABLE_WEB_SOCKETS=1)
else(ENABLE_WEB_SOCKETS)
    add_definitions(-DENABLE_WEB_SOCKETS=0)
endif(ENABLE_WEB_SOCKETS)

if(ENABLE_WML)
    add_definitions(-DENABLE_WML=1)
endif(ENABLE_WML)

if(ENABLE_WORKERS)
    add_definitions(-DENABLE_WORKERS=1)
    if(ENABLE_SHARED_WORKERS)
        add_definitions(-DENABLE_SHARED_WORKERS=1)
    endif(ENABLE_SHARED_WORKERS)
endif(ENABLE_WORKERS)

if(ENABLE_XHTMLMP)
    add_definitions(-DENABLE_XHTMLMP)
    if(ENABLE_WCSS)
        add_definitions(-DENABLE_WCSS)
    endif(ENABLE_WCSS)
endif(ENABLE_XHTMLMP)

if(ENABLE_XPATH)
    add_definitions(-DENABLE_XPATH=1)
endif(ENABLE_XPATH)

if(ENABLE_XSLT)
    add_definitions(-DENABLE_XSLT=1)
endif(ENABLE_XSLT)

if(HAS_VIDEO)
    if(USE_VIDEO_GSTREAMER)
        add_definitions(-DWTF_USE_VIDEO_GSTREAMER=1)
        add_definitions(-DWTF_USE_GSTREAMER=1)
    elseif(USE_VIDEO_NONE)
        add_definitions(-DWTF_USE_VIDEO_NONE=1)
    elseif(USE_VIDEO_PHONON)
        add_definitions(-DWTF_USE_VIDEO_PHONON=1)
    elseif(USE_VIDEO_QT)
        add_definitions(-DWTF_USE_VIDEO_QT=1)
    endif(USE_VIDEO_GSTREAMER)
endif(HAS_VIDEO)

if(ENABLE_TESTS)
    add_definitions(-DENABLE_TESTS=1)
endif(ENABLE_TESTS)

add_definitions(-DENABLE_ANIMATION_API=1 -DENABLE_CHANNEL_MESSAGING=1 -DENABLE_DATALIST_ELEMENT=1 -DENABLE_DATA_TRANSFER_ITEMS=0 -DENABLE_DETAILS_ELEMENT=1 -DENABLE_IFRAME_SEAMLESS=1 -DENABLE_INPUT_TYPE_COLOR=1 -DENABLE_INPUT_TYPE_DATE=1 -DENABLE_INPUT_TYPE_DATETIME_INCOMPLETE=1 -DENABLE_INPUT_TYPE_DATETIMELOCAL=1 -DENABLE_INPUT_TYPE_MONTH=1 -DENABLE_INPUT_TYPE_WEEK=1 -DENABLE_INPUT_TYPE_TIME=1 -DENABLE_DATE_AND_TIME_INPUT_TYPES=1 -DENABLE_LEGACY_NOTIFICATIONS=1 -DENABLE_MEDIA_SOURCE=0 -DENABLE_MEDIA_STATISTICS=1 -DENABLE_METER_ELEMENT=1 -DENABLE_PROGRESS_ELEMENT=1 -DENABLE_STYLE_SCOPED=1 -DENABLE_VIDEO_TRACK=1 -DENABLE_VIEW_MODE_CSS_MEDIA=1 -DENABLE_POINTER_LOCK=1 -DENABLE_PAGE_VISIBILITY_API=1 -DENABLE_REQUEST_ANIMATION_FRAME=0)


add_definitions("-DBUILDING_WebCore=1")

##################################################
# Add Compiler flags.                            #
##################################################

link_directories(${LIBRARY_OUTPUT_PATH})

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-strict-aliasing")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing")
    if(NOT ENABLE_DEBUG)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
    endif(NOT ENABLE_DEBUG)

if(APPLE)
    set(WEBKKIT_LD_FLAGS webcore;jsc;wtf)
else(APPLE)
    set(WEBKKIT_LD_FLAGS -Wl,-whole-archive jsc -Wl,-no-whole-archive webcore;wtf)
endif(APPLE)
else(CMAKE_COMPILER_IS_GNUCXX)
    message(STATUS "Flag for Windows compiler is not implemented")
endif(CMAKE_COMPILER_IS_GNUCXX)

if(NOT IGNORE_CUSTOMER)
  include(Customer/AddCustomerWebCoreCompilerFlags OPTIONAL)
endif(NOT IGNORE_CUSTOMER)
include(AddCEHTMLCompilerFlags OPTIONAL)
include(AddDAECompilerFlags OPTIONAL)
include(AddJSAddOnsCompilerFlags OPTIONAL)
include(AddOrigynSuiteCompilerFlags OPTIONAL)
include(AddWidgetEngineCompilerFlags OPTIONAL)
