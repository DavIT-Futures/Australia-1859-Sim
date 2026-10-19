# 🇦🇺 Australia 1859 Sim (Wyspa) — Predator-Prey Island Ecosystem Life Simulator

[![C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B)
[![Borland C++Builder 6](https://img.shields.io/badge/IDE-Borland%20C%2B%2BBuilder%206-red.svg)](https://en.wikipedia.org/wiki/C%2B%2BBuilder)
[![Platform](https://img.shields.io/badge/Platform-Windows%20(Win32)-lightgrey.svg)](https://microsoft.com/windows)
[![Author](https://img.shields.io/badge/Author-Dawid%20Domaga%C5%82a%20(DavIT--Futures)-orange.svg)](https://github.com/DavIT-Futures)

[**English Overview**](#-english-overview) | [**Polska Dokumentacja**](#-polska-dokumentacja)

---

## 🌍 English Overview

### 🌿 What is This Simulation?
**Island** (*Wyspa*) is an artificial life (ALife) ecosystem simulator and cellular automata environment originally built in **January 2005** by Dawid Domagała for the Object-Oriented Programming course at Wrocław University of Science and Technology (*Politechnika Wrocławska*, Faculty of Electronics).

The project simulates a self-sustaining, emergent ecosystem on an isolated island:
1. **Procedural Island Synthesis:** The user first crafts the island geography. The land is encircled by sparkling blue ocean water with animated wave patterns, soft golden sandy beaches along the coast, expansive green grass meadows inland, rocky mountain ridges, snow-capped peaks, and impassable volcanic zones.
2. **Dynamic Grass Vegetation:** Green grass sprouts and regrows across the island terrain over time based on configurable vegetation velocity parameters.
3. **Prey (Rabbits):** Herbivorous rabbits roam the grassy plains. Every step consumes metabolic energy (measured in Joules). When hungry, rabbits search for grass to graze on. As they feed and age, they reach sexual maturity, undergo gestation, and give birth to offspring.
4. **Predators (Foxes):** Carnivorous foxes are introduced to the island. Foxes hunt rabbits for food, manage their own metabolic burn, form packs, and reproduce when well-fed.
5. **The Closed Ecological Cycle:** *Grass grows &rarr; Rabbits graze on grass &rarr; Foxes hunt rabbits &rarr; Overhunting causes foxes to starve &rarr; Vegetation recovers &rarr; The cycle continues endlessly in a dynamic Lotka-Volterra equilibrium.*

---

### 🇦🇺 The Historical Connection: The Australian Rabbit Crisis of 1859
This simulation closely mirrors one of the most famous ecological events in history: **the Australian rabbit plague**.

> In October 1859, 24 European wild rabbits were released in Victoria, Australia by Thomas Austin for recreational hunting. With virtually no native natural predators and a vast continent of lush flora, the rabbit population exploded exponentially into hundreds of millions. They devastated farmland, triggered catastrophic soil erosion, and decimated indigenous vegetation.
> 
> To curb the invasion, **red foxes** were introduced to Australia in 1871. However, instead of simply containing the rabbits, foxes established their own predatory pressure and severely threatened native wildlife—creating a classic real-world demonstration of **predator-prey-vegetation dynamics, invasive species pressure, and ecological carrying capacity**, exactly as modeled in this simulator.

---

### 🎮 Key Gameplay & Simulation Mechanics
* **Island Generator:**
  * Procedural contour synthesis combining geometric bounding boxes with 4 sinusoidal wave functions of customizable amplitude and random noise.
  * Diamond-algorithm coastal bay generator for carving natural fjords and coves into the coastline.
  * Cellular automata smoothing filters (alternating morphological dilation and erosion using cross-shaped masks).
  * Color gradient terrain zones with noise grain: *Salt Water &rarr; Sand Beach &rarr; Grassland &rarr; Snow &rarr; Mountains & Volcano*.
* **Animal Behavioral AI & Genetics:**
  * Real-time priority hierarchy (eating, fleeing predators, mating).
  * Individual metabolism (Joules per action), hunger threshold, gestation duration, eyesight radius, and lifespan.
  * Behavioral customization and easter eggs (including *"Neo the Commando Rabbit"*).
* **Live Statistics Dashboard:**
  * Real-time counters of active rabbit and fox populations.
  * Detailed mortality analytics: deaths from old age, starvation, or predation.
* **Plug & Play Retro Binary:**
  * Fully standalone Win32 executable (`ver16/wyspa.exe`) statically linked with Borland VCL.
  * Runs natively on **Windows 10 & Windows 11 64-bit** with zero installation or external DLL dependencies.

---

## 📸 Screenshots & Gallery

| Island Ecosystem View | Island Shape Generator |
|:---:|:---:|
| ![Island Simulation View](docs/screenshots/7.png) | ![Island Shape Generator](docs/screenshots/1.png) |

| Coastal Bays & Coves Generator | Live Population Statistics |
|:---:|:---:|
| ![Bays Generator](docs/screenshots/2.png) | ![Population Stats](docs/screenshots/7g.png) |

---

## 🇵🇱 Polska Dokumentacja

### 🌟 Opis Projektu
Projekt symulacji ekosystemu wyspy (drapieżnik–ofiara) zrealizowany w **styczniu 2005 roku** w ramach kursu **Projekt z Programowania Obiektowego** na **Wydziale Elektroniki Politechniki Wrocławskiej**.

Aplikacja modeluje interakcje w zamkniętym ekosystemie wyspy pomiędzy **roślinożercami (króliki)**, **drapieżnikami (lisy)** a **zasobami środowiskowymi (wegetacja trawy)** na dynamicznie generowanym, konfigurowalnym terenie.

### Główne Funkcjonalności
* **Generator wyspy:**
  * Rysowanie konturu wyspy oparte o 4 sinusojdy i szum losowy,
  * Generator nieregularnych zatok (od małych zatoczek po głębokie fiordy),
  * Wygładzanie brzegów oparte o automaty komórkowe z maską krzyżową (naprzemienne operacje dylatacji i erozji lądu i wody),
  * Strefy gradientowe: morze, plaża, trawa, śnieg, góry, wulkan.
* **Symulacja Życia i Ekologii:**
  * **Króliki (Ofiary):** spalanie dżuli przy ruchu, głód, poszukiwanie trawy, ucieczka przed lisem, dojrzałość, ciąża, śmierć głodowa/ze starości/ze zjedzenia.
  * **Lisy (Drapieżniki):** polowanie na króliki, pościg, zapotrzebowanie energetyczne, watahy i rozród.
  * **Wegetacja Trawy:** dynamiczny wzrost trawy, odnawianie się wyjedzonych kęp.
  * **Inżynieria Genetyczna:** panel edycji cech osobniczych i priorytetów zachowań ("Neo jako królik-komandos").
  * **Statystyki:** liczniki populacji i przyczyn zgonów na żywo.

---

## 📁 Struktura Repozytorium

```
Australia-1859-Sim/
├── modern/                # ✨ NOWOCZESNY PORT C++20 + RAYLIB (Visual Studio 2026 / CMake)
│   ├── CMakeLists.txt     # Automatyczne pobieranie Raylib i konfiguracja projektu
│   ├── src/               # Przeniesiony, w 100% wierny kod algorytmiczny
│   │   ├── main.cpp       # Nowoczesne okno 60 FPS, pętla gry i interfejs HUD
│   │   ├── Simulation.cpp # Generator wyspy, BFS fal, wegetacja, renderer RGBA
│   │   ├── Kroliki.cpp    # Klasa królików, stado, metabolizm, rozród, ucieczka
│   │   ├── Lisy.cpp       # Klasa lisów, polowanie, stado, zachowanie
│   │   └── *.h            # Klasy bazowe, kolejka FIFO BFS
│   ├── assets/            # Oryginalne ikony i sprite'y zwierząt
│   └── bin/               # Gotowy, skompilowany plik Australia1859Sim.exe (x64)
├── ver16/                 # Ostateczna archiwalna wersja projektu (Borland C++Builder 6)
│   ├── wyspa.bpr          # Plik projektu Borland C++Builder 6
│   ├── wyspa.cpp          # Punkt wejścia WinMain
│   ├── glowny.cpp / .h    # Główne okno aplikacji VCL
│   ├── glowny.dfm         # Definicja formularza VCL
│   ├── Kroliki.cpp / .h   # Oryginalne algorytmy królików
│   ├── Lisy.cpp / .h      # Oryginalne algorytmy lisów
│   └── wyspa.exe          # Oryginalny plik wykonywalny Win32 z 2005 roku
├── ver15/                 # Wersja pośrednia (etap rozwoju projektu)
├── ver14/                 # Wczesna wersja prototypowa
├── docs/                  # Dokumentacja i materiały archiwalne
│   ├── wyspa.doc          # Oryginalna dokumentacja projektowa PWr (2005)
│   └── screenshots/       # Zrzuty ekranu w formacie PNG
├── plany.txt              # Oryginalne notatki autora z prac nad projektem
├── .gitignore             # Wykluczenie plików tymczasowych Borland i CMake
└── README.md              # Niniejsza dokumentacja
```

---

## ⚡ Nowoczesny Port C++20 (Raylib + Autentyczny Interfejs Borland GUI)

Projekt posiada w pełni funkcjonalny, nowoczesny port w folderze `modern/`, który zachowuje **100% oryginalnych algorytmów z 2005 roku** oraz **przywraca wierny, klasyczny interfejs graficzny Borland C++Builder 6 (VCL)**:

### 🖥️ Wiernie Przywrócony Interfejs Borland C++Builder 6:
* **Etapowy Kreator Świata (Wizard Flow):**
  * **Etap 0: Generator „Bóg ver. 1.3.12”** – z 4 zakładkami:
    * `Kształt` – dobór amplitudy i generowanie wstępnego zarysu lądu,
    * `Zatoki` – rzeźbienie linii brzegowej (zatoki głębokie oraz zatoki na plaży),
    * `Korekta` – powiększanie (`+`), pomniejszanie (`-`) lądu oraz wygładzanie brzegów automatami komórkowymi,
    * `Wnętrze` – proporcje plaży, trawy, śniegu oraz dodawanie ziarnistości terenu.
  * **Etap 1: Generator „Króliczek ver. 1.3.1”** – konfiguracja liczebności, stad i rozproszenia populacji królików.
  * **Etap 2: Generator „Lisek ver. 1.3.1”** – konfiguracja liczebności, stad i rozproszenia populacji lisów.
  * **Etap 3: Informer „UB ver. 1.3.6”** – aktywna symulacja ekosystemu z 7 zakładkami:
    * `Trawka` – kontrola wegetacji, zazielenianie na maksa, koszenie i reset trawy,
    * `Króliki` – kontrola genetyki i metabolizmu (prędkość, metabolizm, kęs, żołądek, głód, starvation, detekcja lisów, długość życia, dojrzałość, ciąża),
    * `Lisy` – parametry drapieżników (prędkość, metabolizm, wartość odżywcza królika, żołądek, głód, długość życia, ciąża),
    * `Stat` – statystyki na żywo: liczebność, zgony z głodu, ze starości oraz króliki upolowane,
    * `Mój królik` / `Mój lis` – szczegółowy inspektor wybranego osobnika (status, płeć, wiek/max, najedzenie, ciąża, wielkość),
    * `Ewolucja` – średnie parametry populacji mierzone w czasie rzeczywistym.
* **Klasyczne kontrolki VCL:**
  * Zakładki (TPageControl),
  * Ramki 3D (TGroupBox, TBevel, Sunken/Raised boxes),
  * Pola numeryczne TUpDown ze strzałkami góra/dół (spinboxy),
  * Pola tekstowe TEdit o żółtym tle z purpurowym/czarnym fontem,
  * Przyciski nawigacyjne `<< Powrót` oraz `OK >>` (w etapie symulacji działający jako pauza/wznowienie).
* **🖥️ Opcja Pełnego Ekranu (Fullscreen):**
  * Przełączanie w dowolnym momencie dedykowanym przyciskiem **`[Pełny ekran (F11)]`** na dole panelu lub klawiszem **`F11`**,
  * Wirtualna rozdzielczość ze skalowaniem letterbox zachowującym idealne proporcje bez rozciągania obrazu,
  * Wygładzanie i precyzyjne mapowanie kursora myszy na wirtualne płótno w każdym trybie.

### 🎮 Uruchomienie portu (Gotowy plik `.exe`)
Skompilowany, w pełni niezależny 64-bitowy plik wykonywalny znajduje się w:  
👉 **`modern/bin/Australia1859Sim.exe`**  
Wystarczy go uruchomić – działa natywnie na współczesnym Windowsie bez instalowania żadnych bibliotek!

### ⌨️ Sterowanie i skróty klawiszowe w nowoczesnym porcie:
* **`[F11]`** / **Przycisk na dole panelu** – Przełączenie trybu pełnoekranowego (Fullscreen / Windowed)
* **`[SPACJA]`** – Przejście do następnego etapu w kreatorze lub Wstrzymanie / Wznowienie w symulacji
* **`[1] / [2] / [3] / [4]`** – Szybka zmiana tempa symulacji (1x, 2x, 5x, 10x)
* **`Kliknięcie myszką na mapie`** – Bezpośrednie zaznaczenie najbliższego królika lub lisa i przejście do jego karty w inspektorze (`Mój królik` / `Mój lis`).
* **`Klikanie zakładek i strzałek UpDown`** – Płynna zmiana parametrów na żywo.

### 🛠️ Kompilacja portu ze źródeł (Visual Studio 2026 / CMake):
```bash
cd modern
cmake -B build
cmake --build build --config Release
```
CMake automatycznie pobierze i skompiluje bibliotekę Raylib – nie trzeba nic instalować ręcznie!

---

## 🏛️ Wersja Klasyczna (Borland C++Builder 6 / 2005)

Oryginalna, archiwalna aplikacja znajduje się w folderze `ver16/wyspa.exe`:
* Jest to 32-bitowy plik wykonywalny Win32 ze statycznie zlinkowaną biblioteką VCL.
* Działa natywnie na współczesnych systemach Windows (Windows 10, Windows 11 64-bit) pod warstwą WOW64.
* Do rekompilacji źródeł z folderu `ver16/` wymagane jest środowisko **Borland C++Builder 6.0** (lub Embarcadero C++Builder z obsługą VCL).

---

## 👨‍💻 Autor / Author

* **Dawid Domagała** ([@DavIT-Futures](https://github.com/DavIT-Futures))
* Politechnika Wrocławska, Wydział Elektroniki (2005)
