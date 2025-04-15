#==============================================================================
MUDUO_LIB = -lmuduo_net -lmuduo_base -lpthread
#==============================================================================
OUT_DIR = /home/violet/D/CApp/Project/ChatCluster/test/02_Muduo_Test/bin/
#==============================================================================
BUILD_TOOL = g++
#==============================================================================
# 编译选项
CFLAGS = -g
# CFLAGS = -O2
#==============================================================================

all : ${OUT_DIR}server_1 ${OUT_DIR}client_1

${OUT_DIR}server_1 : server_1.cpp
	${BUILD_TOOL} ${CFLAGS} -o ${OUT_DIR}server_1 server_1.cpp ${MUDUO_LIB}

${OUT_DIR}client_1 : client_1.cpp
	${BUILD_TOOL} ${CFLAGS} -o ${OUT_DIR}client_1 client_1.cpp ${MUDUO_LIB}

clean :
	rm -rf ${OUT_DIR}server_1 ${OUT_DIR}client_1
