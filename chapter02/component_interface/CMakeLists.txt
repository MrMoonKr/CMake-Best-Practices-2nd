# CMakeLists file for the Chapter 2 - Component Interface
#
# SPDX-License-Identifier: MIT

# 프로젝트 설정
project(
    ch2_framework_component_interface
    VERSION 1.0
    DESCRIPTION "Chapter 2 component interface implementation"
    LANGUAGES CXX
)

# 라이브러리 추가가
add_library( ch2_framework_component_interface INTERFACE )

# include 디렉토리 추가
target_include_directories(
    ch2_framework_component_interface INTERFACE include/
)

# 컴파일 설정
target_compile_features( 
    ch2_framework_component_interface INTERFACE cxx_std_11
)

# Make specified target(s) installable. Separate them to components.
# 설치용 타겟 설정
install( TARGETS ch2_framework_component_interface COMPONENT ch2.libraries )

# Install the headers
# 헤더 파일 설치
install(
    DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/include/
    COMPONENT ch2.libraries
    DESTINATION include
)
