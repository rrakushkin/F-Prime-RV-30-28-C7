####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
####

set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/RTC.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/RTC.cpp"
)


set(MOD_DEPS
    PicoSDK
    HardwareI2C
)

register_fprime_module()
