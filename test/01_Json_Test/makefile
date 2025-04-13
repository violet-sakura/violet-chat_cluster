#-------------------------------------------------------------------
JSON_INCL = -I/home/violet/D/CApp/Project/ChatCluster/test

JSON_CPP = /home/violet/D/CApp/Project/ChatCluster/test/json.hpp

OUT_DIR = /home/violet/D/CApp/Project/ChatCluster/test/01_Json_Test/bin/

# 编译选项
CFLAGS = -g
# CFLAGS = -O2
#-------------------------------------------------------------------

all : ${OUT_DIR}testA1 ${OUT_DIR}testA2

${OUT_DIR}testA1 : testA1.cpp
	g++ ${CFLAGS} -o ${OUT_DIR}testA1 testA1.cpp ${JSON_INCL} ${JSON_CPP}

${OUT_DIR}testA2 : testA2.cpp
	g++ ${CFLAGS} -o ${OUT_DIR}testA2 testA2.cpp ${JSON_INCL} ${JSON_CPP}

clean :
	rm -rf ${OUT_DIR}testA1 ${OUT_DIR}testA2