
GRIND = /usr/bin/valgrind
GRIND_OPTS = --show-leak-kinds=all --leak-check=full --track-origins=yes -v

all: build

build: setup
	@make -C build

setup:
	@cd build && (export CC=`which clang`; export CXX=`which clang++`; cmake ../)

setup-win64:
	@cd build && cmake ../ -DCMAKE_TOOLCHAIN_FILE=../Win64.cmake

clean:
	@rm -rf build/*
	@rm -rf bin/*

run:
	bin/./TerraNova

run-monitor:
	$(GRIND) $(GRIND_OPTS) bin/./TerraNova > log/debug 2> log/error
