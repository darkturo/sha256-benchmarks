cmake_minimum_required(VERSION 3.10)

# build_benchmark(Name [LIBRARIES ...])
function(build_benchmark Name)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

    # common stuff
    find_package(gflags REQUIRED)
    find_package(Folly REQUIRED)
    find_package(fmt REQUIRED)
    find_package(Boost REQUIRED COMPONENTS filesystem system)

    add_executable(${Name} main.cc)

    if (VERBOSE)
        add_compile_definitions(${Name} ENABLE_STDOUT_DEBUG=1)
    endif()

    # Weird contraption I did to look similar to other cmake functions
    set(LIBS)
    set(COLLECT_LIBS OFF)
    message(STATUS "LIBS: ${ARGN}")
    foreach(arg IN LISTS ARGN)
        if (COLLECT_LIBS)
            list(APPEND LIBS ${arg})
        elseif (${arg} STREQUAL "LIBRARIES")
            set(COLLECT_LIBS ON)
        endif()
    endforeach()
    message(STATUS "LIBS: ${LIBS}")

    target_link_libraries(${Name}
            PRIVATE
            Folly::folly Folly::follybenchmark
            fmt::fmt
            Boost::filesystem Boost::system
            gflags
            ${LIBS}
    )

endfunction()

