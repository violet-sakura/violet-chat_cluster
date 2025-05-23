# 版本要求
cmake_minimum_required(VERSION 3.20)
# 项目名称
project(ChatCluster)

# 编译选项
# set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)
set(CMAKE_BUILD_TYPE "Debug")

# 可执行程序输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# 头文件路径
include_directories(
	${CMAKE_SOURCE_DIR}/thirdparty/asynclog/include
	${CMAKE_SOURCE_DIR}/include/server
)

# 子目录
add_subdirectory(src)