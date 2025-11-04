# 🧪 Plan de Test - Interface TidalTeensy

## 📋 Checklist de Test

### ✅ Phase 1 : Démarrage

- [ ] **1.1** Ouvrir un terminal dans le dossier TidalTeensy
- [ ] **1.2** Exécuter `python serve_interface.py`
- [ ] **1.3** Vérifier le message de confirmation :
  ```
  🎹 TidalTeensy Interface Server
  🌐 Open in browser: http://localhost:8000/web_interface.html
  ```
- [ ] **1.4** Ouvrir Chrome/Edge/Opera
- [ ] **1.5** Aller sur `http://localhost:8000/web_interface.html`
- [ ] **1.6** Vérifier que la page se charge sans erreur

**Résultat attendu** : Interface visible avec modale de connexion

---

### ✅ Phase 2 : Connexion

- [ ] **2.1** Brancher le Teensy 4.0 en USB
- [ ] **2.2** Cliquer sur "🔌 Se connecter au Teensy"
- [ ] **2.3** Vérifier que la fenêtre de sélection de port s'ouvre
- [ ] **2.4** Sélectionner le port USB du Teensy
- [ ] **2.5** Cliquer sur "Connecter"
- [ ] **2.6** Vérifier dans la console :
  ```
  ✓ Connecté au Teensy!
  ```
- [ ] **2.7** Vérifier que le point en haut à droite est VERT
- [ ] **2.8** Vérifier que le statut indique "Connecté"

**Résultat attendu** : Connexion établie, modale fermée

---

### ✅ Phase 3 : Interface Visuelle

- [ ] **3.1** Vérifier la présence de l'éditeur de code à gauche
- [ ] **3.2** Vérifier la numérotation des lignes (1, 2, 3...)
- [ ] **3.3** Vérifier la console à droite
- [ ] **3.4** Vérifier les boutons en haut de l'éditeur :
  - [ ] "▶ Evaluate All"
  - [ ] "▶ Eval Line"
  - [ ] "■ Stop All"
- [ ] **3.5** Vérifier les quick commands en bas :
  - [ ] "d1 drums"
  - [ ] "d2 bass"
  - [ ] "d3 chord"
  - [ ] "bpm 140"
  - [ ] "clear all"

**Résultat attendu** : Interface complète et lisible

---

### ✅ Phase 4 : Quick Commands

- [ ] **4.1** Cliquer sur "d1 drums"
- [ ] **4.2** Vérifier que `d1 bd sd hh cp` apparaît dans l'éditeur
- [ ] **4.3** Cliquer sur "d2 bass"
- [ ] **4.4** Vérifier que `d2 bass:c2*4` s'ajoute en dessous
- [ ] **4.5** Cliquer sur "bpm 140"
- [ ] **4.6** Vérifier que `bpm 140` s'ajoute
- [ ] **4.7** Vérifier que le curseur se place après chaque insertion

**Résultat attendu** : Code inséré correctement

---

### ✅ Phase 5 : Numérotation et État

- [ ] **5.1** Cliquer sur la ligne 1
- [ ] **5.2** Vérifier que le numéro 1 devient VERT (ligne active)
- [ ] **5.3** Cliquer sur la ligne 2
- [ ] **5.4** Vérifier que le numéro 2 devient VERT
- [ ] **5.5** Écrire du texte dans l'éditeur
- [ ] **5.6** Vérifier que les numéros de ligne se mettent à jour
- [ ] **5.7** Scroller dans l'éditeur
- [ ] **5.8** Vérifier que les numéros scrollent ensemble

**Résultat attendu** : Numérotation synchronisée et ligne active visible

---

### ✅ Phase 6 : Évaluation Ligne par Ligne (Shift+Enter)

- [ ] **6.1** Effacer l'éditeur
- [ ] **6.2** Écrire : `d1 bd sd hh cp`
- [ ] **6.3** Placer le curseur sur cette ligne
- [ ] **6.4** Appuyer sur **Shift+Enter**
- [ ] **6.5** Vérifier dans la console :
  ```
  → Line 1: d1 bd sd hh cp
  ```
- [ ] **6.6** Vérifier que le Teensy répond (message en vert)
- [ ] **6.7** **ÉCOUTER** : vérifier que le son joue (drums)

**Résultat attendu** : Ligne envoyée, pattern joue

- [ ] **6.8** Ajouter une ligne 2 : `d2 bd*4`
- [ ] **6.9** Placer curseur sur ligne 2
- [ ] **6.10** Appuyer sur **Shift+Enter**
- [ ] **6.11** **ÉCOUTER** : vérifier que d2 s'ajoute au son

**Résultat attendu** : Deuxième pattern s'ajoute

---

### ✅ Phase 7 : Évaluation Complète (Ctrl+Enter)

- [ ] **7.1** Effacer l'éditeur
- [ ] **7.2** Écrire plusieurs lignes :
  ```
  d1 bd sd hh cp
  d2 bd*4
  d3 hh*8
  bpm 130
  ```
- [ ] **7.3** Appuyer sur **Ctrl+Enter**
- [ ] **7.4** Vérifier dans la console :
  ```
  ▶ Évaluation de tout le code...
  → d1 bd sd hh cp
  → d2 bd*4
  → d3 hh*8
  → bpm 130
  ✓ 4 commande(s) envoyée(s)
  ```
- [ ] **7.5** **ÉCOUTER** : vérifier que tous les patterns jouent

**Résultat attendu** : Tout le code exécuté d'un coup

---

### ✅ Phase 8 : Modification en Live

- [ ] **8.1** Avec le code de l'étape 7 qui joue
- [ ] **8.2** Modifier la ligne 1 : `d1 bd*8`
- [ ] **8.3** Vérifier que le numéro de ligne 1 devient ORANGE (modifié)
- [ ] **8.4** Placer curseur sur ligne 1
- [ ] **8.5** Appuyer sur **Shift+Enter**
- [ ] **8.6** Vérifier que le numéro redevient GRIS/NORMAL
- [ ] **8.7** **ÉCOUTER** : vérifier que d1 change (bd plus rapide)

**Résultat attendu** : Pattern modifié en temps réel

---

### ✅ Phase 9 : Stop (Ctrl+.)

- [ ] **9.1** Avec des patterns qui jouent
- [ ] **9.2** Appuyer sur **Ctrl+.**
- [ ] **9.3** Vérifier dans la console :
  ```
  ■ Arrêt de tous les patterns...
  ✓ Tous les patterns arrêtés
  ```
- [ ] **9.4** **ÉCOUTER** : vérifier que tout s'arrête

**Résultat attendu** : Silence immédiat

---

### ✅ Phase 10 : Commentaires

- [ ] **10.1** Écrire :
  ```
  -- Drums
  d1 bd sd hh cp
  -- Bass
  d2 bass:c2*4
  ```
- [ ] **10.2** Appuyer sur **Ctrl+Enter**
- [ ] **10.3** Vérifier que seules les lignes d1 et d2 sont envoyées
- [ ] **10.4** Vérifier que les commentaires sont ignorés

**Résultat attendu** : Commentaires ignorés lors de l'évaluation

---

### ✅ Phase 11 : Notes Mélodiques

- [ ] **11.1** Écrire : `d4 sine:c4 sine:e4 sine:g4`
- [ ] **11.2** Appuyer sur **Shift+Enter**
- [ ] **11.3** **ÉCOUTER** : vérifier l'accord (3 notes ensemble)
- [ ] **11.4** Modifier : `d4 bass:c2*4`
- [ ] **11.5** Appuyer sur **Shift+Enter**
- [ ] **11.6** **ÉCOUTER** : vérifier la ligne de basse

**Résultat attendu** : Notes musicales fonctionnent

---

### ✅ Phase 12 : Validation Syntaxique

- [ ] **12.1** Écrire une ligne invalide : `d9 bd sd`
- [ ] **12.2** Appuyer sur **Shift+Enter**
- [ ] **12.3** Vérifier dans la console :
  ```
  Erreur ligne X: Syntax non reconnue
  ```
- [ ] **12.4** Vérifier que le numéro de ligne devient ROUGE
- [ ] **12.5** Corriger : `d1 bd sd`
- [ ] **12.6** Vérifier que le numéro redevient normal

**Résultat attendu** : Erreurs détectées et affichées

---

### ✅ Phase 13 : Clear Console

- [ ] **13.1** Envoyer plusieurs commandes
- [ ] **13.2** Vérifier que la console est remplie
- [ ] **13.3** Appuyer sur **Ctrl+L**
- [ ] **13.4** Vérifier que la console est effacée :
  ```
  Console cleared
  ```
- [ ] **13.5** Vérifier que l'éditeur n'est PAS effacé

**Résultat attendu** : Console clear, code intact

---

### ✅ Phase 14 : Déconnexion

- [ ] **14.1** Cliquer sur "Déconnecter" en haut à droite
- [ ] **14.2** Vérifier dans la console :
  ```
  ✓ Déconnecté
  ```
- [ ] **14.3** Vérifier que le point devient ROUGE
- [ ] **14.4** Vérifier que le statut indique "Déconnecté"
- [ ] **14.5** Essayer d'envoyer une commande (**Shift+Enter**)
- [ ] **14.6** Vérifier l'erreur :
  ```
  ✗ Non connecté au Teensy
  ```

**Résultat attendu** : Déconnexion propre

---

### ✅ Phase 15 : Reconnexion

- [ ] **15.1** Cliquer sur "Déconnecter" (qui devient "Se connecter")
- [ ] **15.2** Répéter Phase 2
- [ ] **15.3** Vérifier que tout refonctionne

**Résultat attendu** : Reconnexion réussie

---

## 🐛 Bugs Potentiels à Vérifier

### Layout
- [ ] Les deux panneaux (éditeur + console) sont visibles
- [ ] Pas de scrollbar horizontal (tout tient dans la fenêtre)
- [ ] Redimensionnement fenêtre fonctionne

### Synchronisation
- [ ] Numéros de ligne scrollent avec l'éditeur
- [ ] Ligne active mise en surbrillance
- [ ] Indicateurs d'état (orange/rouge) fonctionnent

### Performance
- [ ] Pas de lag lors de l'édition
- [ ] Parsing en temps réel fluide
- [ ] Console scroll automatique sans saccade

### Edge Cases
- [ ] Ligne vide (ignorée)
- [ ] Lignes avec espaces seulement (ignorées)
- [ ] Très longue ligne (affichage correct)
- [ ] Beaucoup de lignes (>50) (scroll fonctionne)

---

## 📊 Résultats Attendus

### Fonctionnel ✅
- Connexion au Teensy
- Écriture de code multi-lignes
- Évaluation ligne par ligne (Shift+Enter)
- Évaluation complète (Ctrl+Enter)
- Modification en live
- Stop immédiat (Ctrl+.)
- Notes mélodiques
- Commentaires ignorés

### Visuel ✅
- Interface en 2 colonnes
- Numérotation des lignes
- Ligne active en vert
- Lignes modifiées en orange
- Lignes erreur en rouge
- Console colorée (vert/cyan/orange/rouge)

### Pratique ✅
- Workflow intuitif
- Raccourcis clavier fonctionnels
- Quick commands utiles
- Parsing en temps réel

---

## 🎯 Critères de Succès

| Critère | Description | Statut |
|---------|-------------|--------|
| **Connexion** | Se connecte au Teensy sans erreur | ⬜ |
| **Édition** | Peut écrire du code multi-lignes | ⬜ |
| **Évaluation** | Ctrl+Enter et Shift+Enter fonctionnent | ⬜ |
| **Modification** | Peut modifier et ré-évaluer | ⬜ |
| **Indicateurs** | Numéros colorés (vert/orange/rouge) | ⬜ |
| **Console** | Messages affichés correctement | ⬜ |
| **Audio** | Patterns jouent sur le Teensy | ⬜ |
| **Stop** | Ctrl+. arrête tout | ⬜ |
| **Notes** | Instruments mélodiques fonctionnent | ⬜ |
| **Parsing** | Erreurs détectées en temps réel | ⬜ |

---

## 📝 Notes de Test

```
Date du test : _______________
Navigateur : Chrome / Edge / Opera (version: _______)
OS : Windows / Linux / Mac
Teensy : 4.0 / 4.1

Résultats :
[X] Tous les tests passent
[ ] Certains tests échouent (détails ci-dessous)

Bugs trouvés :
1. _______________________________________________
2. _______________________________________________
3. _______________________________________________

Améliorations suggérées :
1. _______________________________________________
2. _______________________________________________
3. _______________________________________________

Impressions générales :
_____________________________________________________
_____________________________________________________
_____________________________________________________
```

---

## 🎉 Test Réussi ?

Si tous les tests passent, vous avez maintenant :
- ✅ Un éditeur de code multi-lignes fonctionnel
- ✅ Un système de parsing en temps réel
- ✅ Un workflow de live coding professionnel
- ✅ Une interface moderne et intuitive

**Félicitations ! Vous pouvez maintenant faire du live coding avec TidalTeensy ! 🎵🎹**
