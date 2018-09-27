

CFLAGS=-Wall -g -std=c11 -lSDL2 -llua5.3
EXE=sim

all: main.c ## build

docs: FORCE
	doxygen doxygen.cfg

cell.o:
	gcc ${CFLAGS} -o $@ cell.c

err.o: 
	gcc -c err.c -o $@

optical-ctl.o: 
	gcc -c optical-ctl.c -o $@ 

main.c: optical-ctl.o
	gcc ${CFLAGS} $@ -o ${EXE}

test: ## test
	echo test

work: ## open all files in editor
	emacs -nw *.c *.h *.lua Makefile

setup:
	touch battle-plan.org
	mkdir -p design

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
	bash clean.bash

FORCE:
