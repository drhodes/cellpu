## c-json is crying about deprecated functions that have since been undeprecated.

CFLAGS= -O0 -g -std=c++17 \
	-Wall \
	-Wno-deprecated-declarations \
	-Wno-switch \
	-fsanitize=address \
	#-Werror \

LDFLAGS=-lSDL2 -llua5.3 -lSDL2_ttf -ljson-c
TESTFLAGS=-Wall -g -std=c11
TESTLIBS= -lSDL2 -llua5.3 -lcheck -lsubunit -pthread -lrt -lm -lsubunit
EXE=sim
TESTEXE=testbin
CC=g++

all: clean main ## build

docs: FORCE ## create documentation with doxygen
	doxygen doxygen.cfg

profile: clean main ## start cachegrind after some use
	valgrind --tool=callgrind --dump-instr=yes ./${EXE}
	cachegrind callgrind.out*

watch: ## setup a watch for the source directory to rebuild on change
	when-changed -r Makefile src/*.c src/*.cpp src/*.h -c "clear && make clean && make -j8 main"

common.o: 
	${CC} -c ${CFLAGS} src/common.c -o $@

instruction.o: 
	${CC} -c ${CFLAGS} src/instruction.c -o $@

grid.o: 
	${CC} -c ${CFLAGS} src/grid.c -o $@

grid-edit.o: 
	${CC} -c ${CFLAGS} src/grid-edit.c -o $@

cell.o:
	${CC} -c ${CFLAGS} src/cell.c -o $@

atlas.o:
	${CC} -c ${CFLAGS} src/atlas.c -o $@

display-state.o:
	${CC} -c ${CFLAGS} src/display-state.c -o $@

err.o:
	${CC} -c ${CFLAGS} src/err.cpp -o $@

callbacks.o:
	${CC} -c ${CFLAGS} src/callbacks.c -o $@

bbox.o:
	${CC} -c ${CFLAGS} src/bbox.cpp -o $@

term.o:
	${CC} -c ${CFLAGS} src/term.cpp -o $@

opcode.o:
	${CC} -c ${CFLAGS} src/opcode.c -o $@

OBJ	=	common.o\
		display-state.o\
		callbacks.o err.o\
		term.o\
		bbox.o\
		atlas.o\
		cell.o\
		grid.o\
		instruction.o\
		opcode.o\
		grid-edit.o

main: ${OBJ} ## 
	${CC} ${CFLAGS} ${LDFLAGS} -o ${EXE} src/$@.c $?

test-optical-ctl: optical-ctl FORCE ## test
	${CC} ${TESTFLAGS} test/test-optical-ctl.c ${TESTLIBS} -o ${TESTEXE}
	./${TESTEXE}

work: ## open all files in editor
	emacs -nw src/*.c src/*.cpp src/*.h lua/*.lua Makefile

add: clean ## add files to the git repo
	git add -A :/

commit: ## git commit -a
	git commit -a

# http://marmelab.com/blog/2016/02/29/auto-documented-makefile.html
.PHONY: help clean docs
help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk \
	'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

clean: FORCE ## clean all the things
	rm -f ${EXE}
	rm -f ${TESTEXE}
	rm -f callgrind.out*
	rm -f gmon.out*
	bash clean.bash

webdocs:
	bash webdocs.bash

FORCE:


# SRC = $(wildcard src/*.c)
# OBJ = $(SRC:src/*.c=obj/*.o)

# ${OBJ}.o:
# 	${CC} -c ${CFLAGS} src/$@.c -o $@

# .PRECIOUS: ${OBJ}
# obj/%.o: src/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# obj/%.o: src/%.c
# 	${CC} ${CFLAGS} -c $< -o $@

# main: ${OBJ}
# 	${CC} ${CFLAGS} ${LDFLAGS} ${OBJ} -o ${EXE}
