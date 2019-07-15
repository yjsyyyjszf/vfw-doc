# CMakeList.txt : CMake project for vxp-cmk, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
# add_executable (vxp-cmk "vxp-cmk.cpp" "vxp-cmk.h")
# add_executable (vxp-cmk "vxp-cmk.cpp" "vxp-cmk.h" "GlueEVNT.h" "utf_vxa_common_def.h" "VxaEventStrUtls.h" "VxaEventUtils.h")

# TODO: Add tests and install targets if needed.
add_library (vxp-cmk "vxp-cmk.cpp" "vxp-cmk.h")
# add_library (vxp-doc "vxp-cmk.cpp" "vxp-cmk.h" "GlueEVNT.h" "utf_vxa_common_def.h" "VxaEventStrUtls.h" "VxaEventUtils.h")
 
target_include_directories(vxp-cmk PUBLIC .)