cmake_minimum_required(VERSION 3.16.3)

include(cmake/cable/bootstrap.cmake)

include(CableBuildInfo)
include(CableBuildType)
include(CableToolchains)
include(HunterGate)

include(defaults/HunterCacheServers)

cable_configure_toolchain(DEFAULT cxx11)

set(HUNTER_CONFIGURATION_TYPES Release CACHE STRING "Build type of Hunter packages")
set(HUNTER_JOBS_NUMBER 6 CACHE STRING "Number of parallel builds used by Hunter")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.112.tar.gz"
    SHA1 "4b894e1d5d203f0cc9a77431dbb1b486ab6f4430"
    LOCAL
)

cable_set_build_type(DEFAULT Release CONFIGURATION_TYPES Release RelWithDebInfo)

project(miner)
set(PROJECT_VERSION 0.01)

# ====================== Project Details ======================== #

## Xilinx
set(XILINX_VITIS $ENV{XILINX_VITIS})
set(XILINX_VIVADO $ENV{XILINX_VIVADO})
set(XCL_KERNEL $ENV{XCL_KERNEL})
set(XCL_OPT_INDEX $ENV{XCL_OPT_INDEX})
set(XCL_EMULATION_MODE $ENV{XCL_EMULATION_MODE})
set(XCL_CU $ENV{XCL_CU})
set(XCL_PLATFORM $ENV{XCL_PLATFORM})
set(XCL_OPTS none buffered dataflow distributed vec h2k k2k)

## Xilinx Runtime
set(XILINX_XRT $ENV{XILINX_XRT})
set(XRT_PROFILE "true")
set(XRT_TIMELINE_TRACE "true")
set(XRT_DATA_TRANSFER_TRACE "fine")


hunter_add_package(Boost COMPONENTS system filesystem thread)
find_package(Boost CONFIG REQUIRED COMPONENTS system filesystem thread)

hunter_add_package(jsoncpp)
find_package(jsoncpp CONFIG REQUIRED)



cable_add_buildinfo_library(PROJECT_NAME ${PROJECT_NAME})


add_subdirectory(libethash-fpga)
add_subdirectory(fpga-xclbin)

add_subdirectory(miner)

