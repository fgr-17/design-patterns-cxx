set(SRC_DIR src)

find_program(CPPLINT_EXECUTABLE NAMES cpplint)
if (NOT CPPLINT_EXECUTABLE)
    message(FATAL_ERROR "cpplint not found. Please install it.")
endif()

file(GLOB_RECURSE ALL_SOURCE_FILES
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/*.h"
)

add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/cpplint.txt
    COMMAND ${CPPLINT_EXECUTABLE} ${ALL_SOURCE_FILES}
    COMMAND ${CMAKE_COMMAND} -E echo "cpplint finished" > ${CMAKE_BINARY_DIR}/cpplint.txt
    COMMENT "Running cpplint..."
    VERBATIM
)

add_custom_target(
    run_cpplint ALL
    DEPENDS ${CMAKE_BINARY_DIR}/cpplint.txt
)
