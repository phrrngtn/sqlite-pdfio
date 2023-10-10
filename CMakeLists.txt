cmake_minimum_required(VERSION 3.25)
project(sqlite_pdfio  VERSION 0.1)

set(TARGET_NAME "sqlite_pdfio")
set(SOURCES "sqlite_pdfio.cpp"
	    "tg/tg.c"
)

find_package(nlohmann_json CONFIG REQUIRED)
find_package(unofficial-sqlite3 CONFIG REQUIRED)
find_path(SQLITE_INCLUDE_DIR sqlite3ext.h)
include_directories(${SQLITE_INCLUDE_DIR} "tg")

# Perhaps it is better to contribute a vcpkg for pdfio?
# https://learn.microsoft.com/en-us/vcpkg/examples/packaging-github-repos
# https://learn.microsoft.com/en-us/vcpkg/maintainers/functions/vcpkg_build_make

add_library(${TARGET_NAME} ${SOURCES})

set_property(TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 20)
target_link_libraries(${TARGET_NAME} PRIVATE nlohmann_json::nlohmann_json)
