# 📝 Nouvelle Interface : Éditeur de Code Multi-Lignes

## 🎯 Changements majeurs

L'interface web a été **complètement redessinée** pour passer d'un terminal ligne par ligne à un **éditeur de code complet** avec parsing en temps réel.

### Avant vs Après

#### ❌ Ancien système (Terminal)
- Une seule ligne de saisie
- Commandes envoyées une par une
- Pas d'édition du code précédent
- Historique limité avec flèches

#### ✅ Nouveau système (Éditeur)
- **Éditeur multi-lignes** avec numérotation
- **Parsing en temps réel** de chaque ligne
- **Modification libre** de n'importe quelle ligne
- **Évaluation sélective** (une ligne ou tout)
- **Console séparée** pour les retours
- **Suivi de l'état** de chaque ligne

---

## 🖥️ Interface

### Layout en 2 panneaux

```
┌─────────────────────────────────────────────────────┐
│ 🎹 TidalTeensy Code Editor           [Déconnecter] │
├───────────────────────────┬─────────────────────────┤
│ 📝 Code Editor            │ 📟 Console              │
│ [▶ Eval All] [▶ Eval Line│ [Clear]                 │
│ [■ Stop]                  │                         │
├─────┬─────────────────────┤                         │
│  1  │ d1 bd sd hh cp      │ ✓ Web Serial API OK     │
│  2  │ d2 bd*4             │ Cliquez pour connecter  │
│  3  │ d3 hh*8             │                         │
│  4  │                     │                         │
│  5  │ bpm 140             │                         │
│     │                     │                         │
├─────┴─────────────────────┤                         │
│ Quick: [d1 drums] [bass]  │                         │
└───────────────────────────┴─────────────────────────┘
```

### Panneau Gauche : Code Editor
- **Numérotation des lignes** : automatique et synchronisée
- **Surbrillance ligne courante** : fond vert
- **Indicateurs d'état** :
  - ⚫ Normal (gris)
  - 🟢 Ligne courante (vert)
  - 🟠 Modifié (orange)
  - 🔴 Erreur (rouge)

### Panneau Droit : Console
- **Affichage des messages** :
  - 🟢 Messages Teensy (vert)
  - 🔵 Commandes envoyées (cyan)
  - 🟠 Infos système (orange)
  - 🔴 Erreurs (rouge)
- **Auto-scroll** : derniers messages toujours visibles
- **Clear button** : nettoyer l'historique

---

## ⌨️ Raccourcis Clavier

| Raccourci | Action | Description |
|-----------|--------|-------------|
| **Ctrl+Enter** | Evaluate All | Envoie tout le code au Teensy |
| **Shift+Enter** | Eval Line | Envoie uniquement la ligne courante |
| **Ctrl+.** | Stop All | Envoie `clear` (arrête tous les patterns) |
| **Ctrl+L** | Clear Console | Efface la console (pas le code) |

---

## 🎵 Utilisation

### 1. Écrire du code

```
d1 bd sd hh cp
d2 bd*4
d3 hh*8
d4 sine:c4 sine:e4 sine:g4

bpm 140
```

### 2. Options d'évaluation

#### Option A : Tout évaluer (**Ctrl+Enter**)
- Envoie toutes les lignes non vides/non-commentées
- Affiche chaque commande dans la console
- Marque les lignes comme "envoyées"
- Idéal pour démarrer une session

#### Option B : Ligne par ligne (**Shift+Enter**)
- Envoie uniquement la ligne sous le curseur
- Permet de tester/modifier ligne par ligne
- Workflow plus proche de Tidal Cycles
- Parfait pour le live coding

#### Option C : Bouton "Stop All" (**Ctrl+.**)
- Envoie la commande `clear`
- Arrête tous les patterns immédiatement
- Bouton rouge "■ Stop All" dans l'interface

### 3. Modifier et ré-évaluer

```
d1 bd sd hh cp        ← Évalué (ligne grise)
d2 bd*4               ← Modifier en bd*8
d3 hh*8               ← OK
```

Après modification de la ligne 2 :
- Ligne 2 devient **orange** (modifiée)
- Appuyer **Shift+Enter** sur ligne 2 uniquement
- Ligne redevient **grise** (évaluée)

---

## 🔍 Parsing en Temps Réel

### Validation syntaxique

Chaque ligne est analysée automatiquement :

#### ✅ Syntaxe valide
```
d1 bd sd hh cp              → Pattern (d1-d8)
bpm 140                     → Commande
-- Commentaire              → Commentaire (ignoré)
                            → Ligne vide (ignorée)
```

#### ❌ Syntaxe invalide
```
d9 bd sd                    → Erreur : d9 n'existe pas
bd sd hh                    → Erreur : manque d1-d8
xyz 123                     → Erreur : commande inconnue
```

### Indicateurs visuels

- **Numéro de ligne vert** : ligne courante
- **Numéro de ligne orange** : ligne modifiée (pas encore envoyée)
- **Numéro de ligne rouge** : erreur de syntaxe
- **Numéro de ligne gris** : ligne normale/envoyée

---

## 🆕 Nouvelles Fonctionnalités

### 1. État de chaque ligne

Chaque ligne a un état :
```javascript
{
  content: "d1 bd sd hh cp",
  sent: true,          // Déjà envoyée au Teensy
  modified: false,     // Pas modifiée depuis l'envoi
  error: false,        // Pas d'erreur de syntaxe
  type: "pattern"      // Type: pattern, command, comment
}
```

### 2. Boutons Quick Commands

Insèrent du code à la position du curseur :
- **d1 drums** : `d1 bd sd hh cp`
- **d2 bass** : `d2 bass:c2*4`
- **d3 chord** : `d3 sine:c4 sine:e4 sine:g4`
- **bpm 140** : `bpm 140`
- **clear all** : Envoie `clear` immédiatement

### 3. Commentaires

```
-- Ceci est un commentaire
-- Les commentaires sont ignorés lors de l'évaluation
d1 bd sd hh cp   -- Commentaire en fin de ligne (pas supporté)
```

**Note** : Seuls les commentaires en début de ligne (`--`) sont supportés pour l'instant.

### 4. Synchronisation scroll

Les numéros de ligne scrollent automatiquement avec l'éditeur.

---

## 💡 Workflow Live Coding

### Session typique

```
1. Se connecter au Teensy (bouton)
2. Écrire plusieurs patterns
3. Ctrl+Enter → tout démarre
4. Modifier une ligne (ex: d2)
5. Shift+Enter → juste d2 se met à jour
6. Continuer à modifier/évaluer en live
7. Ctrl+. → stop si besoin
```

### Avantages

- **Voir tout le code** : contexte complet visible
- **Modifier n'importe où** : pas de contrainte de flux
- **Évaluer sélectivement** : ligne par ligne ou tout
- **Pas de perte** : le code reste affiché
- **Debuggage facilité** : indicateurs visuels d'état

---

## 🛠️ Architecture Technique

### Structure HTML

```html
<div class="main-content">
  <!-- Panneau éditeur -->
  <div class="editor-panel">
    <div class="line-numbers"></div>
    <textarea id="codeEditor"></textarea>
  </div>
  
  <!-- Panneau console -->
  <div class="console-panel">
    <div class="console-output"></div>
  </div>
</div>
```

### Fonctions JavaScript principales

```javascript
// Parsing
parseLine(line)              → { valid, type, error }
onEditorChange()             → Met à jour numéros + état

// Évaluation
evaluateCode()               → Envoie tout
evaluateSelection()          → Envoie ligne courante
clearAllPatterns()           → clear

// Gestion état
linesState[lineNum]          → État de chaque ligne
updateLineNumbers()          → UI des numéros

// Communication
sendCommand(cmd)             → Envoie via Serial
readLoop()                   → Lit réponses Teensy
```

---

## 🎨 Thème Visuel

### Couleurs

- **Fond éditeur** : `#0a0e27` (bleu nuit)
- **Fond numéros** : `#16213e` (bleu foncé)
- **Texte code** : `#00ff00` (vert Matrix)
- **Ligne active** : `#00ff8820` (vert transparent)
- **Bordures** : `#00ff88` (cyan)
- **Erreurs** : `#ff4444` (rouge)
- **Modifié** : `#ffaa00` (orange)

### Police

- **Monospace** : Courier New, Consolas
- **Taille** : 14px
- **Line-height** : 1.6 (lisibilité)

---

## 📊 Comparaison avec Tidal Cycles

| Fonctionnalité | Tidal Cycles | TidalTeensy Editor |
|----------------|--------------|-------------------|
| Éditeur multi-lignes | ✅ Atom/VS Code | ✅ Intégré web |
| Éval tout | ✅ | ✅ Ctrl+Enter |
| Éval sélection | ✅ | ✅ Shift+Enter |
| Coloration syntaxe | ✅ | 🔶 Basique |
| Auto-complétion | ✅ | ❌ Pas encore |
| Hush (stop) | ✅ | ✅ Ctrl+. |
| Historique | ✅ | 🔶 Implicite (code reste) |

---

## 🚀 Améliorations Futures Possibles

### Court terme
1. **Coloration syntaxique avancée**
   - Surligner `d1-d8` en bleu
   - Samples en jaune
   - Notes en violet
   - Commandes en vert

2. **Auto-complétion**
   - Tab après `d1` → liste de samples
   - Tab après `sine:` → notes suggérées
   - Ctrl+Space → menu contextuel

3. **Recherche/Remplacement**
   - Ctrl+F : chercher
   - Ctrl+H : remplacer

### Moyen terme
4. **Sauvegarde/Chargement**
   - Save code localement (localStorage)
   - Export/Import fichiers .tidal
   - Presets de sessions

5. **Undo/Redo**
   - Ctrl+Z : annuler
   - Ctrl+Y : refaire
   - Historique des modifications

6. **Thèmes**
   - Mode sombre/clair
   - Palettes de couleurs
   - Personnalisation

### Long terme
7. **Collaboration**
   - Partage de session en temps réel
   - Code sharing via URL
   - Session multi-utilisateur

8. **Visualisation**
   - Timeline visuelle des patterns
   - Waveform display
   - Spectrum analyzer

---

## 🐛 Limitations Actuelles

1. **Pas de coloration syntaxique** : texte monochrome (vert)
2. **Commentaires basiques** : seulement `--` en début de ligne
3. **Pas d'historique Ctrl+Z** : natif du textarea seulement
4. **Pas de numéros de ligne cliquables** : pas de sélection par clic
5. **Parsing simple** : détection basique des erreurs

---

## 📖 Documentation Mise à Jour

Les documents suivants ont été **mis à jour** :
- ✅ **README.md** : mention de la nouvelle interface
- ✅ **setup.md** : instructions d'utilisation
- 🆕 **EDITOR_INTERFACE.md** : ce document

---

## ✅ Tests Recommandés

1. **Test interface** : Ouvrir `web_interface.html` dans Chrome
2. **Test connexion** : Se connecter au Teensy
3. **Test écriture** : Écrire plusieurs lignes de code
4. **Test Ctrl+Enter** : Évaluer tout le code
5. **Test Shift+Enter** : Évaluer une ligne
6. **Test modification** : Modifier puis ré-évaluer
7. **Test Ctrl+.** : Arrêter tous les patterns
8. **Test commentaires** : Vérifier que `--` fonctionne
9. **Test quick buttons** : Insérer du code via boutons
10. **Test scroll** : Vérifier sync numéros/éditeur

---

## 🎉 Résumé

L'interface est maintenant un **véritable éditeur de code live** :
- ✅ Multi-lignes avec numérotation
- ✅ Parsing en temps réel
- ✅ Modification libre
- ✅ Évaluation sélective
- ✅ Console séparée
- ✅ Raccourcis clavier
- ✅ Indicateurs visuels d'état
- ✅ Quick commands

**Workflow naturel** pour le live coding comme Tidal Cycles ! 🎵🎹
