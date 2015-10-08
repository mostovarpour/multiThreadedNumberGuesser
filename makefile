make: numberGuesser.c server.c
	gcc numberGuesser.c server.c -lpthread -o serverOut
	gcc client.c -o clientOut

clean:
	rm serverOut clientOut
