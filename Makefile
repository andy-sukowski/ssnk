# See LICENSE file for copyright and license details.

include config.mk

SRC = ssnk.c linked_list.c
OBJ = ${SRC:.c=.o}

all: options ssnk

options:
	@echo ssnk build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

ssnk: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f ssnk ${OBJ}

install: all
	mkdir -p ${PREFIX}/bin
	cp -f ssnk ${PREFIX}/bin
	chmod 755 ${PREFIX}/bin/ssnk

uninstall:
	rm -f ${PREFIX}/bin/ssnk

.PHONY: all options clean install uninstall
