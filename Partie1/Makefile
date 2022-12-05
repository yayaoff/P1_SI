CC=gcc
CFLAGS=-Wall -Werror -g -w
LIBS=-lpthread
MAKEFLAGS += --silent

fec_philo:
	@$(CC) utils/philo.c -o fec_philo.out $(CFLAGS) $(LIBS)

fec_prod_cons:
	@$(CC) utils/prod_cons.c -o fec_prod_cons.out $(CFLAGS) $(LIBS)

fec_wr_read:
	@$(CC) utils/writer_readers.c -o fec_wr_read.out $(CFLAGS) $(LIBS)

clean :
	rm -f csv/*.csv
	rm -f png/*.png

graph:
	./experiments.sh
	python3 utils/plots.py