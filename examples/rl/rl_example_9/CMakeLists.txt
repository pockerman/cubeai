cmake_minimum_required(VERSION 3.6 FATAL_ERROR)

SET(EXECUTABLE  rl_example_9)
SET(SOURCE ${EXECUTABLE}.cpp)

ADD_EXECUTABLE(${EXECUTABLE} ${SOURCE})

TARGET_LINK_LIBRARIES(${EXECUTABLE} cubeailib)
TARGET_LINK_LIBRARIES(${EXECUTABLE} ${TORCH_LIBRARIES})
TARGET_LINK_LIBRARIES(${EXECUTABLE} pthread)
TARGET_LINK_LIBRARIES(${EXECUTABLE} openblas)
TARGET_LINK_LIBRARIES(${EXECUTABLE} gymfcpplib)
TARGET_LINK_LIBRARIES(${EXECUTABLE} python3.10)
TARGET_LINK_LIBRARIES(${EXECUTABLE} boost_python310)
TARGET_LINK_LIBRARIES(${EXECUTABLE} boost_system)

