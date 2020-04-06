all: compile
compile:
	gcc -Wall -Werror -O2 -o cr Main.c
install: all
	cp cr /usr/bin/cr
	cp cr.1 /usr/share/man/man1/cr.1
uninstall:
	rm /usr/bin/cr
	rm /usr/share/man/man1/cr.1
clean:
	rm cr
