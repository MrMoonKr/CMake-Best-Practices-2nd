cmake_minimum_required( VERSION 3.23 )

project( "game-blackjack"
    VERSION 1.0
    DESCRIPTION "https://github.com/Charibdys/curses-blackjack"
    LANGUAGES C CXX
)

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

# pdcurses 패키지 확인 및 링크 옵션
find_package( unofficial-pdcurses CONFIG REQUIRED )
# target_link_libraries( main PRIVATE unofficial::pdcurses::pdcurses )

# pcg 패키지 확인 및 링크 옵션
find_path( PCG_INCLUDE_DIRS "pcg_extras.hpp" )
# target_include_directories( main PRIVATE ${PCG_INCLUDE_DIRS} )


# chapter00_00 : hello_pdcurses.cpp 예제
add_executable( game-blackjack 
    ./src/card.cpp      ./src/card.h
    ./src/debug.cpp     ./src/debug.h
    ./src/display.cpp   ./src/display.h
    ./src/game.cpp      ./src/game.h
    ./src/main.cpp
)
target_include_directories( game-blackjack PRIVATE ./src )
target_include_directories( game-blackjack PRIVATE ${PCG_INCLUDE_DIRS} )
target_link_libraries( game-blackjack PRIVATE unofficial::pdcurses::pdcurses )

