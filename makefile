make: numberGuesser.c server.c
	g++ numberGuesser.c server.c -lpthread -o out

clean:
	rm out
