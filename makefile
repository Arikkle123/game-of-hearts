
TARGET= hearts.out
CC= gcc
CFLAGS= -ansi -g -pedantic
OBJS= cards.o ui.o deck.o player.o game.o heartRound.o heartRoundRun.o

$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)


ui.o: ui.c ui.h cards.h
	$(CC) $(CFLAGS) -c ui.c
	
deck.o: cards.h deck.c deck.h ui.c ui.h
	$(CC) $(CFLAGS) -c deck.c
	
player.o: cards.h player.c player.h deck.h ui.c ui.h
	$(CC) $(CFLAGS) -c player.c
	
game.o: cards.h game.c game.h deck.h player.h ui.c ui.h
	$(CC) $(CFLAGS) -c game.c
	
heartRound.o: cards.h heartRound.c heartRound.h player.h deck.h ui.c ui.h
	$(CC) $(CFLAGS) -c heartRound.c

heartRoundRun.o: cards.h heartRound.c heartRound.h player.h deck.h heartRoundRun.c ui.c ui.h
	$(CC) $(CFLAGS) -c heartRoundRun.c
	
clean:
	rm -f $(TARGET) $(OBJS)
