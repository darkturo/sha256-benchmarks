cmake_minimum_required(VERSION 3.10)

set(RUST_PROJECT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(RUST_BINARY "${RUST_PROJECT_PATH}/target/release/rust-sha2-bench")

add_custom_target(rust-sha2-bench ALL
        COMMAND cargo build --release
        WORKING_DIRECTORY ${RUST_PROJECT_PATH}
)

add_custom_command(TARGET rust-sha2-bench POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${RUST_BINARY} ${RUST_PROJECT_PATH}
)