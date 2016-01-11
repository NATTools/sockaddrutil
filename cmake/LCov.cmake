# TODO: parameterize for reuse
add_custom_target(coverage_report
  COMMAND lcov --directory src/CMakeFiles/sockaddrutil.dir --capture --output-file sockaddrutil.info
  COMMAND genhtml --output-directory lcov sockaddrutil.info
  COMMAND echo "Coverage report in: file://${CMAKE_BINARY_DIR}/lcov/index.html"
)
