cmake_minimum_required(VERSION 4.0)
project(KernelForge)

set(CMAKE_CXX_STANDARD 23)

# --- AdaptiveCpp ---
set(AdaptiveCpp_DIR "/usr/local/lib/cmake/AdaptiveCpp" CACHE STRING
        "AdaptiveCpp install directory containing cmake scripts")
find_package(AdaptiveCpp CONFIG REQUIRED)

# --- Drogon ---
find_package(Drogon REQUIRED)

# --- OpenMP (для omp-бэкенда AdaptiveCpp) ---
find_package(OpenMP REQUIRED)

file(GLOB_RECURSE KERNELFORGE_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/framework/src/*.cpp"
)
file(GLOB_RECURSE MODULE_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/modules/*.cc"
)
file(GLOB_RECURSE TRANSPORT_SOURCES CONFIGURE_DEPENDS
        "${CMAKE_CURRENT_SOURCE_DIR}/transport/*.cc"
)

add_executable(kernelforge_server
        main.cpp
        modules/calc/Person.cpp
        ${KERNELFORGE_SOURCES}
        ${MODULE_SOURCES}
        ${TRANSPORT_SOURCES}
)

# include-пути для framework
target_include_directories(kernelforge_server
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/framework/include"
)

add_sycl_to_target(TARGET kernelforge_server)

# libomp include, если нашли
if(DEFINED LIBOMP_INCLUDE_DIR)
    target_include_directories(kernelforge_server PRIVATE ${LIBOMP_INCLUDE_DIR})
endif()

target_link_libraries(kernelforge_server
        PRIVATE
        Drogon::Drogon
        AdaptiveCpp::acpp-common
        OpenMP::OpenMP_CXX
)