set(SRC_MAIN myspice.cpp)
set(SRC_OTHERS argparse.cpp)
set(SRC_STAMP mat.cpp device.cpp resistor.cpp capacitor.cpp inductor.cpp mutual.cpp isrc.cpp vsrc.cpp utils.cpp stamp.cpp)

add_executable(myspice ${SRC_MAIN} ${SRC_OTHERS} ${SRC_STAMP})