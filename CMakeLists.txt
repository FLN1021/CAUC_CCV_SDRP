cmake_minimum_required(VERSION 3.10)
project(CAUC_CCV_SDRP)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig)

pkg_check_modules(LIBRTLSDR REQUIRED librtlsdr)
pkg_check_modules(LIBUSB REQUIRED libusb-1.0)

add_executable(CAUC_CCV_SDRP main.cpp
        rtl_adsb.h
        rtl_adsb.cpp
        rtl_con.cpp
        rtl_con.h
)

target_link_libraries(CAUC_CCV_SDRP PRIVATE ${LIBRTLSDR_LIBRARIES})
