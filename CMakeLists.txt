
project(tm C)
cmake_minimum_required(VERSION 2.6)
if(POLICY CMP0011)
    cmake_policy(SET CMP0011 NEW)
endif(POLICY CMP0011)

set(CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
    ${CMAKE_MODULE_PATH})
include(MacroInstallPrefix)
include(MacroLogVar)
include(MacroDeleteInstalled)
include(MacroSetDefaultInstallDirs)
include(MacroSetBuildType)
include(MacroSystemOrLocalDep)
include(MacroOption)

macro_set_build_type()

set(pn "${PROJECT_NAME}")
set(${pn}_srcdir "${CMAKE_CURRENT_SOURCE_DIR}")
set(${pn}_builddir "${CMAKE_CURRENT_BINARY_DIR}")
string(TOUPPER "${pn}" PN)

macro_option(${PN}_ENABLE_TESTS "Compile tests." ON)

macro_option(${PN}_ENABLE_SHARED "Build shared library." ON)
macro_option(${PN}_ENABLE_STATIC "Build static library." ON)

macro_option(${PN}_USE_SYSTEM_PLAT "Use the system's version of plat." ON)
macro_option(${PN}_USE_SYSTEM_DECL "Use the system's version of decl." ON)

set(${pn}_plat_expr ">=")
set(${pn}_plat_ver "1.5")
set(${pn}_decl_expr ">=")
set(${pn}_decl_ver "1.4.1")
macro_system_or_local_dep(plat NOLIB "../plat" NOBUILD "${${pn}_plat_ver}")
macro_system_or_local_dep(decl NOLIB "../decl" NOBUILD "${${pn}_decl_ver}")
set(${pn}_pkgconfig_deps "plat ${${pn}_plat_expr} ${${pn}_plat_ver}")
foreach(${pn}_i "decl")
    set(${pn}_pkgconfig_deps "${${pn}_pkgconfig_deps}, ${${pn}_i} ${${pn}_${${pn}_i}_expr} ${${pn}_${${pn}_i}_ver}")
endforeach(${pn}_i "decl")

macro_set_default_install_dirs()

macro_install_prefix(${pn}_prefix)
macro_log_var(${pn}_prefix)

set(${pn}_VERSION_MAJOR 1)
set(${pn}_VERSION_MINOR 0)
set(${pn}_VERSION_PATCH 0)
set(${pn}_VERSION_STR "${${pn}_VERSION_MAJOR}.${${pn}_VERSION_MINOR}.${${pn}_VERSION_PATCH}")

set(${pn}_VENDOR_STR "Gavin Beatty")
set(${pn}_CONTACT_STR "Gavin Beatty <gavinbeatty@gmail.com>")
set(${pn}_HOMEPAGE_STR "http://repo.or.cz/p/tm")
set(${pn}_DESCRIPTION_STR "Plugin loading in C.")

set(${pn}_build_include_dirs
"${CMAKE_CURRENT_SOURCE_DIR}/src"
"${CMAKE_CURRENT_BINARY_DIR}/src"
${plat_INCLUDE_DIRS}
${decl_INCLUDE_DIRS}
)
set(${pn}_include_dirs "${CMAKE_INSTALL_PREFIX}/${${pn}_includedir}")
set(${pn}_export_file "${CMAKE_INSTALL_PREFIX}/${${pn}_cmakeexportdir}/LibraryExport${pn}.cmake")

configure_file("${${pn}_srcdir}/src/${pn}/config.h.in"
               "${${pn}_builddir}/src/${pn}/config.h"
               @ONLY)
set(build_include_dirs ${${pn}_build_include_dirs})
configure_file("${${pn}_srcdir}/BuildExport${pn}.cmake.in"
               "${${pn}_builddir}/BuildExport${pn}.cmake"
               @ONLY)
set(include_dirs ${${pn}_include_dirs})
set(export_file "${${pn}_export_file}")
configure_file("${${pn}_srcdir}/Export${pn}.cmake.in"
               "${${pn}_builddir}/Export${pn}.cmake"
               @ONLY)
set(description_str "${${pn}_DESCRIPTION_STR}")
set(version_str "${${pn}_VERSION_STR}")
set(homepage_str "${${pn}_HOMEPAGE_STR}")
set(libdir "${${pn}_libdir}")
set(includedir "${${pn}_includedir}")
set(pkgconfig_deps "${${pn}_pkgconfig_deps}")
configure_file("${${pn}_srcdir}/${pn}.pc.in"
               "${${pn}_builddir}/${pn}.pc"
               @ONLY)
set(name "${pn}")
string(TOUPPER "${name}" NAME)
string(REGEX REPLACE "." " " empty "${name}")
set(no_libs FALSE)
set(default_lib_type "_shared")
set(shared_libs TRUE)
set(static_libs TRUE)
set(config_header "config.h")
file(READ "cmake/MacroVersionCmp.cmake" macro_version_str)
set(deps_code "
m_req_dep(\"\${_p}\" plat NOTEXACT \"${${pn}_plat_ver}\" \"\${_p}_plat_found\")
m_req_dep(\"\${_p}\" decl NOTEXACT \"${${pn}_decl_ver}\" \"\${_p}_decl_found\")
")
configure_file("${${pn}_srcdir}/cmake/FindGeneric.cmake.in"
               "${${pn}_srcdir}/Find${pn}.cmake"
               @ONLY)


set(${pn}_SRCS
src/${pn}/${pn}.c
)
set(${pn}_HDRS
"${${pn}_builddir}/src/${pn}/config.h"
src/${pn}/${pn}.h
)

include_directories(${${pn}_build_include_dirs})

macro(${pn}_add_library _shared_static)
    string(TOUPPER "${_shared_static}" _upper)
    string(TOLOWER "${_shared_static}" _lower)
    set(${pn}_targets ${${pn}_targets} "${pn}_${_lower}")
    add_library(${pn}_${_lower} ${_upper} ${${pn}_SRCS})
    set_target_properties(${pn}_${_lower} PROPERTIES
        OUTPUT_NAME         ${pn}
        SOVERSION           "${${pn}_VERSION_STR}"
        COMPILE_DEFINITIONS "${PN}_${_upper}_LIB_BUILD=1"
        LINK_INTERFACE_LIBRARIES ""
        CLEAN_DIRECT_OUTPUT 1
    )
endmacro(${pn}_add_library _shared_static)

set(${pn}_targets)
if(${PN}_ENABLE_SHARED)
    tm_add_library(SHARED)
endif(${PN}_ENABLE_SHARED)
if(${PN}_ENABLE_STATIC)
    tm_add_library(STATIC)
endif(${PN}_ENABLE_STATIC)


export(TARGETS ${${pn}_targets}
    FILE "${${pn}_builddir}/BuildExport${pn}.cmake"
    NAMESPACE ${pn}_build_
    APPEND
)

if(${PN}_ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif(${PN}_ENABLE_TESTS)

if(NOT ${PN}_NO_INSTALL)
install(TARGETS     ${${pn}_targets}
    EXPORT                  ${pn}_export
    ARCHIVE DESTINATION     "${${pn}_libdir}"
    LIBRARY DESTINATION     "${${pn}_libdir}"
)
install(FILES           ${${pn}_HDRS}
        DESTINATION     "${${pn}_projincludedir}"
)
install(FILES           "${${pn}_builddir}/Export${pn}.cmake"
        DESTINATION     "${${pn}_cmakeexportdir}"
)
macro_delete_installed("${${pn}_cmakeexportdir}/LibraryExport${pn}-*.cmake")
install(EXPORT      ${pn}_export
    DESTINATION     "${${pn}_cmakeexportdir}"
    NAMESPACE       "${pn}_export_"
    FILE            "LibraryExport${pn}.cmake"
)
install(FILES           "${${pn}_srcdir}/Find${pn}.cmake"
        DESTINATION     "${${pn}_cmakefindpkgdir}"
)
install(FILES           "${${pn}_builddir}/${pn}.pc"
        DESTINATION     "${${pn}_pkgconfigdir}"
)
endif(NOT ${PN}_NO_INSTALL)


