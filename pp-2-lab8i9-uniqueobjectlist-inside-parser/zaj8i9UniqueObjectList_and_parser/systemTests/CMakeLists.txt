project(system_tests)

set(BOOST_ROOT "./libs/boost_1_81/") # either set it here or from the command line
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_NO_SYSTEM_PATHS TRUE)

if (Boost_NO_SYSTEM_PATHS)
  set(BOOST_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/libs/boost_1_81/")
  set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}")
  message("Boost: ${BOOST_INCLUDE_DIRS}")
  set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
else()
    find_package(Boost REQUIRED) # header only libraries must not be added here
endif (Boost_NO_SYSTEM_PATHS)



file(GLOB INPUT_OUTPUT_FILES inputOutputData/*.txt)
message(" + Znaleziono pliki wejścia/wyjścia do testów: ${INPUT_OUTPUT_FILES}")

add_executable(${PROJECT_NAME} executableTests.cpp ${INPUT_OUTPUT_FILES})
add_dependencies(${PROJECT_NAME} ${MAIN_PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE ${BOOST_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} gtest gtest_main)

target_compile_definitions(${PROJECT_NAME} PRIVATE COMMANDS_PARSER_PATH="${PROJECT_BINARY_PATH}")
target_compile_definitions(${PROJECT_NAME} PRIVATE CMAKE_CURRENT_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")


############ KOMENDA: make run_system_tests
add_custom_target(run_${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
