# Installation et Guide de Démarrage

## 📋 Prérequis

### Matériel
- **Teensy 4.0**
- **Audio Shield for Teensy 4.x** (avec SGTL5000) OU sortie I2S
- Enceintes ou casque
- Câble USB

### Logiciels
1. **Arduino IDE** (version 1.8.x ou 2.x)
2. **Teensyduino** (extension Teensy pour Arduino)
   - Télécharger depuis: https://www.pjrc.com/teensy/td_download.html
3. **Librairie Audio** (incluse avec Teensyduino)

## 🚀 Installation

### Étape 1: Configuration de l'Arduino IDE

1. Installer Arduino IDE
2. Installer Teensyduino
3. Redémarrer Arduino IDE
4. Vérifier que "Teensy 4.0" apparaît dans `Tools > Board`

### Étape 2: Connexion du Teensy

#### Option A: Avec Audio Shield (recommandé)
```
Teensy 4.0 + Audio Shield
├── Connecter l'Audio Shield sur le Teensy
├── Brancher les enceintes/casque sur la sortie jack
└── Connecter le Teensy en USB à l'ordinateur
```

#### Option B: Sans Audio Shield (DAC I2S externe)
Si vous utilisez un DAC I2S externe, modifier les connexions:
```cpp
// Dans TidalTeensy.ino, commenter:
// AudioControlSGTL5000 audioShield;

// Et les lignes:
// audioShield.enable();
// audioShield.volume(0.5);
```

### Étape 3: Upload du code

1. Ouvrir `TidalTeensy.ino`
2. Sélectionner:
   - `Tools > Board > Teensy 4.0`
   - `Tools > USB Type > Serial`
   - `Tools > CPU Speed > 600 MHz`
   - `Tools > Port > [Votre port Teensy]`
3. Cliquer sur **Upload** (ou Ctrl+U)
4. Le Teensy devrait redémarrer automatiquement

### Étape 4: Test initial

1. Ouvrir le **Serial Monitor** (`Tools > Serial Monitor`)
2. Régler le baud rate à **115200**
3. Vous devriez voir:
```
=== TidalTeensy v0.1 ===
Live Coding System pour Teensy 4.0

[Parser] Initialisé
[Scheduler] Initialisé à 120.00 BPM
[SerialInterface] Prêt

=== Commandes TidalTeensy ===
...
```

4. Taper dans le Serial Monitor:
```
d1 bd sd hh cp
```

5. Vous devriez entendre un pattern de batterie! 🎵

## 🎹 Utilisation via Python

### Installation de l'interface Python

1. Installer Python 3.7+ si nécessaire
2. Installer pySerial:
```bash
pip install pyserial
```

3. Lancer l'interface interactive:
```bash
python tidal_interface.py
```

4. Ou le mode démo:
```bash
python tidal_interface.py demo
```

### Exemple de script Python

```python
from tidal_interface import TidalTeensyInterface
import time

teensy = TidalTeensyInterface('COM3')  # Adapter le port

teensy.pattern(1, "bd sd hh cp")
time.sleep(4)

teensy.bpm(160)
teensy.pattern(2, "bd*4")
time.sleep(8)

teensy.clear()
teensy.close()
```

## 🌐 Interface Web

### Lancement de l'interface web

1. Ouvrir `web_interface.html` dans **Chrome**, **Edge** ou **Opera**
   (Web Serial API requise)

2. Cliquer sur **"Connecter"**

3. Sélectionner le port du Teensy

4. Utiliser l'interface graphique pour:
   - Entrer des patterns sur d1-d4
   - Changer le BPM
   - Essayer les exemples prédéfinis

## 🔧 Dépannage

### Pas de son

**Vérifier:**
1. Volume de l'Audio Shield (ligne 45 dans TidalTeensy.ino)
   ```cpp
   audioShield.volume(0.5); // Essayer 0.8
   ```

2. Connexions physiques:
   - Audio Shield bien enfoncé sur le Teensy
   - Enceintes branchées et allumées
   - Jack bien inséré

3. Test hardware:
   - Charger un exemple de la librairie Audio: `File > Examples > Audio > HardwareTesting > PassThroughStereo`
   - Si ça fonctionne, le hardware est OK

### Erreurs de compilation

**"Audio.h not found"**
- Réinstaller Teensyduino
- Vérifier que le board "Teensy 4.0" est bien sélectionné

**"AudioStream has no member..."**
- Version de Teensyduino trop ancienne
- Mettre à jour vers la dernière version

### Port série introuvable

**Windows:**
```
- Vérifier dans Gestionnaire de périphériques > Ports COM
- Le Teensy apparaît généralement comme "USB Serial Device"
- Noter le numéro (COM3, COM4, etc.)
```

**Linux:**
```bash
ls /dev/ttyACM*
# Ou
ls /dev/ttyUSB*

# Donner les permissions:
sudo usermod -a -G dialout $USER
# Puis se reconnecter
```

**Mac:**
```bash
ls /dev/tty.usb*
```

### Latence audio

Si vous remarquez de la latence:

1. Réduire `AudioMemory()`:
   ```cpp
   AudioMemory(12); // Au lieu de 20
   ```

2. Augmenter la fréquence CPU:
   `Tools > CPU Speed > 600 MHz`

### Parser ne reconnaît pas les commandes

Vérifier:
1. Terminaison de ligne: `\n` ou `\r\n`
2. Format des commandes:
   ```
   d1 bd sd hh cp   ✓ Correct
   d1 "bd sd hh cp" ✓ Correct (avec guillemets)
   d1bd sd hh cp    ✗ Manque un espace
   ```

## 📊 Optimisation des performances

### Réduire l'utilisation CPU

1. Augmenter le délai dans `loop()`:
   ```cpp
   delayMicroseconds(500); // Au lieu de 100
   ```

2. Réduire le nombre de voix actives:
   ```cpp
   #define MAX_VOICES 4 // Au lieu de 8
   ```

### Améliorer la précision temporelle

1. Utiliser IntervalTimer pour le scheduler (avancé)
2. Réduire les Serial.print() dans le code de production

## 🎓 Tutoriels

### Créer un premier pattern

```
1. Connecter le Teensy
2. Ouvrir Serial Monitor
3. Taper: d1 bd sd hh cp
4. Appuyer sur Enter
5. Le pattern joue en boucle!
```

### Superposer plusieurs patterns

```
d1 bd sd hh cp    # Pattern de base
d2 bd*4           # Kick rapide
d3 hh*8           # Hi-hat rapide
```

### Changer le tempo en live

```
bpm 140           # Accélérer
bpm 90            # Ralentir
```

### Créer des rythmes complexes

```
d1 bd ~ sd ~      # Kick-Snare basique
d2 hh hh hh hh    # Hi-hat constant
d3 ~ ~ cp ~       # Clap sur le temps 3
```

## 📚 Ressources

- [Documentation Teensy Audio](https://www.pjrc.com/teensy/td_libs_Audio.html)
- [Tidal Cycles](https://tidalcycles.org/) (inspiration)
- [Forum PJRC](https://forum.pjrc.com/) (support Teensy)

## 🤝 Support

En cas de problème:
1. Vérifier ce guide
2. Activer les messages debug (dans Serial Monitor)
3. Vérifier les exemples de la librairie Audio
4. Consulter le README.md pour les détails techniques
