set(SRC_MAIN myspice.cpp)
set(SRC_OTHERS argparse.cpp)
set(SRC_STAMP matrix.cpp devices.cpp utils.cpp stamp.cpp)

add_executable(myspice ${SRC_MAIN} ${SRC_OTHERS} ${SRC_STAMP})