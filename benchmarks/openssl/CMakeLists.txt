cmake_minimum_required(VERSION 3.10)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

find_package(gflags REQUIRED)
find_package(Folly REQUIRED)
find_package(fmt REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem system)

add_executable(openssl-sha256-bench main.cc)

if (VERBOSE)
	add_compile_definitions(openssl-sha256-bench ENABLE_STDOUT_DEBUG=1)
endif()

target_link_libraries(openssl-sha256-bench
	PRIVATE
	Folly::folly Folly::follybenchmark
	fmt::fmt
	Boost::filesystem Boost::system
	gflags
	ssl crypto
)
