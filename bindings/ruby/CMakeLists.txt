# ADD_CUSTOM_COMMAND(
#    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/dist/gtkmateview.c
#    COMMAND valac -C --library gtkmateview 
#     --pkg gtksourceview-2.0 --pkg libxml-2.0 --pkg gee-1.0 --pkg gtksourceview-2.0 
#     --vapidir=./../vapi/ --pkg=oniguruma ${srcs} -d ../dist
#    #DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/dist/gtkmateview.vala
#    )

#pkg_check_modules(RUBY ruby)

FIND_PACKAGE(Ruby REQUIRED)
#include(FindRuby)
#FindRuby()

if(RUBY_INCLUDE_PATH)


    find_program(VALAR valar PATHS ${CMAKE_HOME_DIRECTORY}/../valar/bin/)
    if(NOT VALAR)
        find_path(VALAR valar ${CMAKE_HOME_DIRECTORY}/../valar/bin/)
    endif(NOT VALAR)
    message("Use valar ${VALAR}")
    #ruby ${CMAKE_HOME_DIRECTORY}/../valar/bin/valar 
    ADD_CUSTOM_COMMAND(
       OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/gtkmateview_rb.c
       COMMAND ${VALAR}
           ${CMAKE_HOME_DIRECTORY}/lib/gtkmateview.vapi 
           --deps="gtk+-2.0,oniguruma,gtksourceview-2.0" 
           --vapidirs=${CMAKE_HOME_DIRECTORY}/vapi/oniguruma.vapi
           --output-dir=${CMAKE_CURRENT_BINARY_DIR}
       )

    include_directories(
        ${RUBY_INCLUDE_PATH}
    ${GTK_INCLUDE_DIRS}
    ${SOURCEVIEW_INCLUDE_DIRS}
    ${GEE_INCLUDE_DIRS}
    ${CMAKE_HOME_DIRECTORY}/dist
        )
    link_directories(
        ${RUBY_LIBRARY}
    ${GTK_LIBRARY_DIRS}
        ${SOURCEVIEW_LIBRARY_DIRS}
    ${GEE_LIBRARY_DIRS}
            )
#link_directories(
#    ${GTK_LIBRARY_DIRS}
#    ${GLIB_LIBRARY_DIRS}
#    ${SOURCEVIEW_LIBRARY_DIRS}
#    ${GEE_LIBRARY_DIRS}
#    )

#include_directories(
#    ${GTK_INCLUDE_DIRS}
#    ${GLIB_INCLUDE_DIRS}
#    ${SOURCEVIEW_INCLUDE_DIRS}
#    ${GEE_INCLUDE_DIRS}
#    ${CMAKE_CURRENT_BINARY_DIR})



    add_library(gtkmateview_rb SHARED 
                ${CMAKE_CURRENT_BINARY_DIR}/gtkmateview_rb.c)


    # ADD_CUSTOM_COMMAND(
    #   OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/../dist/gtkmateview.c
    #   COMMAND valac -C --library gtkmateview --pkg gtksourceview-2.0 --pkg libxml-2.0 --pkg gee-1.0 --pkg gtksourceview-2.0 --vapidir=./../vapi/ --pkg=oniguruma ${srcs}
    #   DEPENDS generate ${srcs}
    #   )

    ADD_CUSTOM_TARGET(bindings-ruby
                      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/dist/gtkmateview.c
    #                  SOURCES ../gtkmateview.vala
    )
endif(RUBY_INCLUDE_PATH)