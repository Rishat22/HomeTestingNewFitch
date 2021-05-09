cmake_minimum_required(VERSION 3.2)

if(DEFINED ENV{GITHUB_RUN_NUMBER})
    project(TestGitActions VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
else()
    project(TestGitActions)
endif()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

add_executable(TestGitActions_cli
    main.cpp
)

set(project_sources
    lib.cpp
    ip_filter.cpp
    )
add_library(TestGitActions ${project_sources} )

add_executable(unit_tests unit_tests.cpp)

set_target_properties(TestGitActions_cli TestGitActions unit_tests PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(TestGitActions
    PRIVATE "${CMAKE_BINARY_DIR}"
)
set_target_properties(unit_tests PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(TestGitActions_cli PRIVATE
    TestGitActions
)
target_link_libraries(unit_tests
    ${Boost_LIBRARIES}
    TestGitActions
)

if (MSVC)
    target_compile_options(TestGitActions_cli PRIVATE
        /W4
    )
    target_compile_options(TestGitActions PRIVATE
        /W4
    )
    target_compile_options(unit_tests PRIVATE
        /W4
    )
else ()
    target_compile_options(TestGitActions_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(TestGitActions PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(unit_tests PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS TestGitActions_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(unit_tests unit_tests)
