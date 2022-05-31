game:
	make -f client.mk
	make -f server.mk

clean:
	make clean -f client.mk
	make clean -f server.mk