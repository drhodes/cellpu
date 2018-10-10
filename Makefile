CFLAGS=-Wall -pg -std=c11
LDFLAGS=-lSDL2 -llua5.3 -lSDL2_ttf
TESTFLAGS=-Wall -g -std=c11
TESTLIBS= -lSDL2 -llua5.3 -lcheck -lsubunit -pthread -lrt -lm -lsubunit
EXE=sim
TESTEXE=testbin

all: clean main ## build

run: all
	rlwrap ./${EXE}

docs: FORCE
	doxygen doxygen.cfg

profile: clean main
	valgrind --tool=callgrind --dump-instr=yes ./${EXE}
	kcachegrind callgrind.out*

display-state.o:
	${CC} -c ${CFLAGS} src/display-state.c -o $@ 

err.o: 
	${CC} -c ${CFLAGS} src/err.c -o $@

callbacks.o:
	${CC} -c ${CFLAGS} src/callbacks.c -o $@  

bbox.o: 
	${CC} -c ${CFLAGS} src/bbox.c -o $@  

term.o: 
	${CC} -c ${CFLAGS} src/term.c -o $@  

main: display-state.o callbacks.o err.o term.o bbox.o
	${CC} ${CFLAGS} ${LDFLAGS} -o ${EXE} src/$@.c $? 

test-optical-ctl: optical-ctl FORCE ## test
	${CC} ${TESTFLAGS} test/test-optical-ctl.c ${TESTLIBS} -o ${TESTEXE}
	./${TESTEXE}

work: ## open all files in editor
	emacs -nw src/*.c src/*.h lua/*.lua Makefile

add: clean ## add files to the git repo
	git add -A :/

commit: ## git commit -a
	git commit -a

# http://marmelab.com/blog/2016/02/29/auto-documented-makefile.html
.PHONY: help clean
help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk \
	'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

clean: FORCE ## clean all the things
	rm -f ${EXE}
	rm -f ${TESTEXE}
	rm -f callgrind.out*
	rm -f gmon.out*
	bash clean.bash

FORCE:
