#pragma once
#include "Model.h"
/* TUTORIAL U¯YWANIA TEJ KLASY
	zobacz implementacjê Draw() w Example1.cpp ];->
	
	ogó³em:
	jest tutaj Draw(), NextFrame() do rysowania i przygotowywania modelu do nastêpnej klatki,
	zgodnie z konwencj¹ któr¹ przedstawi³ VANdrzejewski na labkach;
	
	dodatkowo:
	LoadDefautlPerspectiveMatrix(); -> przed rysowaniem w Draw() wypada to odpaliæ ¿eby powi¹zaæ obiekt z kamer¹

	LoadModelFromObjFile(std::string fileName); -> wczytuje model z pliku .obj, ale uwaga!
	implementacja tego pozostawia wiele do ¿yczenia, szczególnie jeœli weŸmiesz pod uwagê nieustanne operacje na stringach
	jako quick-fix zrobi³em ExportLoadedMatrixesToFile - który zapisuje wczytane i przeliczone macierze modelu do
	dwóch plików txt (w ka¿ej linii s¹ 3 liczby double),
	po takiej operacji (jednorazowo) mo¿esz w kreatorach modeli u¿yæ QuickLoadFromFiles, który na dwóch w¹tkach (serio?:P)
	wczytuje te dwa pliki. Dzia³a lepiej. TESTED.
	how to:
	1. przed pierwszym uruchomieniem dajesz w konstruktorze:
	this->LoadModelFromObjFile("plik.obj");
	this->ExportLoadedMatrixesToFile("plik"); BEZ ROZSZERZEN ANI INNYCH CYRKÓW
	2. potem zmieniasz konstruktor na:
	this->QuickLoadFromFiles("plik");

	LoadMaterialFromMtlFile(std::string fileName); ->na przysz³oœæ, do wczytywania materia³ów. Poleg³em przy pierwszej
	próbie u¿ycia ich

	a! ¿eby obiekt siê rzeczywiœcie narysowa³:
	1. musisz go utworzyæ w metodzie CreateObjectsToDraw() w Drawer.cpp (dodajesz go do s³ownika - sprawdŸ jak to tam wygl¹da)
	jeœli masz lepszy pomys³ na ogarniêcie wszystkich modeli, czuæ wolnym do zmiana
	2. musisz wywo³aæ na tym obiekcie metodê Draw() w Display() w Drawer.cpp. NextFrame() wywo³uje Drawer samodzielnie.
	3. powinno dzia³aæ.

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

