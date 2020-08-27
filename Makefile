all: compile link

build: compile link run

compile:
	g++ -c *.cpp

link:
	g++ *.o -o Main -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm *.o *.exe

run:
	Main.exe