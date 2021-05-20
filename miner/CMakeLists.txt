set(CMAKE_CXX_STANDARD 14)

aux_source_directory(. SRC_LIST)

include_directories(BEFORE ..)

set(EXECUTABLE miner)

file(GLOB HEADERS "*.h")

add_executable( ${EXECUTABLE} ${SRC_LIST} ${HEADERS})

# hunter_add_package(CLI11)
# find_package(CLI11 CONFIG REQUIRED)

target_link_libraries(miner PRIVATE kec Boost::system Boost::thread)

target_include_directories(miner PRIVATE $ENV{XILINX_XRT}/include ../libethash/xcl2)
target_link_directories(miner PUBLIC $ENV{XILINX_XRT}/lib)	
target_link_libraries(miner PUBLIC xrt_coreutil OpenCL pthread rt stdc++)

include(GNUInstallDirs)
install(TARGETS miner DESTINATION ${CMAKE_INSTALL_BINDIR})