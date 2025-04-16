cmake_minimum_required(VERSION 3.16)

project(progress_bar LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(progress_bar
    main.cpp
    Timer.h)

include(GNUInstallDirs)
install(TARGETS progress_bar
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
