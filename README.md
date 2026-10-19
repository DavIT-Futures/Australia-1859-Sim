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

## 🚀 Uruchomienie Programu / Running the Application

Skompilowana aplikacja znajduje się w folderze `ver16/wyspa.exe`.

* Jest to 32-bitowy plik wykonywalny Win32 ze **statycznie zlinkowaną biblioteką VCL (Visual Component Library)**.
* **Nie wymaga żadnych zewnętrznych bibliotek DLL ani instalatorów.**
* **Działa natywnie na współczesnych systemach Windows (Windows 10, Windows 11 64-bit)** pod warstwą WOW64.
* Wystarczy dwukrotnie kliknąć `ver16/wyspa.exe`, aby uruchomić symulator.

---

## 🛠️ Kompilacja ze Źródeł / Building from Source

Kod źródłowy został napisany z wykorzystaniem biblioteki **VCL** dedykowanej dla środowiska **Borland C++Builder 6.0**:

1. Otwórz projekt `ver16/wyspa.bpr` w środowisku **Borland C++Builder 6.0** (lub kompatybilnym Embarcadero RAD Studio / C++Builder z obsługą VCL).
2. Wybierz konfigurację `Release` lub `Debug`.
3. Uruchom kompilację skrótem `Project -> Make` (`Ctrl+F9`) lub `Project -> Build` (`Shift+F9`).

---

## 👨‍💻 Autor / Author

* **Dawid Domagała** ([@DavIT-Futures](https://github.com/DavIT-Futures))
* Politechnika Wrocławska, Wydział Elektroniki (2005)
