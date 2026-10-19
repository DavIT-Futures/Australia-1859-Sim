# 🏝️ Wyspa (Island) — Symulacja Ekosystemu Drapieżnik-Ofiara

[![C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B)
[![Borland C++Builder 6](https://img.shields.io/badge/IDE-Borland%20C%2B%2BBuilder%206-red.svg)](https://en.wikipedia.org/wiki/C%2B%2BBuilder)
[![Platform](https://img.shields.io/badge/Platform-Windows%20(Win32)-lightgrey.svg)](https://microsoft.com/windows)
[![Author](https://img.shields.io/badge/Author-Dawid%20Domaga%C5%82a%20(DavIT--Futures)-orange.svg)](https://github.com/DavIT-Futures)

Projekt symulacji ekosystemu wyspy (drapieżnik–ofiara) zrealizowany w **styczniu 2005 roku** w ramach kursu **Projekt z Programowania Obiektowego** na **Wydziale Elektroniki Politechniki Wrocławskiej**.

Aplikacja modeluje interakcje w zamkniętym ekosystemie wyspy pomiędzy **roślinożercami (króliki)**, **drapieżnikami (lisy)** a **zasobami środowiskowymi (wegetacja trawy)** na dynamicznie generowanym, konfigurowalnym terenie.

---

## 📸 Galeria i Zrzuty Ekranu

| Widok Symulacji Wyspy | Panel Sterowania i Parametry Ekosystemu |
|:---:|:---:|
| ![Wyspa Główna](docs/screenshots/7.png) | ![Panel Generowania](docs/screenshots/1.png) |

| Generator Zatok i Wybrzeża | Panel Statystyk Populacji |
|:---:|:---:|
| ![Generator Zatok](docs/screenshots/2.png) | ![Statystyki](docs/screenshots/7g.png) |

---

## 🌟 Główne Funkcjonalności

### 1. Proceduralny Generator Wyspy
* **Kształtowanie konturu:** Generowanie lądu na bazie obwiedni geometrycznej, na którą nakładane są 4 fale sinusoidalne o regulowanej amplitudzie oraz szum losowy.
* **Generator zatok:** Algorytm rombowy z kontrolowaną nieregularnością i wielkością zatok (możliwość generowania zatok głębokich lub drobnych zatoczek plażowych).
* **Filtry morfologiczne i wygładzanie:** Wygładzanie brzegów oparte o automaty komórkowe z maską krzyżową (naprzemienne operacje dylatacji i erozji lądu i wody).
* **Gradientowe strefy klimatyczno-terenowe:**
  - Woda słona (strefa nieprzekraczalna dla zwierząt)
  - Plaża
  - Pas trawiasty (obszar wegetacji)
  - Śnieg
  - Góry i wulkan (bariery terenowe)
* **Ziarnistość terenu:** Płynne przejścia kolorystyczne (gradient) z losowym szumem zaburzającym granice stref.

### 2. Symulacja Życia i Ekologii (Króliki & Lisy)
* **Króliki (Ofiary):**
  - Metabolizm: spalanie energii (w dżulach) podczas każdego ruchu,
  - Głód i poszukiwanie pożywienia: zjadanie kęp trawy i uzupełnianie zapasów energetycznych,
  - Zmysły: dynamiczny zasięg widzenia lisów i ucieczka przed drapieżnikiem,
  - Rozmnażanie: wiek dojrzałości płciowej, okres ciąży, narodziny potomstwa,
  - Śmiertelność: śmierć ze starości, z głodu lub w wyniku upolowania przez lisa.
* **Lisy (Drapieżniki):**
  - Polowanie: wykrywanie królików, pościg, zjadanie ofiar,
  - Zapotrzebowanie energetyczne: większe tempo metabolizmu wymagające stałych łowów,
  - Rozród i watahy: tworzenie stad i rozprzestrzenianie populacji drapieżników.
* **Wegetacja Trawy:**
  - Dynamiczny wzrost trawy zależny od współczynnika wegetacji,
  - Odnawianie się wyjedzonych kęp po określonym czasie,
  - Możliwość globalnego zresetowania lub przyspieszenia wegetacji.
* **Inżynieria Genetyczna i Priorytety Behawioralne:**
  - Zaawansowany panel edycji indywidualnych parametrów osobników,
  - Hierarchia potrzeb (jedzenie, ucieczka, rozród),
  - Tryby specjalne ("Neo jako królik-komandos").
* **Panel Statystyk:**
  - Bieżący licznik populacji lisów i królików,
  - Analiza przyczyn zgonów (z głodu, ze starości, upolowane).

---

## 📁 Struktura Repozytorium

```
Wyspa/
├── ver16/                 # Ostateczna, najbardziej dopracowana wersja projektu (BCB6)
│   ├── wyspa.bpr          # Plik projektu Borland C++Builder 6
│   ├── wyspa.cpp          # Punkt wejścia WinMain
│   ├── glowny.cpp / .h    # Główne okno aplikacji, pętla zdarzeń i generator wyspy
│   ├── glowny.dfm         # Definicja formularza VCL
│   ├── Kroliki.cpp / .h   # Zarządca stada królików
│   ├── krolik.cpp / .h    # Klasa pojedynczego królika
│   ├── Lisy.cpp / .h      # Zarządca populacji lisów
│   ├── Lis.cpp / .h       # Klasa pojedynczego lisa
│   ├── zwierze.cpp / .h   # Klasa bazowa zwierzęcia (dziedziczenie OOP)
│   ├── kolejka.cpp / .h   # Kolejka priorytetowa / dyspozytor zdarzeń
│   ├── PlodK.cpp / .h     # Obsługa rozrodu królików
│   ├── PlodL.cpp / .h     # Obsługa rozrodu lisów
│   ├── nic.h              # Pomocnicze stałe i definicje
│   ├── wyspa.res          # Zasoby binarne Win32
│   ├── *.bmp              # Ikony i sprite'y zwierząt (lis, królik, kursor)
│   └── wyspa.exe          # Gotowy, skompilowany plik wykonywalny Win32
├── ver15/                 # Wersja pośrednia (etap rozwoju projektu)
├── ver14/                 # Wczesna wersja prototypowa
├── docs/                  # Dokumentacja i materiały archiwalne
│   ├── wyspa.doc          # Oryginalna dokumentacja projektowa PWr (2005)
│   └── screenshots/       # Zrzuty ekranu w formacie PNG
├── plany.txt              # Oryginalne notatki autora z prac nad projektem
├── .gitignore             # Ignorowanie plików tymczasowych Borland (.obj, .tds, .~*)
└── README.md              # Niniejsza dokumentacja
```

---

## 🚀 Uruchomienie Programu

Skompilowana aplikacja znajduje się w folderze `ver16/wyspa.exe`.

* Jest to 32-bitowy plik wykonywalny Win32 ze **statycznie zlinkowaną biblioteką VCL (Visual Component Library)**.
* **Nie wymaga żadnych zewnętrznych bibliotek DLL ani instalatorów.**
* **Działa natywnie na współczesnych systemach Windows (Windows 10, Windows 11 64-bit)** pod warstwą WOW64.
* Wystarczy dwukrotnie kliknąć `ver16/wyspa.exe`, aby uruchomić symulator.

---

## 🛠️ Kompilacja ze Źródeł

Kod źródłowy został napisany z wykorzystaniem biblioteki **VCL** dedykowanej dla środowiska **Borland C++Builder 6.0**:

1. Otwórz projekt `ver16/wyspa.bpr` w środowisku **Borland C++Builder 6.0** (lub kompatybilnym Embarcadero RAD Studio / C++Builder z obsługą VCL).
2. Wybierz konfigurację `Release` lub `Debug`.
3. Uruchom kompilację skrótem `Project -> Make` (`Ctrl+F9`) lub `Project -> Build` (`Shift+F9`).

---

## 👨‍💻 Autor

* **Dawid Domagała** ([@DavIT-Futures](https://github.com/DavIT-Futures))
* Politechnika Wrocławska, Wydział Elektroniki (2005)
