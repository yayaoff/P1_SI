CC=gcc
CFLAGS=-Wall -Werror -g -w
LIBS=-lpthread
MAKEFLAGS += --silent

make:
	@$(CC) utils/philo.c -o fec_philo.out $(CFLAGS) $(LIBS)
	@$(CC) utils/prod_cons.c -o fec_prod_cons.out $(CFLAGS) $(LIBS)
	@$(CC) utils/writer_readers.c -o fec_wr_read.out $(CFLAGS) $(LIBS)

clean :
	rm -f csv/*.csv
	rm -f png/*.png
	rm -f *.out
	rm -f *.txt

test:
	make clean
	make
	./experiments.sh
	python3 utils/plots.py