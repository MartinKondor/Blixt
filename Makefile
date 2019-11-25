
comp:
	@gcc src/* -Iinclude -o bin/blx.exe
	@bin/blx.exe bin/test.txt

decomp:
	@gcc src/* -Iinclude -o bin/blx.exe
	@bin/blx.exe bin/test.txt
	@bin/blx.exe bin/test.txt.blx

test:
	@gcc src/* -Iinclude -o bin/blx.exe
	@python test.py
