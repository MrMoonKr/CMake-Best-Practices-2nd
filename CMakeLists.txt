# 최소 요구 버전 지정
cmake_minimum_required( VERSION 3.23 )

set( VCPKG_TARGET_TRIPLET "x64-windows" CACHE STRING "")
set( CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

# 프로젝트 이름, 버전, 설명, 사용할 언어 지정
project( "CMakeBestPractices"
    VERSION 1.0.0
    DESCRIPTION "The 'build-all' instructions for all examples for the book CMake Best Practices"
    LANGUAGES C CXX
)

# 외부 CMake 프로젝트를 가져오라고 지정
include( CTest )

# 빌드 타입 지정
set( CMAKE_BUILD_TYPE "Debug"
    CACHE STRING "Default build type for single-config generators"
)

set( CMAKE_EXPORT_COMPILE_COMMANDS TRUE )

# 내부 전역 변수 조회
get_property( is_multi_config_generator GLOBAL
    PROPERTY GENERATOR_IS_MULTI_CONFIG
)
if( NOT is_multi_config_generator )
    message( STATUS "[정보] Using a single-config generator ( ${CMAKE_GENERATOR} )")
    message( STATUS "[정보] Current build type is `${CMAKE_BUILD_TYPE}`")
else()
    message( STATUS "[정보] Using a multi-config generator ( ${CMAKE_GENERATOR} )")
    message( STATUS "[정보] Current build type is `${CMAKE_BUILD_TYPE}`")
endif()


find_program( CCACHE_PROGRAM ccache )
if( CCACHE_PROGRAM )
    set( CMAKE_C_COMPILER_LAUNCHER ${CCACHE_PROGRAM} )
    set( CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM} )
endif()

set_property( GLOBAL PROPERTY USE_FOLDERS ON )

# 하위 프로젝트 추가
add_subdirectory( chapter00 )
# add_subdirectory( chapter01 )
# add_subdirectory( chapter02 )
# add_subdirectory( chapter03 )
# add_subdirectory( chapter04 )
# add_subdirectory( chapter05 )
# add_subdirectory( chapter06 )
# add_subdirectory( chapter07 )
# add_subdirectory( chapter08 )
# the chapter 10 examples are intended to be built standalone
# add_subdirectory( chapter10 )

# add chapter 11 examples only on Apple platforms
# if( APPLE )
#     add_subdirectory( chapter11 )
# endif()

# add_subdirectory( chapter12 )
# add_subdirectory( chapter13 )
# add_subdirectory( chapter14 )
