#include "ModelMover.h"

/* ta klasa doda³a du¿o kodu, ale przynajmniej mo¿na wygodnie umieszczaæ obiekty i je przesuwaæ na ¿ywo
	bez ponownego kompilowania;
	aby w³¹czyæ przesuwanie na ¿ywo nale¿y:
	1. do modelu (czegoœ co dziedziczy po Model.h) dodaæ instancjê klasy ModelMover
	2. do eventParams dodaæ instancjê ModelMover (t¹ z punktu 1)
	\->powy¿sze dzieje siê w Drawer.cpp CreateObjectsToDraw()

	3. jak odpalisz program, klikasz "m" na klawiaturze aby w³¹czyæ/wy³¹czyæ poruszanie
	4. klikasz x, y lub z aby wybraæ oœ, któr¹ chcesz zmieniaæ
	5. klikasz r, t lub u aby wybraæ rotacjê, translacjê, skalowanie
	6. klikasz i aby zwiêkszyæ parametr, k ¿eby zmniejszyæ
	7. aby zobaczyæ obecne koordy dajesz p (print), i na konsoli widzisz x,y,z dla obecnego ustawienia.

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
