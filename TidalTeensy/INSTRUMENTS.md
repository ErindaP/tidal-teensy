# 🎹 Guide des Instruments et Notes - TidalTeensy

## 🥁 Percussions (samples existants)

### Sons de batterie classiques
```
bd / kick          # Kick drum (grosse caisse)
sd / snare / sn    # Snare drum (caisse claire)
hh / hat           # Hi-hat (charleston)
cp / clap          # Handclap
```

### Nouvelles percussions ajoutées
```
tom / lt / mt      # Tom (différentes hauteurs)
rim / rs           # Rimshot (coup sur le bord)
cymbal / crash / ride  # Cymbales
```

### Exemples de patterns percussion
```
d1 bd sd hh cp
d2 tom rim cymbal
d3 bd*4 sd hh*8
```

---

## 🎵 Instruments Mélodiques

### Syntaxe pour jouer des notes
```
instrument:note

Exemples:
sine:c4        # Sine wave jouant un Do central
bass:a2        # Basse jouant un La grave
lead:e4        # Lead jouant un Mi
```

### Liste des instruments disponibles

#### **1. SINE / SIN** 🌊
Son doux, pur, sans harmoniques
```
d1 sine:c4 sine:e4 sine:g4    # Accord Do majeur
d2 sine:a3 ~ sine:c4 ~
```
**Caractéristiques:** Attack doux, sustain long, parfait pour les pads

#### **2. SAW / SAWTOOTH** ⚡
Son brillant, riche en harmoniques
```
d1 saw:c4 saw:d4 saw:e4 saw:f4
d2 saw:a2*4                    # Ligne de basse
```
**Caractéristiques:** Attack rapide, son brillant, idéal pour les leads

#### **3. SQUARE / PULSE** 🔲
Son 8-bit, style rétro
```
d1 square:c5 square:e5 square:g5
d2 square:c4 ~ ~ square:c5     # Arpège
```
**Caractéristiques:** Son creux, parfait pour les mélodies chip-tune

#### **4. TRIANGLE / TRI** 🔺
Son doux, type flûte
```
d1 triangle:c4 triangle:d4 triangle:e4
d2 tri:g4 tri:a4 tri:b4
```
**Caractéristiques:** Doux mais avec un peu de corps, style flûte douce

#### **5. BASS** 🎸
Basse synthétique puissante
```
d1 bass:c2 bass:c2 bass:g2 bass:f2
d2 bass:a1*4
d3 bass:c2 ~ bass:c3 ~
```
**Caractéristiques:** Attack très court, envelope punchy, harmoniques riches

#### **6. LEAD** 🎤
Synthé lead avec vibrato
```
d1 lead:c4 lead:e4 lead:g4 lead:c5
d2 lead:a4*2 lead:b4*2
```
**Caractéristiques:** Vibrato subtil, sustain long, parfait pour les solos

#### **7. PAD** 🌌
Son atmosphérique, ambiant
```
d1 pad:c3 pad:e3 pad:g3        # Accord tenu
d2 pad:a2 ~ ~ ~                # Note longue
```
**Caractéristiques:** Attack très lent (300ms), mix d'harmoniques, ambiant

#### **8. PLUCK / HARP** 🪕
Son pincé, type guitare/harpe
```
d1 pluck:c4 pluck:e4 pluck:g4 pluck:c5
d2 pluck:c3*8                  # Arpège rapide
```
**Caractéristiques:** Attack instantané, decay rapide, son percussif mélodique

---

## 🎼 Notation des Notes

### Format de base
```
note = [lettre][modificateur][octave]

Exemples:
c4     # Do central (middle C)
d#3    # Ré dièse, octave 3
gb5    # Sol bémol, octave 5
a4     # La 440Hz (note de référence)
```

### Lettres des notes (système anglo-saxon)
```
c  → Do
d  → Ré
e  → Mi
f  → Fa
g  → Sol
a  → La
b  → Si
```

### Modificateurs
```
#      # Dièse (augmente d'un demi-ton)
b      # Bémol (diminue d'un demi-ton)

Exemples:
c#4    # Do dièse
db4    # Ré bémol (même note que c#4)
f#3    # Fa dièse
```

### Octaves
```
0-1    # Très grave
2-3    # Grave (basse)
4      # Medium (voix, mélodies)
5-6    # Aigu
7-8    # Très aigu
```

### Exemples de notes par octave
```
Octave 2 (grave):    c2 d2 e2 f2 g2 a2 b2
Octave 3 (basse):    c3 d3 e3 f3 g3 a3 b3
Octave 4 (central):  c4 d4 e4 f4 g4 a4 b4
Octave 5 (aigu):     c5 d5 e5 f5 g5 a5 b5
```

---

## 🎶 Exemples de Patterns Musicaux

### Mélodie simple
```
d1 sine:c4 sine:d4 sine:e4 sine:f4
d2 sine:g4 sine:a4 sine:b4 sine:c5
```

### Ligne de basse + mélodie
```
d1 bass:c2 bass:c2 bass:g2 bass:f2
d2 lead:c4 ~ lead:e4 lead:g4
```

### Accord tenu + arpège
```
d1 pad:c3 pad:e3 pad:g3
d2 pluck:c4 pluck:e4 pluck:g4 pluck:c5
```

### Techno / EDM
```
d1 bd*4                        # Kick 4/4
d2 bass:c2*8                   # Bassline rapide
d3 lead:c4 ~ lead:c5 ~         # Lead stab
d4 hh*8                        # Hi-hat constant
```

### Ambiant / Atmosphérique
```
d1 pad:c3 ~ ~ ~
d2 pad:e3 ~ ~ ~
d3 pluck:c5 ~ pluck:g4 ~
d4 ~ ~ cymbal ~
```

### Arpège rapide
```
d1 pluck:c4*8
d2 pluck:e4*8
d3 pluck:g4*8
d4 bd ~ sd ~
```

### Mélodie 8-bit (rétro)
```
d1 square:c5 square:e5 square:g5 square:c6
d2 square:c4*4
d3 bd sd hh cp
```

---

## 🎹 Gammes Courantes

### Gamme de Do Majeur
```
c4 d4 e4 f4 g4 a4 b4 c5
```

### Gamme de La Mineur Naturelle
```
a3 b3 c4 d4 e4 f4 g4 a4
```

### Pentatonique de Do
```
c4 d4 e4 g4 a4 c5
```

### Accord de Do Majeur
```
d1 sine:c4 sine:e4 sine:g4
```

### Accord de La Mineur
```
d1 pad:a3 pad:c4 pad:e4
```

---

## 💡 Astuces et Techniques

### Répétition de notes
```
d1 bass:c2*4              # La note c2 jouée 4 fois par cycle
d2 lead:e4*8              # La note e4 jouée 8 fois par cycle
```

### Silences
```
d1 sine:c4 ~ sine:e4 ~   # Alternance note/silence
d2 bass:a2 ~ ~ ~          # Note puis 3 silences
```

### Mix percussion + mélodie
```
d1 bd sd hh cp            # Rythme
d2 bass:c2 ~ bass:g2 ~    # Basse
d3 lead:c4 lead:e4 lead:g4  # Mélodie
```

### Polyphonie (plusieurs notes simultanées)
```
d1 sine:c4
d2 sine:e4               # Ces 3 canaux jouent
d3 sine:g4               # simultanément = accord
```

### Octaves différentes
```
d1 bass:c2               # Basse (grave)
d2 pluck:c4              # Mélodie (medium)
d3 lead:c5               # Lead (aigu)
```

---

## 🔧 Limitations Actuelles

- **Polyphonie:** Max 16 voix simultanées (partagées entre tous les canaux)
- **Durée des notes:** Fixe à 0.5s par défaut
- **Pas d'effets:** Pas encore de reverb, delay, filtres dynamiques
- **Vélocité limitée:** Le paramètre velocity affecte seulement le volume

---

## 🚀 Prochaines Améliorations Possibles

1. **Durée de note variable:** `sine:c4:1.0` (1 seconde)
2. **Vélocité par note:** `sine:c4@0.5` (volume 50%)
3. **Effets:** `sine:c4 # reverb 0.5 # lpf 800`
4. **Accords raccourcis:** `sine:'c4 e4 g4'`
5. **Gammes automatiques:** `scale "major" "c4"`

---

## 📝 Exemples Complets de Sessions

### Session 1: Techno Minimaliste
```
d1 bd*4
d2 bass:c2*8
d3 hh*8
d4 lead:c4 ~ lead:c5 ~
bpm 128
```

### Session 2: Ambient Calme
```
d1 pad:c3 ~ ~ ~
d2 pad:e3 ~ ~ ~
d3 pluck:c5 ~ ~ pluck:g4
d4 ~ ~ cymbal ~
bpm 80
```

### Session 3: Mélodie 8-bit
```
d1 square:c5 square:d5 square:e5 square:f5
d2 square:c4*4
d3 bd ~ sd ~
d4 hh*8
bpm 140
```

### Session 4: Basse Funk
```
d1 bd ~ bd sd
d2 bass:c2 bass:c2 bass:g2 bass:c3
d3 hh hh hh hh
d4 cp ~ ~ ~
bpm 110
```

Amusez-vous bien avec TidalTeensy! 🎵
