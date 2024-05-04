# Минимально допустимая версия CMake
cmake_minimum_required(VERSION 3.22 FATAL_ERROR)

# Настройка параметров сборки CMake
set(CMAKE_BUILD_TYPE "Release")

# Настройка параметров следования стандарту языка C++ 
set(CMAKE_CXX_STANDARD 17)

# Рабочее название
set(APP "main")

# Основные параметры проекта
project(${APP} VERSION 0.1 LANGUAGES CXX)

# Настройка параметров компилятора
add_compile_options(-c -O2 -Wall -Wextra -Werror -pedantic)

# Определить цель
add_executable(${APP})

# add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/thirdparty/SQLiteCpp)

message(${CMAKE_CURRENT_LIST_DIR})

# Библиотечные фйлы
target_link_libraries(${APP}
  TgBot
  boost_system ssl crypto
  pthread
  SQLiteCpp
  sqlite3
  dl
)

include_directories("./inc")

# Директории с подключаемыми файлами
target_include_directories(${APP}
  PUBLIC
    /usr/local/include/tgbot
    /usr/local/include/SQLiteCp
  # PRIVATE
  #   smaill_cppTgBot/inc
)

# Определение, какие файлы используются при сборке цели
target_sources(${APP}
  PRIVATE
    src/main.cpp
)