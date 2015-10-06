make: numberGuesser.c server.c
	g++ numberGuesser.c server.c -lpthread -o serverOut
	gcc client.c -o clientOut

clean:
	rm serverOut clientOut
