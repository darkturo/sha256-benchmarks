cmake_minimum_required(VERSION 3.10)

function(build_benchmark Name Library)
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

    target_link_libraries(${Name}
            PRIVATE
            Folly::folly Folly::follybenchmark
            fmt::fmt
            Boost::filesystem Boost::system
            gflags
            ${Library}
            )
endfunction()

