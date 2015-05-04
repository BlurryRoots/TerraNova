
build: setup
	@make -C build

# utility makeflile to setup cmake call
setup:
	@cd build && (export CC=`which clang`; export CXX=`which clang++`; cmake ../)

clean:
	@rm -rf build/*
