bookKeeper: Address.o Patron.o Charge.o Material.o Menu.o bookKeeper.o
	g++ Address.o Patron.o Charge.o Material.o Menu.o bookKeeper.o -o bookKeeper -l mysqlcppconn

Material.o: Classes/Material.cpp
	g++ -c Classes/Material.cpp

Charge.o: Classes/Charge.cpp
	g++ -c Classes/Charge.cpp

Patron.o: Classes/Patron.cpp
	g++ -c Classes/Patron.cpp

Address.o: Classes/Address.cpp
	g++ -c Classes/Address.cpp

Menu.o: Classes/Menu.cpp
	g++ -c Classes/Menu.cpp

bookKeeper.o: bookKeeper.cpp
	g++ -c bookKeeper.cpp

clean:
	rm -f *.o
	rm -f bookKeeper

run:
	./bookKeeper
