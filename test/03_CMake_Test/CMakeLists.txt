# 指定 CMake 最低版本号
cmake_minimum_required(VERSION 3.20)

# 定义项目名称
project(CMakeTestProject)

# 设置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

# 添加子目录
add_subdirectory(./src)
