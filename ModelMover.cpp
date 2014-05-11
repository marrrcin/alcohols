#include "ModelMover.h"

/* ta klasa doda�a du�o kodu, ale przynajmniej mo�na wygodnie umieszcza� obiekty i je przesuwa� na �ywo
	bez ponownego kompilowania;
	aby w��czy� przesuwanie na �ywo nale�y:
	1. do modelu (czego� co dziedziczy po Model.h) doda� instancj� klasy ModelMover
	2. do eventParams doda� instancj� ModelMover (t� z punktu 1)
	\->powy�sze dzieje si� w Drawer.cpp CreateObjectsToDraw()

	3. jak odpalisz program, klikasz "m" na klawiaturze aby w��czy�/wy��czy� poruszanie
	4. klikasz x, y lub z aby wybra� o�, kt�r� chcesz zmienia�
	5. klikasz r, t lub u aby wybra� rotacj�, translacj�, skalowanie
	6. klikasz i aby zwi�kszy� parametr, k �eby zmniejszy�
	7. aby zobaczy� obecne koordy dajesz p (print), i na konsoli widzisz x,y,z dla obecnego ustawienia.

*/

ModelMover::ModelMover()
{
	this->translateX = 0;
	this->translateY = 0;
	this->translateZ = 0;
	this->scaleX = 1;
	this->scaleY = 1;
	this->scaleZ = 1;
	this->rotateAngle = 0;
	this->rotateX = 1;
	this->rotateY = 0;
	this->rotateZ = 0;
	this->isEnabled = false;
}


ModelMover::~ModelMover()
{
}
