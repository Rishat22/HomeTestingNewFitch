cmake_minimum_required(VERSION 3.2)

if(DEFINED ENV{GITHUB_RUN_NUMBER})
    project(Lesson1 VERSION 0.0.$ENV{GITHUB_RUN_NUMBER})
else()
    project(Lesson1)
endif()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

add_executable(lesson_cli
    main.cpp
)

set(project_sources
    lib.cpp
    ip_filter.cpp
    )
add_library(lesson ${project_sources} )

add_executable(test_version test_version.cpp)

set_target_properties(lesson_cli lesson test_version PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)
target_include_directories(lesson
    PRIVATE "${CMAKE_BINARY_DIR}"
)
set_target_properties(test_version PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)

target_link_libraries(lesson_cli PRIVATE
    lesson
)
target_link_libraries(test_version
    ${Boost_LIBRARIES}
    lesson
)

if (MSVC)
    target_compile_options(lesson_cli PRIVATE
        /W4
    )
    target_compile_options(lesson PRIVATE
        /W4
    )
    target_compile_options(test_version PRIVATE
        /W4
    )
else ()
    target_compile_options(lesson_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(lesson PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_version PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()



install(TARGETS lesson_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)

enable_testing()

add_test(test_version test_version)
