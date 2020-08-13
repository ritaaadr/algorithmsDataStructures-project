
#! /bin/bash

gcc -x c -O3 -o main \
  adt/adt.c adt/int/adtint.c adt/flt/adtflt.c adt/str/adtstr.c adt/rec/adtrec.c \
  stack/stack.c stack/vec/stackvec.c stack/lst/stacklst.c \
  queue/queue.c queue/vec/queuevec.c queue/lst/queuelst.c \
  bst/bst.c bst/rec/bstrec.c bst/itr/bstitr.c \
  itr/itr.c \
  bst/bstitrpreord.c bst/bstitrinord.c bst/bstitrpostord.c bst/bstitrbreadth.c \
  utility.c main.c
