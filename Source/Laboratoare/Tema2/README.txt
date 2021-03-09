README TEMA 2 EGC
	Bogdan - Andrei Buga, 332CB

Platforme
	Generare:
		Platformele au fost gandite precum cuburi cu centrul in (0,0,0) si latura 1.
		Acestea sunt redimensionate astfel:
			- grosime de 0.1
			- latime de 1
			- lungime variabila, intre 2 si 5
		Culoarea platformei are urmatoarele probabilitati:
			- 24 / 35 albastru
			- 3 / 35 verde
			- 2 / 35 galben
			- 2 / 35 portocaliu
			- 2 / 35 magenta
			- 1 / 35 rosu
			- 1 / 35 turcoaz
		Pentru a determina pe ce coloane vom avea platforme in randul urmator, folosim o variabila aleatoare de 3 biti,
		in care minim 2 dintre cei 3 biti sunt 1. Acesti biti determina pe ce coloane vom avea platformele viitoare.
		Aceastea apar atunci cand platformele pe care sta jucatorul ies din ecran.
		
	Schimbarea culorii dupa ce a aterizat personajul:
		Dupa ce jucatorul a sarit si se detecteaza o coliziune intre jucator si platforma,
		jucatorul ramane pe platforma, iar platforma devine mov.
		
		Se mai considera aterizare si cand jucatorul a cazut de pe o platforma 
		si se detecteaza coliziune cu o alta platforma atunci cand
		yJucator >= 0.
		
	Poziționarea inițială corectă:
		La inceput, avem 3 platforme albastre urmate de 3 platforme verzi, cate una pe fiecare coloana.
	
Personajul
	Deplasare:
		Jucatorul poate accelera cu W, decelera cu S, si poate sa se deplaseze stanga-dreapta cu A si D.
		Acesta sare de pe SPACE.
	
	Animare in shader:
		Am creat mai multe shadere pentru juactor, cate unul pentru fiecare tip de power-up:
			verde - se alungeste de 2 ori
			galben - se contracta de 2 ori
			turcoaz - se schimba din sfera in diamant
			portocaliu - se schimba din sfera intr-o forma... ciudata : roata eliptica cu laterale conice
	
	1st / 3rd person camera:
		Cand suntem in modul "3rd Person Camera", camera este mereu in spatele jucatorului.
		Cand suntem in modul "1st Person Camera", camera va fi mereu la pozitia jucatorului si, 
		in acest caz, sfera jucatorului nu va fi "rendered" pe ecran.
		Indiferent de modul camerei, jucatorul se va uita mereu in fata (pe axa OZ-), pe verticala (up = (0,1,0)).
		
	Animarea personajului atunci când cade de pe platforme:
		Atunci cand jucatorul nu mai este pe nicio platforma, acesta va cadea pana cand ajunge sa nu mai fie vizibil pe ecran.
		Odata ce iese din cadrul ecranului, jocul se va termina.
		
Coliziuni
	Am avut nevoie de o singura coliziune: sfera - paralelipiped.
	In implementarea acesteia, am verificat mai intai daca avem coliziune pe fiecare dimensiune;
	in cazul in care nu avem,
	verificam daca distanta dintre cele 2 obiecte este mai mica sau egala decat raza jucatorului.
	
Interfata cu utilizatorul
	Pentru obiectele de interfata, consideram numai matricea Model in shader, fara sa tinem cont si de View si Projection.
	Se vor afisa urmatoarele lucruri:
		Bara de combustibil (stanga-jos)
		Bara de viteza (dreapta-jos)
		Indicator de micsorare (stangs-sus)
		Timp ramas la viteza ridicata
		Timp ramas la invincibilitate

Combustibil
	Jucatorul consuma combustibil in functie de viteza sa.
	
Puteri speciale
	Pe baza probabilitatilor de mai sus, avem urmatoarele puteri:
		rosu - termina jocul
		portocaliu - mentine jucatorul la o viteza ridicata (4 s)
		galben - reduce cantitatea de combustibil ramasa
		verde - creste cantitatea de combustibil ramasa
		turcoaz - invincibilitate
		magenta - micsorare / revenire la dimensiunea normala