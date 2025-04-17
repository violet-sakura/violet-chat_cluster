
# 设置源文件列表
# 1.
set(SRC_LIST ./server_1.cpp)
# 2.
# aux_source_directory(. SRC_LIST)

# 生成可执行文件
add_executable(server_1 ${SRC_LIST})

# 设置可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

# 设置链接库
set(MuduoLib_1 muduo_net)
set(MuduoLib_2 muduo_base)
set(MuduoLib_3 pthread)

# 链接库
target_link_libraries(server_1 PRIVATE
	${MuduoLib_1} ${MuduoLib_2} ${MuduoLib_3}
)
