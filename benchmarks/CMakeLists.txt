cmake_minimum_required(VERSION 3.10)
project(sha256-benchmarks VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(VERBOSE "Print status during the benchmark. OBS this is just for troubleshooting as it will impact the stats" OFF)

file(GLOB DIRS LIST_DIRECTORIES true "${CMAKE_CURRENT_SOURCE_DIR}/*") 
foreach(benchmark_dir ${DIRS})
    if(IS_DIRECTORY ${benchmark_dir})
	    if(EXISTS ${benchmark_dir}/CMakeLists.txt)
		    add_subdirectory(${benchmark_dir})
	    endif()
    endif()
endforeach()
