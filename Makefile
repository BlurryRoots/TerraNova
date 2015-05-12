
build: setup
	@make -C build

# utility makeflile to setup cmake call
setup:
	@cd build && (export CC=`which clang`; export CXX=`which clang++`; cmake ../)

setup-win64:
	@cd build && cmake ../ -DCMAKE_TOOLCHAIN_FILE=../Win64.cmake

clean:
	@rm -rf build/*
