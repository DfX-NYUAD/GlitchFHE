# CMake generated Testfile for 
# Source directory: /home/dfx/projects/FIA_FHE/FHE_sim/EVA/third_party/Galois/lonestar/scientific/cpu/barneshut
# Build directory: /home/dfx/projects/FIA_FHE/FHE_sim/EVA/third_party/Galois/lonestar/scientific/cpu/barneshut
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(run-small-barneshut-cpu-4 "/home/dfx/projects/FIA_FHE/FHE_sim/EVA/third_party/Galois/lonestar/scientific/cpu/barneshut/barneshut-cpu" "-n" "10000" "-steps" "1" "-seed" "0" "-t" "4")
set_tests_properties(run-small-barneshut-cpu-4 PROPERTIES  ENVIRONMENT "GALOIS_DO_NOT_BIND_THREADS=1" LABELS "quick" _BACKTRACE_TRIPLES "/home/dfx/projects/FIA_FHE/FHE_sim/EVA/third_party/Galois/lonestar/CMakeLists.txt;17;add_test;/home/dfx/projects/FIA_FHE/FHE_sim/EVA/third_party/Galois/lonestar/scientific/cpu/barneshut/CMakeLists.txt;10;add_test_scale;/home/dfx/projects/FIA_FHE/FHE_sim/EVA/third_party/Galois/lonestar/scientific/cpu/barneshut/CMakeLists.txt;0;")
add_test(run-small-barneshut-cpu-2 "/home/dfx/projects/FIA_FHE/FHE_sim/EVA/third_party/Galois/lonestar/scientific/cpu/barneshut/barneshut-cpu" "-n" "10000" "-steps" "1" "-seed" "0" "-t" "2")
set_tests_properties(run-small-barneshut-cpu-2 PROPERTIES  ENVIRONMENT "GALOIS_DO_NOT_BIND_THREADS=1" LABELS "quick" _BACKTRACE_TRIPLES "/home/dfx/projects/FIA_FHE/FHE_sim/EVA/third_party/Galois/lonestar/CMakeLists.txt;17;add_test;/home/dfx/projects/FIA_FHE/FHE_sim/EVA/third_party/Galois/lonestar/scientific/cpu/barneshut/CMakeLists.txt;10;add_test_scale;/home/dfx/projects/FIA_FHE/FHE_sim/EVA/third_party/Galois/lonestar/scientific/cpu/barneshut/CMakeLists.txt;0;")
add_test(run-small-barneshut-cpu-1 "/home/dfx/projects/FIA_FHE/FHE_sim/EVA/third_party/Galois/lonestar/scientific/cpu/barneshut/barneshut-cpu" "-n" "10000" "-steps" "1" "-seed" "0" "-t" "1")
set_tests_properties(run-small-barneshut-cpu-1 PROPERTIES  ENVIRONMENT "GALOIS_DO_NOT_BIND_THREADS=1" LABELS "quick" _BACKTRACE_TRIPLES "/home/dfx/projects/FIA_FHE/FHE_sim/EVA/third_party/Galois/lonestar/CMakeLists.txt;17;add_test;/home/dfx/projects/FIA_FHE/FHE_sim/EVA/third_party/Galois/lonestar/scientific/cpu/barneshut/CMakeLists.txt;10;add_test_scale;/home/dfx/projects/FIA_FHE/FHE_sim/EVA/third_party/Galois/lonestar/scientific/cpu/barneshut/CMakeLists.txt;0;")
