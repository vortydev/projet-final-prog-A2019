/*
 * Programme: main.cpp
 *
 * Projet: Travail de session
 * Auteurs: Emily Bernier et �tienne M�nard
 *
 * Cr�ation: 26 novembre 2019
 * Travail: Gestion d'inventaire
 *
 * Param�tres: Aucun
 * R�sultat: Lis les fichiers d'achats, d'inventaire et de ventes, fais des fancy math et �cris un fichier d'analyse comportant la date.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include "cleanIO.h"
#include "date.h"
#include "tableMagic.h"
#include "beeseChurger.h"

using namespace std;

void readFileToTable(string path, double table[]);
void readFileTo2Tables(string path, double table1[], string table2[]);

/* fonction: lancement du programme
 * param: int argc: nb param�tres recus de la ligne de commande
 * param: char ** argv: tableau contenant les parametres recus de ligne de commande
 * return: int: code d'erreur: 0 = aucune erreur
 */
void main (int argc, char **argv) {
	locale::global(locale{ "fr" });
	string today, hier;
	getDates(today, hier);
	cout << "Date d'aujourd'hui: " << today << endl << "Date d'hier: " << hier << endl << endl;

	string pathInventaire = "./files/Inventaires_" + hier + ".txt";
	string pathAchats = "./files/Achats_" + today + ".txt";
	string pathVentes = "./files/Ventes_" + today + ".txt";
	string pathAnalyse = "./files/Analyse_" + today + ".txt";
	//ofstream fichierAnalyse(pathAnalyse); // not yet

	string tableNom[9] = { "Boeuf", "Pain" "Laitue", "Cheddar jaune", "Cheddar blanc", "Cornichons", "Oignons", "Tomate" "Sauce" };
	string tableType[9];
	double tableQntInv[9];
	double tableQntAcht[9];
	double tableQntVentes[9] = { 0,0,0,0,0,0,0,0,0 };
	double tablePertes[9];
	double tableAnal[9];

	readFileTo2Tables(pathInventaire, tableQntInv, tableType);
	readFileTo2Tables(pathAchats, tableQntAcht, tableType);
	readFileToTable(pathVentes, tableQntVentes);

	calcPertes(tableQntInv, tableQntVentes, tablePertes);
	calcAnal(tableQntInv, tableQntAcht, tableQntVentes, tablePertes, tableAnal);

	cout << endl << "Programme par �tienne M�nard et Emily Bernier." << endl;
	system("PAUSE");
}

void readFileToTable(string path, double table[]) {
	ifstream file(path);
	string ligne;
	int index = 0;

	if (file) {
		index = 0;
		while (!file.eof()) {
			getline(file, ligne);
			addVntesQnt(ligne, table, index);
			index++;
		}

		file.close();
	}
	else cout << path << " could not be opened." << endl;
}

void readFileTo2Tables(string path, double table1[], string table2[]) {
	ifstream file(path);
	string ligne;
	int index = 0;

	if (file) {
		while (!file.eof()) {
			getline(file, ligne);
			addLineToTables(ligne, table1, table2, index);
			index++;
		}

		file.close();
	}
	else cout << path << " could not be opened." << endl;
}