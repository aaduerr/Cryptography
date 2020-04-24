OBJS = scanner.o funct.o cryptography.o
OOPTS = -Wall -Wextra -g -c -std=gnu99
LOPTS = -Wall -Wextra -g -std=gnu99

cryptography : $(OBJS)
	gcc $(LOPTS) -o cryptography $(OBJS)

cryptography.o : cryptography.c funct.h scanner.h
	gcc $(OOPTS) cryptography.c

funct.o : funct.c funct.h scanner.h
	gcc $(OOPTS) funct.c

scanner.o : scanner.c scanner.h
	gcc $(OOPTS) scanner.c

clean :
	rm -f $(OBJS) cryptography

test :	cryptography
	./cryptography
