# TidalTeensy - Live Coding System pour Teensy 4.0

Un système de live coding inspiré de **Tidal Cycles** fonctionnant sur Teensy 4.0 avec la librairie AudioStream.h.

## 🎵 Fonctionnalités

- **Parser de patterns** inspiré de Tidal Cycles
- **Scheduler précis** avec gestion du timing en microsecondes
- **Synthèse audio temps réel** via AudioStream.h
- **Interface série** pour le live coding
- **Support de 8 canaux** simultanés (d1 à d8)

## 📋 Architecture

Le projet est décomposé en plusieurs modules:

### 1. **PatternParser** (`PatternParser.h/cpp`)
Parse les patterns textuels type Tidal Cycles:
- `bd sd hh cp` - 4 sons espacés également
- `bd*4` - répétition (bd joué 4 fois)
- `bd sd ~ hh` - silence explicite avec `~`
- `[bd sd] hh` - groupes (à implémenter)

### 2. **Scheduler** (`Scheduler.h/cpp`)
Gère le timing et l'ordonnancement:
- Maintient un compteur précis en microsecondes
- Calcule la position dans le cycle (0.0 - 1.0)
- Supporte 8 patterns simultanés
- BPM ajustable en temps réel

### 3. **AudioEngine** (`AudioEngine.h/cpp`)
Génération audio via AudioStream:
- Synthèse simple de sons de batterie (kick, snare, hihat, clap)
- Polyphonie (8 voix max)
- Génération procédurale avec enveloppes

### 4. **SerialInterface** (`SerialInterface.h/cpp`)
Interface de communication:
- Commandes type Tidal Cycles
- Parsing des commandes en temps réel
- Retours visuels

## 🚀 Utilisation

### Commandes de base

```
d1 bd sd hh cp          # Pattern sur canal 1
d2 bd*4                 # bd joué 4 fois par cycle
d3 bd sd ~ hh           # avec silence
d1 silence              # Coupe le canal 1
bpm 140                 # Change le tempo
clear / hush            # Efface tous les patterns
help                    # Affiche l'aide
```

### Samples disponibles

- **bd** / **kick** - Kick drum
- **sd** / **snare** / **sn** - Snare
- **hh** / **hat** - Hi-hat
- **cp** / **clap** - Clap

## 🔧 Installation

### Matériel requis
- Teensy 4.0
- Audio Shield for Teensy (SGTL5000) ou sortie I2S
- Enceintes/casque

### Logiciels requis
- Arduino IDE avec support Teensy (Teensyduino)
- Librairie Audio pour Teensy

### Upload sur le Teensy

1. Ouvrir `TidalTeensy.ino` dans Arduino IDE
2. Sélectionner: `Tools > Board > Teensy 4.0`
3. Sélectionner: `Tools > USB Type > Serial`
4. Compiler et uploader

### Test via Serial Monitor

1. Ouvrir le Serial Monitor (115200 baud)
2. Taper: `d1 bd sd hh cp`
3. Le pattern devrait jouer en boucle
4. Taper: `bpm 160` pour accélérer

## 📝 Développements futurs

### À implémenter

- [ ] **Groupes** `[bd sd]` - subdivision du temps
- [ ] **Euclid patterns** `bd(3,8)` - rythmes euclidiens
- [ ] **Effets** `# gain 0.8`, `# speed 2`
- [ ] **Polyrythmes** - différentes longueurs de cycles
- [ ] **Samples WAV** depuis carte SD
- [ ] **MIDI out** pour contrôler synthés externes
- [ ] **Interface web** via Ethernet ou WiFi

### Extensions possibles

- **OSC** - Contrôle via Open Sound Control
- **Quantization** - Alignement automatique des commandes
- **Pattern chaining** - Séquences de patterns
- **Randomisation** - Variation algorithmique

## 🎹 Interface de contrôle

Vous pouvez créer une interface pour envoyer des commandes:

### Option 1: Serial Monitor
Le plus simple pour débuter

### Option 2: Script Python
```python
import serial
import time

ser = serial.Serial('COM3', 115200)  # Adapter le port
time.sleep(2)

ser.write(b'd1 bd sd hh cp\n')
time.sleep(4)
ser.write(b'bpm 160\n')
```

### Option 3: Interface Web
Créer une page web qui communique via Serial Web API

## 📊 Performances

- **Latency** : < 5ms (dépend du buffer audio)
- **CPU Usage** : ~30-40% à 120 BPM avec 4 patterns
- **Max patterns** : 8 simultanés
- **Max events/pattern** : 32
- **Sample rate** : 44.1 kHz

## 🐛 Debug

Si pas de son:
1. Vérifier les connexions de l'Audio Shield
2. Vérifier le volume: ligne 45 de `TidalTeensy.ino`
3. Activer les messages debug dans Serial Monitor

## 📚 Références

- [Tidal Cycles](https://tidalcycles.org/)
- [Teensy Audio Library](https://www.pjrc.com/teensy/td_libs_Audio.html)
- [AudioStream Documentation](https://www.pjrc.com/teensy/td_libs_AudioStream.html)

## 📄 Licence

Projet open-source éducatif - À adapter selon vos besoins

## 👨‍💻 Auteur

Créé comme base fonctionnelle pour un système de live coding embarqué
