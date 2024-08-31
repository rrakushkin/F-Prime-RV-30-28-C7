# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
####
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/RV3028.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/RV3028.cpp"
)

# Uncomment and add any modules that this component depends on, else
# they might not be available when cmake tries to build this component.

set(MOD_DEPS
    Fw/Types
    Svc/Passive
    Svc/Active
    # Add more dependencies if needed
)

register_fprime_module()
