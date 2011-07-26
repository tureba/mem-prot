#!/bin/bash

compila() {
	gcc $1 $CFLAGS -o ${2:-${1%.c}}
}

for f in teste?.c; do
	compila $f a.out && ./a.out
done

compila server.c && ./server &
SPID=$!

compila exploit.c && ./exploit -h localhost

# se o exploit funcionar, então o script abre um terminal telnet
telnet localhost 31337

# limpa tudo
kill -9 $SPID
rm -f a.out server exploit
