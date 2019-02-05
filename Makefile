CFLAGS= \
	-O0 \
	-g \
	-std=c++17 \
	-Wall \
	-Werror \
	-Wno-deprecated-declarations \
	-Wno-switch \
	-fsanitize=address \

LDFLAGS=-lSDL2 -llua5.3 -lSDL2_ttf
TESTFLAGS=-Wall -g -std=c11
TESTLIBS= -lSDL2 -llua5.3 -lcheck -lsubunit -pthread -lrt -lm -lsubunit
EXE=sim
TESTEXE=testbin
CC=g++

all: clean main ## build

docs: FORCE ## create documentation with doxygen
	doxygen doxygen.cfg

tags: FORCE ## create tags
	gtags ./src # /usr/include/SDL2 /usr/include/c++/8

see-docs: docs ## open docs in web browser.
	sensible-browser ./dox/html/index.html 

profile: clean main ## start cachegrind after some use
	valgrind --tool=callgrind --dump-instr=yes ./${EXE}
	cachegrind callgrind.out*

watch: ## setup a watch for the source directory to rebuild on change
	when-changed -r Makefile src/*.c src/*.cc src/*.hh -c "clear && make clean && make -j8 main"

expected.o:
	${CC} -c ${CFLAGS} src/expected.cc -o $@

common.o: 
	${CC} -c ${CFLAGS} src/common.cc -o $@

instruction.o: 
	${CC} -c ${CFLAGS} src/instruction.cc -o $@

instruction-selector.o: 
	${CC} -c ${CFLAGS} src/instruction-selector.cc -o $@

app.o: 
	${CC} -c ${CFLAGS} src/app.cc -o $@

entity-store.o: 
	${CC} -c ${CFLAGS} src/entity-store.cc -o $@

cmdr.o: 
	${CC} -c ${CFLAGS} src/cmdr.cc -o $@

text-box.o: 
	${CC} -c ${CFLAGS} src/text-box.cc -o $@

display.o: 
	${CC} -c ${CFLAGS} src/display.cc -o $@

event-loop.o: 
	${CC} -c ${CFLAGS} src/event-loop.cc -o $@

grid.o: 
	${CC} -c ${CFLAGS} src/grid.cc -o $@

grid-edit.o: 
	${CC} -c ${CFLAGS} src/grid-edit.cc -o $@

global.o: 
	${CC} -c ${CFLAGS} src/global.cc -o $@

cell.o:
	${CC} -c ${CFLAGS} src/cell.cc -o $@

draw.o:
	${CC} -c ${CFLAGS} src/draw.cc -o $@

atlas.o:
	${CC} -c ${CFLAGS} src/atlas.cc -o $@

err.o:
	${CC} -c ${CFLAGS} src/err.cc -o $@

callbacks.o:
	${CC} -c ${CFLAGS} src/callbacks.cc -o $@

bbox.o:
	${CC} -c ${CFLAGS} src/bbox.cc -o $@

term.o:
	${CC} -c ${CFLAGS} src/term.cc -o $@

lua.o:
	${CC} -c ${CFLAGS} src/lua.cc -o $@

keybinding.o: 
	${CC} -c ${CFLAGS} src/keybinding.cc -o $@

OBJ	=	app.o\
		atlas.o\
		bbox.o\
		callbacks.o err.o\
		cell.o\
		cmdr.o\
		common.o\
		display.o\
		draw.o\
		event-loop.o\
		global.o\
		grid-edit.o\
		grid.o\
		instruction.o\
		instruction-selector.o\
		keybinding.o\
		lua.o\
		term.o\
		text-box.o\

main: ${OBJ} ## 
	${CC} ${CFLAGS} ${LDFLAGS} -o ${EXE} src/$@.cc $?

work: ## open all files in editor
	emacs -nw src/*.cc src/*.hh lua/*.lua Makefile

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
