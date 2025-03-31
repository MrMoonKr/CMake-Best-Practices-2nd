cmake_minimum_required( VERSION 3.23 )

project( "Chapter00"
    VERSION 1.0
    DESCRIPTION "CMake 사용법 체크용 프로젝트 입니다"
    LANGUAGES CXX
)

# set( CMAKE_EXPORT_COMPILE_COMMANDS FALSE )

message( STATUS "[정보] VCPKG_TARGET_TRIPLET : ${VCPKG_TARGET_TRIPLET}" )
message( STATUS "[정보] CMAKE_TOOLCHAIN_FILE : ${CMAKE_TOOLCHAIN_FILE}" )
message( STATUS "[정보] CMAKE_BUILD_TYPE : ${CMAKE_BUILD_TYPE}" )
message( STATUS "[정보] CMAKE_EXPORT_COMPILE_COMMANDS : ${CMAKE_EXPORT_COMPILE_COMMANDS}" )

# pdcurses 패키지 확인 및 링크 옵션
find_package( unofficial-pdcurses CONFIG REQUIRED )
# target_link_libraries( main PRIVATE unofficial::pdcurses::pdcurses )


# chapter00_00 : hello_pdcurses.cpp 예제
add_executable( chapter00_00 
    ./src/hello_pdcurses.cpp 
)
target_include_directories( chapter00_00 PRIVATE ./src )
target_link_libraries( chapter00_00 PRIVATE unofficial::pdcurses::pdcurses )


# chapter00_01 : 블록격파 게임 예제
add_executable( chapter00_01 
    ./src/clock.cpp ./src/clock.h
    ./src/collision.cpp ./src/collision.h
    ./src/game_menu.cpp ./src/game_menu.h
    ./src/game_over.cpp ./src/game_over.h
    ./src/game_play.cpp ./src/game_play.h
    ./src/game_won.cpp ./src/game_won.h
    ./src/game.cpp ./src/game.h
    ./src/konami.cpp ./src/konami.h
    ./src/main.cpp
    ./src/move.cpp ./src/move.h
    ./src/object.cpp ./src/object.h
    ./src/rect.cpp ./src/rect.h
)


target_link_libraries( chapter00_01 PRIVATE unofficial::pdcurses::pdcurses )

add_executable( chapter00_02
    ./src/apple_war.cpp
)
target_link_libraries( chapter00_02 PRIVATE unofficial::pdcurses::pdcurses )
