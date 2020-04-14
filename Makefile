all: compile
debug:
	gcc -Wall -Werror -g -o cr EntryPn.c
compile:
	gcc -O2 -o cr EntryPn.c
install: all
	cp cr /usr/bin/cr
	cp cr.1 /usr/share/man/man1/cr.1
uninstall:
	rm /usr/bin/cr
	rm /usr/share/man/man1/cr.1
clean:
	rm cr
