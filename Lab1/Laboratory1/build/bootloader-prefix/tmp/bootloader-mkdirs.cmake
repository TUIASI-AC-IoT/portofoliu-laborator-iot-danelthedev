# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/danel/esp/v5.4/esp-idf/components/bootloader/subproject"
  "/home/danel/Facultate/An1/Sem2/IOT/Lab1/Laboratory1/build/bootloader"
  "/home/danel/Facultate/An1/Sem2/IOT/Lab1/Laboratory1/build/bootloader-prefix"
  "/home/danel/Facultate/An1/Sem2/IOT/Lab1/Laboratory1/build/bootloader-prefix/tmp"
  "/home/danel/Facultate/An1/Sem2/IOT/Lab1/Laboratory1/build/bootloader-prefix/src/bootloader-stamp"
  "/home/danel/Facultate/An1/Sem2/IOT/Lab1/Laboratory1/build/bootloader-prefix/src"
  "/home/danel/Facultate/An1/Sem2/IOT/Lab1/Laboratory1/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/danel/Facultate/An1/Sem2/IOT/Lab1/Laboratory1/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/danel/Facultate/An1/Sem2/IOT/Lab1/Laboratory1/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
