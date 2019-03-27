# CMake generated Testfile for 
# Source directory: /home/sebastiaan/projects/bmptkpp/Build-environment/modules/INPUTLIB
# Build directory: /home/sebastiaan/projects/bmptkpp/Build-environment/modules/INPUTLIB/build_test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(build_test "/usr/bin/cmake" "--build" ".")
add_test(unit_test "./unit_test")
set_tests_properties(unit_test PROPERTIES  DEPENDS "build_test")
# add_test(complexity_test "lizard" "-C" "10" "--warnings_only" ".")
# set_tests_properties(complexity_test PROPERTIES  WORKING_DIRECTORY "/home/sebastiaan/projects/bmptkpp/Build-environment/modules/INPUTLIB")
# add_test(clangformat_test "python2" "/home/sebastiaan/projects/bmptkpp/Build-environment/modules/INPUTLIB/.clang-format-compare.py" "/home/sebastiaan/projects/bmptkpp/Build-environment/modules/INPUTLIB/src" "/home/sebastiaan/projects/bmptkpp/Build-environment/modules/INPUTLIB/test")
