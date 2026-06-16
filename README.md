# AIZO_P_2
PROJEKT 2 ALGORYTMY I ZŁOŻONOŚĆ OBLICZENIOWA 
Badanie efektywności algorytmów grafowych w zależności odrozmiaru instancji oraz sposobu reprezentacji grafu w pamięci komputera.

Analizowane problemy:
  -  Wyznaczenie minimalnego drzewa rozpinającego (MTS)  - algorytm Prima i Kruskala
  -  Wyznaczenie najkrótszej ścieżki w grafie - algorytm Dijkstry i Forda-Bellmana
Każdy z algorytmów został zaimplementowany dla dwóch reprezentacji grafu w pamięci komputera:
 - macierz sąsiedztwa
 - lista następników/poprzedników
# OPCJE PLIKU KONFIGURACYJNEGO
  - testMode - (true/false) tryb sprawdzania poprawności, wypisuje wynik działania wybranego w testAlg algorytmu na grafie wczytanym z pliku testFilename
  - testFilename - plik zawierający graf do testów
  - testCasesNodeCount - ilość wierzchołków w grafie do wygenerowania
  - testCasesDensities - gęstości grafów do wygenerowania
  - testRepetitionCounter - ilość instancji problemu do wygenerowania
  - testAlg - algorytm do przetestowania (również w trybie benchmarku) 
    - ALL 
    - PRIM
    - KRUSKAL
    - DIJKSTRA
    - FORD_BELLMAN

