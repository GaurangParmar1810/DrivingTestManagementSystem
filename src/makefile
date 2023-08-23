# you can put include files in this directory
IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

# directory where object files will be created
ODIR=obj
# you can put library files in this directory
LDIR =../lib
# looks for library libm.so or libm.a
LIBS=-pthread

# create string with ../include/<header filename> in our case ../include/myheader.h
_DEPS = header.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# create string with obj/<object filename> in our case obj/add.o and obj/sub.o  (obj folder will be created under current i.e. source directory)
_LIBOBJ = display_data.o  structures.o make_list.o  person_regeister.o  test.o string_attempt.o run.o
LIBOBJ = $(patsubst %,$(ODIR)/%,$(_LIBOBJ))

LIBSRC = display_data.c structures.c make_list.c person_regeister.c test.c string_attempt.c run.c
_APPOBJ = main.o
APPOBJ = $(patsubst %,$(ODIR)/%,$(_APPOBJ))

	 
$(LDIR)/libmyfunc.so:$(LIBOBJ)
	$(CC) -shared -o $@ $^

$(ODIR)/display_data.o: display_data.c
	$(CC) -c -fPIC -o $@ $< $(CFLAGS)

$(ODIR)/structures.o: structures.c
	$(CC) -c -fPIC -o $@ $< $(CFLAGS)

$(ODIR)/make_list.o: make_list.c
	$(CC) -c -fPIC -o $@ $< $(CFLAGS)

$(ODIR)/person_regeister.o: person_regeister.c
	$(CC) -c -fPIC -o $@ $< $(CFLAGS)
	
$(ODIR)/test.o: test.c
	$(CC) -c -fPIC -o $@ $< $(CFLAGS)
	
$(ODIR)/string_attempt.o: string_attempt.c
	$(CC) -c -fPIC -o $@ $< $(CFLAGS)
	
$(ODIR)/run.o: run.c
	$(CC) -c -fPIC -o $@ $< $(CFLAGS)

$(APPOBJ): main.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
../bin/main.out: $(APPOBJ) $(LDIR)/libmyfunc.so
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
.PHONY: clean

# removes object files and temporary files created with ~ at the end of file name in current i.e. source and include directory
clean: 
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
	rm -f call_function.out $(LDIR)/libmyfunc.so
	
.PHONY: all
all: $(LDIR)/libmyfunc.so ../bin/main.out $(APPOBJ)  
