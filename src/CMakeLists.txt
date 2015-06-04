#
#
# compiling/installing sources for sockaddrutil

set ( sockaddrutil_srcs
      sockaddr_util.c
)

add_library ( sockaddrutil SHARED ${sockaddrutil_srcs} )
target_include_directories ( sockaddrutil PUBLIC ../include )
target_include_directories ( sockaddrutil PRIVATE ../src )

install ( TARGETS sockaddrutil
          LIBRARY DESTINATION lib
          ARCHIVE DESTINATION lib
          RUNTIME DESTINATION bin)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)
if (coveralls)
    include(Coveralls)
    coveralls_turn_on_coverage()

    set(COVERAGE_SRCS "")
    foreach (S ${sockaddrutil_srcs})
      get_filename_component(S_ABS ${S} ABSOLUTE)
      list (APPEND COVERAGE_SRCS ${S_ABS})
    endforeach()

    # Create the coveralls target.
    coveralls_setup(
        "${COVERAGE_SRCS}"
        ${coveralls_send}                 # If we should upload.
    )

    #add_dependencies(coveralls, all)
endif()
