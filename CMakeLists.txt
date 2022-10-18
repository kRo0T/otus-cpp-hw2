cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(homework_2 VERSION ${PROJECT_VESRION})

#configure_file(version.h.in version.h)

add_executable(hw2_cli ip_filter.cpp)
add_library(hw2_lib ip_lib.cpp)
add_executable(test_ip test_ip.cpp)

set_target_properties(hw2_cli hw2_lib test_ip PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(hw2_cli
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(hw2_cli PRIVATE
    hw2_lib
)

target_link_libraries(
  test_ip
  GTest::gtest_main
  hw2_lib
)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

if (MSVC)
    target_compile_options(hw2_cli PRIVATE
        /W4
    )
else ()
    target_compile_options(hw2_cli PRIVATE
        #-Wall -Wextra -pedantic -Werror
        -Wall -Wextra
    )
endif()

install(TARGETS hw2_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT e.krotov@mail.ru)
include(CPack)

enable_testing()
include(GoogleTest)
include(CTest)
gtest_discover_tests(test_ip)
