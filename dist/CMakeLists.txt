FILE (GLOB vallasrcs ${CMAKE_HOME_DIRECTORY}/lib/*.vala)
#FIXME: think this is better but doesn't work
#FILE (GLOB vallasrcs RELATIVE ../lib *)

# generate a list of .c and .h files the vala files will generate
#LIST(srcs)
#LIST(headers)
#set(srcs)
foreach(cfile ${vallasrcs})
    STRING(REGEX REPLACE "(.*).vala" "\\1" name "${cfile}" )
    #FIXME: we need a last match here or lib from higher path will be replaced, too
    STRING(REGEX REPLACE "lib" "dist" name "${name}" )
     #STRING(REGEX REPLACE ".*catch: ([^ ]+).*" "\\1" result "${test}" )
    LIST(APPEND v_srcs "${name}.c")
    LIST(APPEND v_headers "${name}.h")
endforeach()

FILE (GLOB srcs *.c)

link_directories(
    ${GTK_LIBRARY_DIRS}
    ${GLIB_LIBRARY_DIRS}
    ${SOURCEVIEW_LIBRARY_DIRS}
    ${GEE_LIBRARY_DIRS}
    )

include_directories(
    ${GTK_INCLUDE_DIRS}
    ${GLIB_INCLUDE_DIRS}
    ${SOURCEVIEW_INCLUDE_DIRS}
    ${GEE_INCLUDE_DIRS}
    ${CMAKE_CURRENT_BINARY_DIR})

foreach(src ${srcs})
    SET_SOURCE_FILES_PROPERTIES(${CMAKE_CURRENT_BINARY_DIR}/dist/${src} PROPERTIES GENERATED 1)
endforeach(src)


add_library(gtkmateview SHARED ${srcs})

#ADD_DEPENDENCIES(gtkmateview generate_c)
ADD_DEPENDENCIES(gtkmateview ${CMAKE_CURRENT_SOURCE_DIR}/dist/gtkmateview.c)

target_link_libraries(gtkmateview 
    ${GTK_LIBRARIES}  )

function(DO_CLEANUP)
    message('juhu')
    foreach(cfile §{srcs})
        message('foreach ${cfile}')
    endforeach(cfile)
    #file(REMOVE test) 
    #file(REMOVE bla)
endfunction(DO_CLEANUP)

ADD_CUSTOM_TARGET(clean_c)# file(REMOVE ${srcs}) file(REMOVE ${headers}))

foreach(cfile ${v_srcs})
    #FIXME: how to do this platform independend ????
    add_custom_command(TARGET clean_c PRE_BUILD COMMAND rm ${cfile})
endforeach()

foreach(cfile ${v_headers})
    #FIXME: how to do this platform independend ????
    add_custom_command(TARGET clean_c PRE_BUILD COMMAND rm ${cfile})
endforeach()

#add_custom_command(TARGET clean_c
#                    PRE_BUILD
#                    DO_CLEANUP)

