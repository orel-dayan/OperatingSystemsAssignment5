CC = gcc
CFLAGS = -pthread

all: st_pipeline

st_pipeline: Math.o Queue.o ActiveObject.o st_pipeline.o
	$(CC) $(CFLAGS) -o st_pipeline Math.o Queue.o ActiveObject.o st_pipeline.o -lm 

Math.o: Math.c Math.h
	$(CC) $(CFLAGS) -c Math.c

Queue.o: Queue.c Queue.h
	$(CC) $(CFLAGS) -c Queue.c

ActiveObject.o: ActiveObject.c ActiveObject.h Queue.h
	$(CC) $(CFLAGS) -c ActiveObject.c

st_pipeline.o: st_pipeline.c ActiveObject.h Queue.h Math.h
	$(CC) $(CFLAGS) -c st_pipeline.c

clean:
	rm *.o st_pipeline
