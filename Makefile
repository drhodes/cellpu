
CFLAGS=-Wall -g -std=c11 -lSDL2 -llua5.3


optical-ctl.o: 
	gcc optical-ctl.h -o $@ 

main: optical-ctl.o
	gcc ${CFLAGS} main.c -o ldpu 

build: main ## build

test: ## test
	echo test

clean: ## clean all the things
	echo implement clean makefile rule

work: ## open all files in editor
	emacs -nw *.v

setup:
	touch battle-plan.org
	mkdir -p design

add: clean ## add files to the git repo
	git add -A :/

commit: ## git commit -a
	git commit -a

# http://marmelab.com/blog/2016/02/29/auto-documented-makefile.html
.PHONY: help
help:
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk \
	'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

FORCE:

