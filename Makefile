.DEFAULT_GOAL := default

default:
	@g++ src/* -Iinclude -o bin/blx.o

comp:
	@g++ src/* -Iinclude -o bin/blx.o
	@bin/blx.o bin/test.txt

decomp:
	@g++ src/* -Iinclude -o bin/blx.o
	@bin/blx.o bin/test.txt
	@bin/blx.o bin/test.txt.blx

test:
	@g++ src/* -Iinclude -o bin/blx.o
	@python test.py
