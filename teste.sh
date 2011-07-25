#!/bin/bash

for f in teste?.c; do
	( gcc $f $CFLAGS && ./a.out )
done
rm a.out
