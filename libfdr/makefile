# Libraries for fields, doubly-linked lists and red-black trees.
# Copyright (C) 2001 James S. Plank
# 
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
# 
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
# 
# ---------------------------------------------------------------------------
# Please see http://www.cs.utk.edu/~plank/plank/classes/cs360/360/notes/Libfdr/
# for instruction on how to use this library.
# 
# Jim Plank
# plank@cs.utk.edu
# http://www.cs.utk.edu/~plank
# 
# Associate Professor
# Department of Computer Science
# University of Tennessee
# 203 Claxton Complex
# 1122 Volunteer Blvd.
# Knoxville, TN 37996-3450
# 
#      865-974-4397
# Fax: 865-974-4404

CC = gcc
CFLAGS = -I include/ 

all: lib/libfdr.a

OBJS = obj/dllist.o obj/fields.o obj/jval.o obj/jrb.o

lib/libfdr.a: $(OBJS)
	ar ru lib/libfdr.a $(OBJS)
	ranlib lib/libfdr.a 

clean:
	rm -f lib/* obj/* lib/libfdr.a

obj/dllist.o : include/dllist.h src/dllist.c
	$(CC) $(CFLAGS) -c -o $@ src/dllist.c

obj/fields.o : include/fields.h src/fields.c
	$(CC) $(CFLAGS) -c -o $@ src/fields.c

obj/jrb.o : include/jrb.h src/jrb.c
	$(CC) $(CFLAGS) -c -o $@ src/jrb.c

obj/jval.o : include/jval.h src/jval.c
	$(CC) $(CFLAGS) -c -o $@ src/jval.c

clean:
	rm -f $(OBJS) $(LIBRARY)