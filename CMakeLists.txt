
cmake_minimum_required(VERSION 3.18)

project(CXX_PROJECT)
cmake_policy(SET CMP0135 NEW)
cmake_policy(SET CMP0167 NEW)
### C++
enable_language(CXX)
set(CMAKE_CXX_STANDARD 23 CACHE STRING "C++ standard required for build")
set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE BOOL "is C++ stndard a requirement")
set(CMAKE_CXX_EXTENSIONS OFF CACHE BOOL "enable/disable compiler specific extensions")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Wfatal-errors")

set(CMAKE_CXX_CLANG_TIDY "clang-tidy")
set(CMAKE_CXX_CLANG_FORMAT "clang-format")
# set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE "iwyu")

message("CMAKE_CXX_COMPILER: " ${CMAKE_CXX_COMPILER})

set(SRC_DIR src)

file(GLOB_RECURSE ALL_SOURCE_FILES 
    ${CMAKE_SOURCE_DIR}/src/*.cpp 
    ${CMAKE_SOURCE_DIR}/src/*.c
    ${CMAKE_SOURCE_DIR}/src/*.h
)

add_custom_target(fix
    COMMAND ${CMAKE_SOURCE_DIR}/scripts/format-modified.sh
    COMMENT "Running clang-format on modified files..."
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
add_custom_target(fix-all
    COMMAND clang-format -i ${ALL_SOURCE_FILES}
    COMMENT "Running clang-format on all source files..."
)

add_subdirectory(test)

add_subdirectory(src/section_2_SOLID/ch3_single_resp)
add_subdirectory(src/section_2_SOLID/ch4_open_closed)
add_subdirectory(src/section_2_SOLID/ch5_liksov_subs)
add_subdirectory(src/section_2_SOLID/ch6_interface_segregation)
add_subdirectory(src/section_2_SOLID/ch7_dep_inversion)

add_subdirectory(src/section_3_builder/ch11-no-builder)
add_subdirectory(src/section_3_builder/ch12-builder)
add_subdirectory(src/section_3_builder/ch13-fluent-builder)
add_subdirectory(src/section_3_builder/ch14-groovy-style-builder)
add_subdirectory(src/section_3_builder/ch15-builder-facets)
add_subdirectory(src/section_3_builder/builder-coding-excercise)

add_subdirectory(src/section_4_factories/ch18-point-example)
add_subdirectory(src/section_4_factories/ch19-factory-method)
add_subdirectory(src/section_4_factories/ch20-factory)
add_subdirectory(src/section_4_factories/ch21-inner-factory)
add_subdirectory(src/section_4_factories/ch22-abstract-factory)
add_subdirectory(src/section_4_factories/ch23-functional-factory)
add_subdirectory(src/section_4_factories/factory-coding-excercise)

add_subdirectory(src/section_5_prototype/ch26-record-keeping)
add_subdirectory(src/section_5_prototype/ch27-prototype)
add_subdirectory(src/section_5_prototype/ch28-prototype-factory)
add_subdirectory(src/section_5_prototype/ch29-prototype-via-serialization)
add_subdirectory(src/section_5_prototype/prototype-coding-excercise)

add_subdirectory(src/section_6_singleton/ch32-singleton-implementation)
add_subdirectory(src/section_6_singleton/ch33-testeability-issues)
add_subdirectory(src/section_6_singleton/ch34-singleton-dep-injection)
add_subdirectory(src/section_6_singleton/ch35-singleton-lifetime)
add_subdirectory(src/section_6_singleton/ch36-monostate)
add_subdirectory(src/section_6_singleton/ch37-multiton)
add_subdirectory(src/section_6_singleton/singleton-coding-excercise)

add_subdirectory(src/section_7_adapter/adapter-coding-excercise)

add_subdirectory(src/section_8_bridge/ch44-pimpl-idiom)
add_subdirectory(src/section_8_bridge/ch45-shrink-wrapped-pimpl)
add_subdirectory(src/section_8_bridge/ch46-bridge-implementation)
add_subdirectory(src/section_8_bridge/bridge-excercise)

add_subdirectory(src/section_9_composite/ch49-geometric-shapes)
add_subdirectory(src/section_9_composite/ch50-neural-networks)
add_subdirectory(src/section_9_composite/ch51-array-backed-properties)
add_subdirectory(src/section_9_composite/composite-excercise)

add_subdirectory(src/section_10_decorator/ch54-dynamic-decorator)
add_subdirectory(src/section_10_decorator/ch55-static-decorator)
add_subdirectory(src/section_10_decorator/ch56-functional-decorator)
add_subdirectory(src/section_10_decorator/decorator-excercise)

add_subdirectory(src/section_11_facade/ch59-facade)

add_subdirectory(src/section_12_flyweight/ch62-handmade-flyweight)
add_subdirectory(src/section_12_flyweight/ch63-boost-flyweight)
add_subdirectory(src/section_12_flyweight/ch64-text-formatting)
add_subdirectory(src/section_12_flyweight/flyweight-excercise)

add_subdirectory(src/section_13_proxy/ch67-smart-pointers)
add_subdirectory(src/section_13_proxy/ch68-property-proxy)
add_subdirectory(src/section_13_proxy/ch69-virtual-proxy)
add_subdirectory(src/section_13_proxy/ch70-communication-proxy)
add_subdirectory(src/section_13_proxy/proxy-excercise)

add_subdirectory(src/section_14_chain_of_responsibility/ch74-pointer-chain)
add_subdirectory(src/section_14_chain_of_responsibility/ch75-broker-chain)
add_subdirectory(src/section_14_chain_of_responsibility/cor-excercise)

add_subdirectory(src/section_15_command/ch78-command)
add_subdirectory(src/section_15_command/ch79-undo-operations)
add_subdirectory(src/section_15_command/ch80-composite-command-macro)
add_subdirectory(src/section_15_command/command-excercise)

add_subdirectory(src/section_16_interpreter/ch83-handmade-interpreter-lexing)
add_subdirectory(src/section_16_interpreter/ch84-handmade-interpreter-parsing)
add_subdirectory(src/section_16_interpreter/ch85-parser-boost)
add_subdirectory(src/section_16_interpreter/interpreter-excercise)

add_subdirectory(src/section_17_iterator/ch88-std-iterators)
add_subdirectory(src/section_17_iterator/ch89-binary-tree-iterator)
add_subdirectory(src/section_17_iterator/ch90-tree-iterator-coroutines)
add_subdirectory(src/section_17_iterator/ch91-boost-iterator-facade)
add_subdirectory(src/section_17_iterator/iterator-excercise)

add_subdirectory(src/section_18_mediator/ch94-chat-room)
add_subdirectory(src/section_18_mediator/ch95-event-broker)
add_subdirectory(src/section_18_mediator/mediator-excercise)

add_subdirectory(src/section_19_memento/ch98-memento)
add_subdirectory(src/section_19_memento/ch99-undo-and-redo)
add_subdirectory(src/section_19_memento/ch100-automatic-memento)
add_subdirectory(src/section_19_memento/memento-excercise)

add_subdirectory(src/section_20_observer/ch103-observer)
add_subdirectory(src/section_20_observer/ch104-observable)
add_subdirectory(src/section_20_observer/ch105-observable-boost)
add_subdirectory(src/section_20_observer/ch106-deps-problem)
add_subdirectory(src/section_20_observer/ch107-thread-safety-reentrancy)
add_subdirectory(src/section_20_observer/observer-excercise)

add_subdirectory(src/section_21_state/ch110-classic-state-impl)
add_subdirectory(src/section_21_state/ch111-handmade-fsm)
add_subdirectory(src/section_21_state/ch112-boost-msm)
add_subdirectory(src/section_21_state/state-excercise)

