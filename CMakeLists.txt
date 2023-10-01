cmake_minimum_required(VERSION 3.25)
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

target_include_directories(CAUC_CCV_SDRP PRIVATE ${LIBRTLSDR_INCLUDE_DIRS} ${LIBUSB_INCLUDE_DIRS})
target_link_directories(CAUC_CCV_SDRP PRIVATE ${LIBRTLSDR_LIBRARY_DIRS} ${LIBUSB_LIBRARY_DIRS})
target_link_libraries(CAUC_CCV_SDRP PRIVATE ${LIBRTLSDR_LIBRARIES} ${LIBUSB_LIBRARIES})
