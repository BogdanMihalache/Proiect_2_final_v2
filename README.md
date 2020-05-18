# Proiect_2_final_v2

Implementarea curenta consta in calcularea pozitiilor prin care trebuie sa treaca
robotul pentru a acoperi aria din interiorul camerei.
Robotul va avea o traiectorie de spirala, incepand de la unul dintre colturile
camerei si deplasandu-se catre centru, urmand laturile poligonului dat.

Primul pas este pozitionarea robotului intr-unul din colturile poligonului
prin intermediul functiei init() din structura Robot.

Robotul retine un poligon pe care trebuie sa il parcurga, care se micsoreaza cu
fiecare latura parcursa. In urma micsorarii poligonului unele colturi ajung sa dispara
(sunt decupate), acestea raman totusi in poligon, dar sunt suprapuse cu colturi deja
existente. (Astfel se poate ajunge in situatia in care poligonul sa ajunga la forma
de patrat, dar sa contina 8 colturi.)

In deplasarea catre urmatorul colt, robotul tine cont de aria ramasa libera din dreptul
coltului si face un pas suplimentar pentru completarea acestei arii (daca are loc de peretii
camerei). De asemenea, robotul tine cont si de colturile decupate in urma micsorarii ariei
si efectueaza pasi suplimentari pentru acoperirea acestora daca este nevoie (compensare).

Robotul se opreste atunci cand toate colturile poligonului se suprapun,
cand raman cu o singura dreapta (care de altfel nu reprezinta o arie) 
sau cand aria ramasa poate fi acoperita printr-o singura deplasare.

Fisierul de input trebuie sa contina raza robotului, numarul de colturi ale poligonului
si coordonatele colturilor.

Format-ul fisierului de input:

R (raza robotului)
N (numarul de colturi ale camerei)
N linii care contin coordonatele pe x si y ale fiecarui colt

exemplu de input:

5
3
0 0
100 0
0 100

Output-ul este format din randuri de coordonate corespunzatoare fiecarei pozitii
prin care trece robotul.
Fiecare rand de output contine coordonatele pozitiei robotului urmate de coordonatele
colturilor ariei pe care o mai are de acoperit robotul.
