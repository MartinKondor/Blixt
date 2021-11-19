.DEFAULT_GOAL := default

default:
	@g++ src/* -std=c++11 -Iinclude -o bin/blx.o

comp:
	@g++ src/* -std=c++11 -Iinclude -o bin/blx.o
	@cp bin/orig.test.txt bin/test.txt
	@bin/blx.o bin/test.txt

decomp:
	@g++ src/* -std=c++11 -Iinclude -o bin/blx.o
	@bin/blx.o bin/test.txt.blx

test:
	@g++ src/* -std=c++11 -Iinclude -o bin/blx.o
	@python test.py
