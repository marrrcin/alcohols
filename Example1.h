#pragma once
#include "Model.h"
/* TUTORIAL U�YWANIA TEJ KLASY
	zobacz implementacj� Draw() w Example1.cpp ];->
	
	og�em:
	jest tutaj Draw(), NextFrame() do rysowania i przygotowywania modelu do nast�pnej klatki,
	zgodnie z konwencj� kt�r� przedstawi� VANdrzejewski na labkach;
	
	dodatkowo:
	LoadDefaultPerspectiveMatrix(); -> przed rysowaniem w Draw() wypada to odpali� �eby powi�za� obiekt z kamer�

	LoadModelFromObjFile(std::string fileName); -> wczytuje model z pliku .obj, ale uwaga!
	implementacja tego pozostawia wiele do �yczenia, szczeg�lnie je�li we�miesz pod uwag� nieustanne operacje na stringach
	jako quick-fix zrobi�em ExportLoadedMatrixesToFile - kt�ry zapisuje wczytane i przeliczone macierze modelu do
	dw�ch plik�w txt (w ka�ej linii s� 3 liczby double),
	po takiej operacji (jednorazowo) mo�esz w kreatorach modeli u�y� QuickLoadFromFiles, kt�ry na dw�ch w�tkach (serio?:P)
	wczytuje te dwa pliki. Dzia�a lepiej. TESTED.
	how to:
	1. przed pierwszym uruchomieniem dajesz w konstruktorze:
	this->LoadModelFromObjFile("plik.obj");
	this->ExportLoadedMatrixesToFile("plik"); BEZ ROZSZERZEN ANI INNYCH CYRK�W
	2. potem zmieniasz konstruktor na:
	this->QuickLoadFromFiles("plik");

	LoadMaterialFromMtlFile(std::string fileName); ->na przysz�o��, do wczytywania materia��w. Poleg�em przy pierwszej
	pr�bie u�ycia ich

	a! �eby obiekt si� rzeczywi�cie narysowa�:
	1. musisz go utworzy� w metodzie CreateObjectsToDraw() w ModelFactory.cpp (dodajesz go do s�ownika - sprawd� jak to tam wygl�da)
	je�li masz lepszy pomys� na ogarni�cie wszystkich modeli, czu� wolnym do zmiana
	2. musisz wywo�a� na tym obiekcie metod� Draw() w Display() w Drawer.cpp (fix: jest ju� p�tla). NextFrame() wywo�uje Drawer samodzielnie.
	3. powinno dzia�a�.

	MZ

*/
class Example1 : public Model
{
private:
	
public:
	Example1();
	~Example1();
	virtual void Draw();
	virtual void NextFrame();

};

