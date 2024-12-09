Przemytnicy - Algorytm Najkrótszej Ścieżki

Opis Projektu:

Ten projekt ma na celu rozwiązanie problemu przewozu metali przez granicę z jak najmniejszym kosztem
przy użyciu algorytmu Dijkstry. Bajtoccy kupcy zamierzają korzystać z alchemicznych procesów przemiany metali,
aby ominąć wysokie cła na złoto.

Podejście:

1. Modelowanie problemu jako graf:
   - Metale są wierzchołkami grafu.
   - Procesy przemiany są krawędziami grafu, z wagami odpowiadającymi kosztowi przemiany.

2. Algorytm Dijkstry:
   - Znalezienie najkrótszej ścieżki w grafie, czyli najtańszej sekwencji przemian metali.

3. Kopiec minimalny:
   - Użycie własnej implementacji kopca minimalnego (priorytetowej kolejki), aby efektywnie realizować algorytm Dijkstry.

Algorytmy:

- Algorytm Dijkstry: Znajduje najkrótsze ścieżki z jednego źródła do wszystkich innych wierzchołków w grafie o nieujemnych wagach krawędzi.
- Kopiec Minimalny: Priorytetowa kolejka używana w algorytmie Dijkstry do wybierania wierzchołków z najmniejszym kosztem.

Zastosowane Struktury Danych:

- Graf: Reprezentowany jako lista sąsiedztwa.
- Kopiec Minimalny: używany do efektywnego zarządzania wierzchołkami w algorytmie Dijkstry.

Zalety i Ograniczenia:

Zalety:
- Efektywne znajdowanie najkrótszych ścieżek dzięki algorytmowi Dijkstry.
- Elastyczność w modelowaniu problemu jako graf.

Ograniczenia:
- Algorytm Dijkstry wymaga grafu z nieujemnymi wagami krawędzi.
- Dla bardzo dużych grafów lub dużych zbiorów danych, czas obliczeń może być długi.
