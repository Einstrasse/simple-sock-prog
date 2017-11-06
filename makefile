all: tcp-client tcp-server udp-client udp-server
	echo "Build complete"
tcp-client: tcp-client.c headerFiles.h
	gcc -o tcp-client tcp-client.c -Wall
tcp-server: tcp-server.c headerFiles.h
	gcc -o tcp-server tcp-server.c -Wall
udp-client: udp-client.c headerFiles.h
	gcc -o udp-client udp-client.c -Wall
udp-server: udp-server.c headerFiles.h
	gcc -o udp-server udp-server.c -Wall
clean:
	rm tcp-server tcp-client udp-server udp-client