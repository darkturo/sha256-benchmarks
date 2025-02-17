cmake_minimum_required(VERSION 3.10)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

find_package(gflags REQUIRED)
find_package(Folly REQUIRED)
find_package(fmt REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem system)

add_executable(wolfsha256 main.cc)

target_link_libraries(wolfsha256
	PRIVATE
	Folly::folly Folly::follybenchmark
	fmt::fmt
	Boost::filesystem Boost::system
	gflags
	wolfssl
)
