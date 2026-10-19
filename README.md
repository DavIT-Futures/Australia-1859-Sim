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

## ⚡ Nowoczesny Port C++20 (Raylib)

Projekt posiada w pełni funkcjonalny, nowoczesny port w folderze `modern/`, który zachowuje **100% oryginalnych algorytmów z 2005 roku**:

### 🎮 Uruchomienie portu (Gotowy plik `.exe`)
Skompilowany, w pełni niezależny 64-bitowy plik wykonywalny znajduje się w:  
👉 **`modern/bin/Australia1859Sim.exe`**  
Wystarczy go uruchomić – działa natywnie na współczesnym Windowsie bez instalowania żadnych bibliotek!

### ⌨️ Sterowanie i skróty klawiszowe w nowoczesnym porcie:
* **`[SPACJA]`** – Wstrzymanie / wznowienie symulacji (Pause / Resume)
* **`[1] / [2] / [3] / [4]`** – Zmiana prędkości symulacji (1x, 2x, 5x, 10x) lub klawisze `+` / `-`
* **`[G]`** – Wygenerowanie nowej wyspy (algorytm sinusoidalny)
* **`[B]`** – Wycięcie nieregularnych zatok brzegowych (algorytm rombowy)
* **`[S]`** – Wygładzenie linii brzegowej (automaty komórkowe / erozja i dylatacja)
* **`[Z]`** – Dodanie ziarna i szumu terenu
* **`[K]`** – Wpuszczenie stada 50 królików
* **`[L]`** – Wpuszczenie stada 10 lisów
* **`[R]`** – Reset trawy do stanu początkowego
* **`[M]`** – Maksymalny rozrost trawy na całej wyspie
* **`[C]`** – Usunięcie wszystkich zwierząt z wyspy
* **`Kliknięcie myszką na zwierzęciu`** – Wybór i podgląd parametrów życiowych osobnika w panelu inspektora (wiek, energia, płeć, ciąża, status zachowania).

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
