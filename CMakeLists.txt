project(gtkmateview)

#define_property(CACHED_VARIABLE
#                   PROPERTY SOMETHING
#                   BRIEF_DOCS "something brief"
#                   FULL_DOCS "here more")
#set(SOMETHING true CACHE bool 'some test')
#mark_as_advanced(CLEAR SOMETHING)
OPTION(WITH_RUBY "Add ruby bindings" ON)
OPTION(WITH_PYTHON "Add python bindings" ON)

INCLUDE_DIRECTORIES(${gtkmateview_BINARY_DIR})

find_package(PkgConfig)
cmake_minimum_required(VERSION 2.6)

pkg_check_modules(GTK gtk+-2.0)
pkg_check_modules(GLIB glib-2.0)
pkg_check_modules(SOURCEVIEW gtksourceview-2.0)
pkg_check_modules(GEE gee-1.0)

# Now the variables GTKMM_INCLUDE_DIRS, GTKMM_LIBRARY_DIRS and GTKMM_LIBRARIES 
# contain what you expect 

add_subdirectory(lib)
add_subdirectory(dist)

if(WITH_RUBY)
    add_subdirectory(bindings/ruby)
endif(WITH_RUBY)