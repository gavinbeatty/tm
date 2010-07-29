project(tm_tests C)
cmake_minimum_required(VERSION 2.6)

include("${tm_BINARY_DIR}/BuildExporttm.cmake")
include_directories(${tm_build_INCLUDE_DIRS})

function(tm_test_libtype__ name_ libtype_)
  add_executable("${name_}" ${ARGN})
  target_link_libraries("${name_}" "tm_build_tm_${libtype_}")
  add_test("${name_}" "${name_}")
endfunction(tm_test_libtype__)

function(tm_test name_)
  tm_test_libtype__("${name_}_static" "static" ${ARGN})
  tm_test_libtype__("${name_}_shared" "shared" ${ARGN})
endfunction(tm_test)

tm_test(test_monotonic monotonic.c)

