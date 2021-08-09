# cmake version
CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

# project name
PROJECT(vd)

# using C++11
set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -std=c++11 ")



# find OpenCV
FIND_PACKAGE(OpenCV REQUIRED)

# show the message of OpenCV
message(STATUS "OpenCV library status:")
message(STATUS "    version: 	${OpenCV_VERSION}")
message(STATUS "    headers: 	${OpenCV_INCLUDE_DIRS}")
message(STATUS "    libraries: 	${OpenCV_LIBS}")

# link headers
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/mylib})
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/displace})


set(PROJECT_BINARY_DIR ${PROJECT_SOURCE_DIR}/../build)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
# 添加源代码文件到SRC_LIST变量中
AUX_SOURCE_DIRECTORY(./ DIR_SRC)

# 生成可执行文件
ADD_EXECUTABLE(vd ${DIR_SRC})



# after ADD_EXECUTABLE，为生成文件target添加库
TARGET_LINK_LIBRARIES(vd ${OpenCV_LIBS})
TARGET_LINK_LIBRARIES(vd Mylib)
TARGET_LINK_LIBRARIES(vd Dis)
