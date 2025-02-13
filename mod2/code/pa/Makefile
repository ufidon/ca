CC=gcc
CFLAGS=-Wall -O1

ISADIR = .
YAS=$(ISADIR)/yas
YIS=$(ISADIR)/yis
PIPE=$(ARCHDIR)/pipe/pipe_tty
SEQ=$(ARCHDIR)/seq/seq_tty
SEQ+ =$(ARCHDIR)/seq/seq+_tty


.SUFFIXES:
.SUFFIXES: .c .s .o .ys .yo .yis .pipe .seq .seq+ .txt

FILES= demo-basic.yo demo-h0.yo demo-h1.yo demo-h2.yo demo-h3.yo \
	 demo-j.yo  demo-ret.yo demo-luh.yo demo-retb.yo \
	 demo-exc1.yo demo-exc2.yo demo-exc3.yo

all: $(FILES) demo-j.txt demo-ret.txt demo-retb.txt \
	 demo-exc1.txt demo-exc2.txt demo-exc3.txt
.c.s:
	$(CC) $(CFLAGS) -S $*.c

.ys.yo:
	$(YAS) $*.ys

# Extracting code fragments
.yo.txt:
	egrep "\|   #|:[ a-f0-9]*\|" $*.yo | \
	perl -ne "s/:[ a-f0-9]+\|/:/; s/[ ]*\|[ ]*#/#/; print;" > $*.txt

.yo.yis: $(YIS)
	$(YIS) $*.yo > $*.yis

.yo.pipe: $(PIPE)
	$(PIPE) -t $*.yo  > $*.pipe

.yo.seq: $(SEQ)
	$(SEQ) -t $*.yo > $*.seq

.yo.seq+: $(SEQ+)
	$(SEQ+) -t $*.yo > $*.seq+

clean:
	rm -f *.o *.yis *.yuc *~ *.yo *.pipe *.seq *.seq+
