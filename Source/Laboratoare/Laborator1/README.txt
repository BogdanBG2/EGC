	README Lab 1

Variabile folosite:
	backgroundCode 
		- codul de intensitate a fundalului
		- ia valori in intervalul 0-10
	modelCode
		- codul modelului de la task-ul 4
		- ia valori de la 0 la 2
	modelName
		- numele modelului curent
	posX, posY si posZ
		- coordonatele obiectului manevrabil
	jumpingHeight
		- inaltimea la care se afla cutia in timpul sariturii
	jumpUp
		- indica daca cutia este in miscarea ascendenta a sariturii
	isJumping
		- indica daca cutia este sau nu intr-o saritura
	
Comenzi:
	F - schimba culoarea fundalului de la negru la albastru;
	  - are 9 stari intermediare; cand fundalul ajunge sa fie 
	  un albastru foarte intens, la urmatoarea apasare va fi negru
	M - schimba modelul; cicleaza in 3 stari: cutie, sfera si ceainic
	W - muta obiectul mutabil in fata
	S - muta obiectul mutabil in spate
	A - muta obiectul mutabil in stanga
	D - muta obiectul mutabil in dreapta
	E - muta obiectul mutabil in sus
	Q - muta obiectul mutabil in jos
	SPACE - face cutia din stanga sa sara (stanga din primul 
		sistem de referinta)
	LeftShift - tripleaza viteza de deplasare a obiectului mutabil
	LeftCtrl - injumatateste viteza de deplasare a obiectului mutabil
	