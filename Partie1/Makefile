CC=gcc
CFLAGS=-Wall -Werror -g 
LIBS=-lpthread
MAKEFLAGS += --silent

fec_philo:
	@$(CC) utils/philo.c -o fec_philo $(CFLAGS) $(LIBS)

fec_prod_cons:
	@$(CC) utils/prod_cons.c -o fec_prod_cons $(CFLAGS) $(LIBS)
fec_wr_read:
	@$(CC) utils/writer_readers.c -o fec_wr_read $(CFLAGS) $(LIBS)

clean:
	rm -f *.csv
	rm -f *.txt

graph:
	./script
	python3 plots.py



	

