FILE (GLOB srcs *.vala)
source_group(vala_files FILES srcs)

#        sh "valac -C --library gtkmateview --pkg gtksourceview-2.0 --pkg libxml-2.0 --pkg gee-1.0 --pkg gtksourceview-2.0 --vapidir=./../vapi/ --pkg=oniguruma *.vala"

#add_custom_command(cfiles test)
#                    message(STATUS
#                            "generating C sources")

#add_custom_command(OUTPUT ../dist/gtkmateview.c
#    COMMAND valac -C --library gtkmateview --pkg gtksourceview-2.0 --pkg libxml-2.0 --pkg gee-1.0 --pkg gtksourceview-2.0 --vapidir=./../vapi/ --pkg=oniguruma *.vala
#)

#ADD_CUSTOM_COMMAND(
#   OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/dist/gtkmateview.c
#   COMMAND valac -C --library gtkmateview --pkg gtksourceview-2.0 --pkg libxml-2.0 --pkg gee-1.0 --pkg gtksourceview-2.0 --vapidir=./../vapi/ --pkg=oniguruma ${srcs}
#   DEPENDS generate ${srcs}
#   )

ADD_CUSTOM_COMMAND(
   OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/dist/gtkmateview.c
   COMMAND valac -C --library gtkmateview 
    --pkg gtksourceview-2.0 --pkg libxml-2.0 --pkg gee-1.0 --pkg gtksourceview-2.0 
    --vapidir=./../vapi/ --pkg=oniguruma ${srcs} -d ../dist
   #DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/dist/gtkmateview.vala
   )


# ADD_CUSTOM_COMMAND(
#   OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/../dist/gtkmateview.c
#   COMMAND valac -C --library gtkmateview --pkg gtksourceview-2.0 --pkg libxml-2.0 --pkg gee-1.0 --pkg gtksourceview-2.0 --vapidir=./../vapi/ --pkg=oniguruma ${srcs}
#   DEPENDS generate ${srcs}
#   )

ADD_CUSTOM_TARGET(generate_c 
                  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/dist/gtkmateview.c
#                  SOURCES ../gtkmateview.vala
)
#ADD_CUSTOM_TARGET(generate_c SOURCES gtkmateview.vala)


# ADD_CUSTOM_COMMAND(
#    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/../dist/gtkmateview.c
#    COMMAND valac -C --library gtkmateview --pkg gtksourceview-2.0 --pkg libxml-2.0 --pkg gee-1.0 --pkg gtksourceview-2.0 --vapidir=./../vapi/ --pkg=oniguruma ${srcs}
#    DEPENDS generate ${srcs}
#    )


#ADD_CUSTOM_TARGET(driver ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/dist/gtkmateview.c)
#ADD_CUSTOM_TARGET(driver ALL DEPENDS gtkmateview.c)

#add_custom_target(gtkmatec ALL DEPENDS ../dist/gtkmateview.c)
                    
#                     COMMAND command1 [ARGS] [args1...]
#                     [COMMAND command2 [ARGS] [args2...] ...]
#                     [MAIN_DEPENDENCY depend]
#                     [DEPENDS [depends...]]
#                     [IMPLICIT_DEPENDS <lang1> depend1 ...]
#                     [WORKING_DIRECTORY dir]
#                     [COMMENT comment] [VERBATIM] [APPEND])#
#                      
#           
# link_directories(
#     ${GTK_LIBRARY_DIRS}
#     ${GLIB_LIBRARY_DIRS}
#     ${SOURCEVIEW_LIBRARY_DIRS}
#     ${GEE_LIBRARY_DIRS}
#     )
#
# include_directories(
#     ${GTK_INCLUDE_DIRS}
#     ${GLIB_INCLUDE_DIRS}
#     ${SOURCEVIEW_INCLUDE_DIRS}
#     ${GEE_INCLUDE_DIRS})
#
#
#
# add_library(gtkmateview SHARED ${srcs})
#
# target_link_libraries(gtkmateview 
#     ${GTK_LIBRARIES}  )