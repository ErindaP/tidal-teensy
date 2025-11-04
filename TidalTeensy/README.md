# TidalTeensy - Live Coding System pour Teensy 4.0

Un système de live coding inspiré de **Tidal Cycles** fonctionnant sur Teensy 4.0 avec la librairie AudioStream.h.

## 🎵 Fonctionnalités

- **Éditeur de code multi-lignes** avec parsing en temps réel
- **Parser de patterns** inspiré de Tidal Cycles
- **Scheduler précis** avec gestion du timing en microsecondes
- **Synthèse audio temps réel** via AudioStream.h (15+ instruments)
- **Interface web moderne** avec Web Serial API
- **Support de 8 canaux** simultanés (d1 à d8)
- **16 voix de polyphonie** pour notes musicales

## 🎹 Instruments Disponibles

### Percussions (7)
- **bd** (kick), **sd** (snare), **hh** (hihat), **cp** (clap)
- **tom**, **rim**, **cymbal**

### Instruments Mélodiques (8)
- **sine**, **saw**, **square**, **triangle**
- **bass**, **lead**, **pad**, **pluck**

### Notes Musicales
Format: `instrument:note` (ex: `sine:c4`, `bass:a2`)
- Notes: c, d, e, f, g, a, b
- Octaves: 0-8 (ex: c4, a3, e5)
- Altérations: # (dièse), b (bémol)

## 🖥️ Interface Web

**Nouvelle interface éditeur de code** avec :
- ✅ Éditeur multi-lignes avec numérotation
- ✅ Parsing en temps réel de chaque ligne
- ✅ Modification libre de n'importe quelle ligne
- ✅ Console séparée pour les messages
- ✅ Raccourcis clavier (Ctrl+Enter, Shift+Enter, Ctrl+.)
- ✅ Indicateurs visuels d'état (modifié, erreur, envoyé)

Voir **[EDITOR_INTERFACE.md](EDITOR_INTERFACE.md)** pour la documentation complète.

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
- 15+ instruments synthétisés (percussions + mélodiques)
- 16 voix de polyphonie
- Génération procédurale avec enveloppes ADSR
- Support des notes musicales (c0-b8)
- Conversion note → fréquence automatique

### 4. **SerialInterface** (`SerialInterface.h/cpp`)
Interface de communication:
- Commandes type Tidal Cycles
- Parsing des commandes en temps réel
- Retours visuels

### 5. **Interface Web** (`web_interface.html`)
Éditeur de code multi-lignes:
- Parsing en temps réel
- Numérotation des lignes
- Console séparée
- Raccourcis clavier
- Web Serial API pour communication USB

## 🚀 Utilisation

### Interface Web (Recommandé)

1. **Démarrer le serveur local** :
```bash
python serve_interface.py
```

2. **Ouvrir dans Chrome/Edge/Opera** :
```
http://localhost:8000/web_interface.html
```

3. **Se connecter au Teensy** (bouton en haut)

4. **Écrire du code** :
```
d1 bd sd hh cp
d2 bd*4
d3 sine:c4 sine:e4 sine:g4
bpm 140
```

5. **Évaluer** :
   - **Ctrl+Enter** : Tout le code
   - **Shift+Enter** : Ligne courante seulement
   - **Ctrl+.** : Stop tous les patterns

Voir **[EDITOR_INTERFACE.md](EDITOR_INTERFACE.md)** pour plus de détails.

### Commandes disponibles

#### Patterns percussion
```
d1 bd sd hh cp          # Pattern sur canal 1
d2 bd*4                 # bd joué 4 fois par cycle
d3 bd sd ~ hh           # avec silence (~)
```

#### Patterns mélodiques
```
d4 sine:c4 sine:e4 sine:g4      # Accord Do majeur
d5 bass:c2*4                     # Ligne de basse répétée
d6 lead:c4 ~ lead:e4 lead:g4    # Mélodie avec silences
d7 pad:c3 pad:e3                 # Pad ambiant
```

#### Commandes système
```
d1 silence              # Coupe le canal 1
bpm 140                 # Change le tempo
clear / hush            # Efface tous les patterns
help                    # Affiche l'aide
```

### Percussions disponibles (7)

- **bd** / **kick** - Kick drum
- **sd** / **snare** / **sn** - Snare
- **hh** / **hat** - Hi-hat
- **cp** / **clap** - Clap
- **tom** - Tom drum
- **rim** - Rimshot
- **cymbal** / **crash** / **ride** - Cymbales

### Instruments mélodiques (8)

- **sine** - Onde sinusoïdale pure
- **saw** - Onde en dents de scie (brillant)
- **square** - Onde carrée (8-bit)
- **triangle** - Onde triangulaire (flûte)
- **bass** - Basse synthétique avec harmoniques
- **lead** - Synthé lead avec vibrato
- **pad** - Son ambiant atmosphérique
- **pluck** - Son pincé (guitare/harpe)

Voir **[INSTRUMENTS.md](INSTRUMENTS.md)** pour exemples détaillés.

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

