#define CATCH_CONFIG_RUNNER
#include <iostream>
#include "catch.h"

#include "graph.h"
#include <string>


int main() {

	Catch::Session().run();

	cout << "Working on Graphs v0.9 by Dominik Bien\n";

	Graph g;

	int auswahl = 1;

	while (auswahl >= 1 && auswahl <= 6) {
		std::cout << "Please choose:\n1) Graph einlesen\n2) Tiefensuche\n3) Breitensuche\n4) Prim\n5) Kruskal\n6)Print Graph\n0 zum Beenden\n";
		std::cin >> auswahl;

		switch (auswahl) 
		{
		case 1:
		{
			std::string filename;
			std::cout << "Dateinamen eingeben: ";
			std::cin >> filename;
			g.init(filename);
			break;
		}
		case 2:
		{
			int key;
			std::cout << "Start Key eingeben: ";
			std::cin >> key;
			if (g.depthSearchRek(key))
				std::cout << "Tiefensuche erfolgreich!" << std::endl;
			else
				std::cout << "Tiefensuche nicht erfolgreich!" << std::endl;
			break;
		}
		case 3:
		{
			int key;
			std::cout << "Start Key eingeben: ";
			std::cin >> key;
			if (g.breadthSearchIter(key))
				std::cout << "Breitensuche erfolgreich!" << std::endl;
			else
				std::cout << "Breitensuche nicht erfolgreich!" << std::endl;
			break;
		}
		case 4:
		{
			int key;
			std::cout << "Start Key eingeben: ";
			std::cin >> key;
			
			double value=g.prim(key);
			std::cout << "Kosten nach Prim MSP: " << value << std::endl;
			break;
		}
		case 5:
		{
			double value = g.kruskal();
			std::cout << "Kosten nach Kruskal MSP: " << value << std::endl;
			break;
		}
		case 6:
		{
			g.printAll();
			break;
		}
		}
	}

	system("PAUSE");
	return 0;
}