# 1.源文件列表
aux_source_directory(. SRC_LIST)

# 2.生成可执行文件
add_executable(chatserver ${SRC_LIST})

# 3.链接库
set(MuduoLib_1 muduo_net)
set(MuduoLib_2 muduo_base)

set(Thread_1 pthread)

target_link_libraries(chatserver PRIVATE
	# Muduo
	${MuduoLib_1} ${MuduoLib_2}
	# Thread
	${Thread_1}
)
