a.out : client_uniform.o impl.o
	gcc client_uniform.o impl.o -lm

Ass1_client.o : client_uniform.c header.h
	gcc -c client_uniform.c

Ass1_impl.o : impl.c header.h
	gcc -c impl.c -lm
