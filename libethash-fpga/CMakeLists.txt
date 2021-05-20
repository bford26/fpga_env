
set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(..)

# ======================================

add_library(ethash-fpga FPGAMiner.cpp FPGAMiner.h xcl2.hpp xcl2.cpp)

# ======================================

target_include_directories(ethash-fpga PUBLIC $ENV{XILINX_XRT}/include )
target_link_directories(ethash-fpga PRIVATE ${XILINX_XRT}/lib)


target_link_libraries(ethash-fpga PUBLIC xrt_coreutil OpenCL pthread rt stdc++)


# target_link_libraries(ethash-fpga PUBLIC ethcore ethash::ethash)


# ================================================================


