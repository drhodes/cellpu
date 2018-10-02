CFLAGS=-Wall -g -std=c11 -lSDL2 -llua5.3 -lSDL2_ttf
TESTFLAGS=-Wall -g -std=c11
TESTLIBS= -lSDL2 -llua5.3 -lcheck -lsubunit -pthread -lrt -lm -lsubunit
EXE=sim
TESTEXE=testbin

all: main ## build

run: all
	rlwrap ./${EXE}

docs: FORCE
	doxygen doxygen.cfg

cell.o:
	${CC} ${CFLAGS} -o $@ src/cell.c

err: 
	${CC} -c src/$@.c -o $@.o

optical-ctl: 
	${CC} -c src/$@.c -o $@.o

main: optical-ctl
	${CC} ${CFLAGS} src/$@.c -o ${EXE}

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
	bash clean.bash

FORCE:
