
#! /bin/bash

gcc -x c -O3 -o main \
  adt/adt.c adt/int/adtint.c adt/flt/adtflt.c adt/str/adtstr.c adt/rec/adtrec.c adt/ptr/adtptr.c adt/vert/adtvert.c\
  stack/stack.c stack/vec/stackvec.c stack/lst/stacklst.c \
  queue/queue.c queue/vec/queuevec.c queue/lst/queuelst.c \
  bst/bst.c bst/rec/bstrec.c bst/itr/bstitr.c \
  graph/graph.c graph/rec/graphrec.c graph/itr/graphitr.c \
  graph/rep/mat/graphmat.c graph/rep/lst/graphlst.c graph/rep/bst/graphbst.c \
  itr/itr.c \
  bst/bstitrpreord.c bst/bstitrinord.c bst/bstitrpostord.c bst/bstitrbreadth.c \
  graph/graphitrpreord.c graph/graphitrpostord.c graph/graphitrbreadth.c \
  graph/vertitr.c \
  graph/bst/bstitr.c graph/mat/edgitr.c graph/mat/matitr.c \
  list/itrlist.c list/list.c\

  utility.c main.c
