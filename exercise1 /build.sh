
#! /bin/bash

gcc -x c -o main \
  adt/adt.c adt/int/adtint.c adt/flt/adtflt.c adt/str/adtstr.c adt/str/adtrec.c \
  stack/stack.c stack/vec/stackvec.c stack/lst/stacklst.c \
  queue/queue.c queue/vec/queuevec.c queue/lst/queuelst.c \
  utility.c main.c
