
set(TEST_CASES)

foreach(TEST_CASE IN LISTS TEST_CASES)
  add_executable(${TEST_CASE} ${TEST_CASE}.cc)

  target_link_libraries(${TEST_CASE} PRIVATE)

  target_compile_features(${TEST_CASE} PRIVATE cxx_std_17)
endforeach()