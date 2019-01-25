# PROJEKT ZALICZENIOWY Z PRZEDMIOTU ZASTOSOWANIA PAKIETU GEANT4 W FIZYCE JĄDROWEJ
## How to run it

1). Compilation

```bash
$ mkdir build
$ cd build
$ cmake .. && make

```
2). Running (in build directory)
```bash
$ ./LaBr3
```

## Cel projektu

Celem projektu było uzyskanie funkcji odpowiedzi układu detektorów LaBr3 rejestrującego promieniowanie gamma emitowane przez jon o określonej energii kinetycznej, tak aby zaobserwować efekt Dopplera.

## Geometria układu
Układ detektorów LaBr3 otacza radialnie punkt emisji promieniowania gamma. Ponieważ celem projektu jest badanie efektu Dopplera zdecydowano się rozmieścić detektory w tylko jednej płaszczyźnie (zagadnienie jest symetryczne).
Poniższa animacja przedstawia przykładową symulację (z widocznymi rozproszeniami Comptonowskimi) i rozmieszczenie detektorów w przestrzeni.
![Wizualizacja](visualisation.gif)


Natomiast dokładny opis geometrii wraz z numerami detektorów oraz przyjętym układem współrzędnych przedstawia rysunek poniżej. Wiązka jonów porusza się z parametrem ```beta``` wzdłuż osi y.
![Geometria układu](geometry.svg)

## Wyniki
Wyniki symulacji zamieszczono w folderze ```results```.
Pierszą symulację wykonano dla materiału detektora NaI, ponieważ zaimplementowanie LaBr3 wymagało stworzenia mikstury. Potencjalnie mogło to spowodować jakieś błędy, więc początkowo sprawdzono czy implementacja efektu Dopplera działa dobrze dla znanego materiału detektora.
![NaI](results/NaI_doppler_effect.png)

Następnie zaimplementowano LaBr3. Wynik zamieszczono poniżej.
![LaBr3](results/LaBr3_doppler_effect.png)

W obu przypadkach emitowany był kwant gamma o energii ***3000 keV***. Na wszystkich widmach widoczne są piki ucieczki oraz linia 511 keV. Widać również przesunięcia dopplerowskie, a ich kierunek i wielkość odpowiada umiejscowieniu detektora w układzie.


## Author
Ewa Adamska


This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
