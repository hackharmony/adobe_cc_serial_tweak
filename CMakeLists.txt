cmake_minimum_required(VERSION 3.12.0)

project(adobe_serial_tweak
    DESCRIPTION "Extends trial on Adobe CC 2018 products"
    LANGUAGES CXX
)

add_executable(adobe_serial_tweak src/adobe_serial_tweak.cc)
target_compile_features(adobe_serial_tweak PUBLIC cxx_std_17)
target_include_directories(
    adobe_serial_tweak
    PRIVATE
    include
)
target_compile_options(
  adobe_serial_tweak
  PRIVATE
  "$<$<CONFIG:Debug>:-Wall -pedantic -g>"
)

install(
  TARGETS adobe_serial_tweak
  CONFIGURATIONS Release
  RUNTIME DESTINATION bin
)
