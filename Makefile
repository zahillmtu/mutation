CC = gcc

SRC = testMutate.c

OBJ_FILE = testMutate.o
EXE_FILE = testMutate

${EXE_FILE}: ${OBJ_FILE} ${HOST_EXE}
	    ${CC} -o ${EXE_FILE} ${OBJ_FILE}

${HOST_EXE}: ${HOST_OBJ}
	    ${CC} -o ${HOST_EXE} ${HOST_OBJ}

.c.o:
	    ${CC} -c $<

clean:
	rm -f ${EXE_FILE} ${OBJ_FILE} v* 
