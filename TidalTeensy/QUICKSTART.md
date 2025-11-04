# 🚀 Quick Start Guide - TidalTeensy Code Editor

## 📦 Ce dont vous avez besoin

- ✅ Teensy 4.0 avec le code TidalTeensy uploadé
- ✅ Chrome, Edge ou Opera (Web Serial API)
- ✅ Python 3.x installé

## 🎯 Démarrage en 5 étapes

### 1️⃣ Connecter le Teensy

Branchez votre Teensy 4.0 en USB à l'ordinateur.

### 2️⃣ Démarrer le serveur web

Ouvrez un terminal dans le dossier TidalTeensy :

```bash
cd d:\ENS\M2\EAS\Tidal_Teensy\TidalTeensyTest\tidal-teensy\TidalTeensy
python serve_interface.py
```

Vous devriez voir :
```
🎹 TidalTeensy Interface Server
📂 Serving directory: ...
🌐 Open in browser: http://localhost:8000/web_interface.html
⚠️  Use Chrome, Edge or Opera (Web Serial API required)
🛑 Press Ctrl+C to stop
```

### 3️⃣ Ouvrir l'interface

Ouvrez Chrome, Edge ou Opera et allez sur :
```
http://localhost:8000/web_interface.html
```

### 4️⃣ Se connecter au Teensy

1. Cliquez sur **"🔌 Se connecter au Teensy"**
2. Dans la fenêtre qui s'ouvre, sélectionnez le port USB du Teensy
3. Cliquez sur "Connecter"

La console devrait afficher :
```
✓ Web Serial API disponible
Sélection du port série...
Ouverture du port...
✓ Connecté au Teensy!
```

### 5️⃣ Coder et jouer !

Écrivez du code dans l'éditeur de gauche :

```
d1 bd sd hh cp
d2 bd*4
d3 hh*8

bpm 140
```

Puis appuyez sur **Ctrl+Enter** pour évaluer tout le code !

---

## ⌨️ Raccourcis Essentiels

| Touche | Action |
|--------|--------|
| **Ctrl+Enter** | Évaluer tout le code |
| **Shift+Enter** | Évaluer seulement la ligne courante |
| **Ctrl+.** | Arrêter tous les patterns |
| **Ctrl+L** | Effacer la console |

---

## 🎵 Premiers Patterns

### Pattern de base
```
d1 bd sd hh cp
```
Appuyez **Shift+Enter** sur cette ligne.

### Ajouter une basse
```
d2 bd*4
```
Appuyez **Shift+Enter** sur cette ligne.

### Ajouter des notes
```
d3 sine:c4 sine:e4 sine:g4
```
Appuyez **Shift+Enter** sur cette ligne.

### Changer le tempo
```
bpm 140
```
Appuyez **Shift+Enter** sur cette ligne.

---

## 🔧 Workflow Live Coding

### Méthode 1 : Tout évaluer

1. Écrivez plusieurs lignes
2. **Ctrl+Enter** → tout démarre en même temps

```
d1 bd sd hh cp
d2 bd*4
d3 sine:c4 sine:e4 sine:g4
bpm 130
```

### Méthode 2 : Ligne par ligne (live coding pur)

1. Écrivez `d1 bd sd hh cp`
2. **Shift+Enter** → d1 démarre
3. Écrivez `d2 bd*4`
4. **Shift+Enter** → d2 s'ajoute
5. Modifiez la ligne 1 : `d1 bd*8`
6. Remettez le curseur sur ligne 1
7. **Shift+Enter** → d1 se met à jour !

### Arrêter tout

**Ctrl+.** ou tapez `clear` puis **Shift+Enter**

---

## 🎹 Exemples Rapides

### Techno
```
bpm 128
d1 bd*4
d2 sd ~ sd ~
d3 hh*8
```

### Ambient
```
bpm 80
d1 pad:c3 ~ ~ ~
d2 pluck:c5 ~ pluck:g4 ~
```

### 8-bit
```
bpm 140
d1 bd ~ bd ~
d2 square:c5 square:d5 square:e5 square:f5
d3 hh*16
```

---

## 📚 Fichiers Utiles

- **examples.tidal** : Plein d'exemples à copier/coller
- **EDITOR_INTERFACE.md** : Documentation complète de l'interface
- **INSTRUMENTS.md** : Guide des instruments et notes
- **README.md** : Vue d'ensemble du projet

---

## 🐛 Problèmes Courants

### "Web Serial API non supportée"
❌ Vous utilisez Firefox ou Safari
✅ Utilisez Chrome, Edge ou Opera

### "Aucun port sélectionné"
❌ Vous avez annulé la sélection du port
✅ Cliquez à nouveau sur "Se connecter" et sélectionnez le Teensy

### "Le port est déjà ouvert"
❌ Le port série est utilisé par un autre programme
✅ Fermez Arduino IDE ou Serial Monitor puis reconnectez

### Pas de son
❌ Vérifiez que le Teensy est bien branché à des enceintes/casque
❌ Vérifiez le volume du système
✅ Testez avec `d1 bd*4` puis **Shift+Enter**

### Le code ne s'envoie pas
❌ Vérifiez que vous êtes connecté (point vert en haut)
❌ Vérifiez la console pour les erreurs
✅ Reconnectez-vous au Teensy

---

## 💡 Conseils

1. **Commencez simple** : un seul pattern d1 d'abord
2. **Ajoutez progressivement** : d2, d3, etc.
3. **Expérimentez** : modifiez et ré-évaluez en live !
4. **Utilisez les commentaires** : `-- mon pattern drums`
5. **Sauvegardez** : copiez votre code dans un fichier .txt

---

## 🎉 Vous êtes prêt !

Maintenant, à vous de jouer ! N'hésitez pas à :
- Consulter **examples.tidal** pour l'inspiration
- Lire **INSTRUMENTS.md** pour découvrir tous les sons
- Expérimenter avec différents BPMs
- Combiner percussions et mélodies

**Happy live coding! 🎵🎹**
