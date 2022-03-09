Canalyse:
	gcc -o canalyse coursework.c

clean:
	rm *.o
	rm canalyse

install:
	mv canalyse /bin/
	chmod +x /bin/canalyse
