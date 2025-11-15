# TP3 : Listes Chaînées - RAPPORT

## Partie 1 : Listes de Elmt_t

### 1.1 Implémentation Générale

Cette implémentation propose une librairie complète de gestion de listes chaînées en C avec support des éléments de type `int` (via `typedef int Elmt_t`).

**Fichiers implémentés :**
- `elmt_t.h / elmt_t.c` : Gestion des éléments
- `list.h / list.c` : Listes simplement chaînées
- `test.c` : Tests principaux
- `Makefile` : Compilation

### 1.2 Fonctions de Base

#### is_empty() - O(1)
Teste si une liste est vide en vérifiant si le pointeur est NULL.

#### create_empty_list() - O(1)
Retourne NULL (liste vide).

#### print_list() - O(n)
Affiche les éléments au format `[a, b, c]` en utilisant la fonction de comparaison passée en paramètre.

#### create_cell() / free_cell() - O(1)
Allocation/libération dynamique d'une cellule.

#### insert_first() - O(1)
Insère un élément en tête de liste. La cellule est créée puis ajoutée en tête.

#### free_list() - O(n)
Libère toute la liste en parcourant et libérant chaque cellule et son élément.

### 1.3 Fonctions Avancées

#### insert_last() - O(n)
Insère un élément en queue de liste.
- Si liste vide : appelle `insert_first()`
- Sinon : recherche le dernier élément et appelle `insert_after()`

La fonction utilise `insert_after()` comme helper pour insérer après une cellule donnée.

#### search() - O(n)
Recherche un élément dans une liste non triée en utilisant la fonction de comparaison passée en paramètre. Retourne la première cellule contenant l'élément ou NULL.

#### length() - O(n)
Parcourt la liste et compte le nombre de cellules.

#### concatenate() - O(n)
Concatène deux listes en trouvant la fin de `l1` et connectant le dernier élément au début de `l2`.

#### mirror_it() - O(n)
Inverse une liste de façon itérative en trois pointeurs : `prev`, `current`, `next`.
- Chaque cellule a son pointeur `next` réorienté vers l'élément précédent
- Complexité : O(n) avec une seule passe

#### mirror_rec() - O(n)
Inverse une liste de façon récursive.
- Descend jusqu'à la fin de la liste
- À la remontée, réoriente les pointeurs
- Risque de débordement de pile pour très grandes listes

#### search_k() - O(n)
Retourne la k-ème cellule (1-indexée) ou NULL si n'existe pas.

#### sorted_search() - O(n)
Recherche dans une liste triée.
- Retourne 1 si l'élément est trouvé
- Retourne 0 sinon, avec `res` pointant sur le dernier maillon avec élément < e
- La double indirection permet de modifier l'endroit trouvé

#### remove_cell() - O(n)
Retire une cellule de la liste.
- Parcourt la liste pour trouver et retirer la cellule
- Retourne 1 si suppression réussie, 0 sinon
- L'appelant doit libérer la mémoire de la cellule

#### remove_all() - O(n²)
Retire toutes les occurrences d'un élément et les ajoute à une nouvelle liste retournée.

#### cut_sup() - O(n²)
Enlève tous les maillons avec une valeur > e et les ajoute à une nouvelle liste retournée.

#### cut_inf() - O(n²)
Enlève tous les maillons avec une valeur < e et les ajoute à une nouvelle liste retournée.

#### canonicalyze() - O(n²)
Enlève tous les doublons et retourne une nouvelle liste contenant les éléments retirés.
Note : Ne peut pas modifier la tête de liste ; si doublon en tête, c'est la copie qui est retirée.

---

## Partie 2 : Tri (Bonus)

Deux algorithmes de tri ont été implémentés dans `sort_list.h / sort_list.c` :

### 2.1 Insertion Sort - O(n²)

**Implémentation :**
- Parcourt la liste et insère chaque élément à sa bonne position
- Construit progressivement une liste triée

**Complexité :**
- Pire cas : O(n²) (liste inversée)
- Meilleur cas : O(n) (liste déjà triée)
- Cas moyen : O(n²)

**Avantages pour les listes :**
- ✅ Stable (maintient l'ordre des éléments égaux)
- ✅ Efficace pour petites listes
- ✅ Implémentation simple

**Inconvénients pour les listes :**
- ❌ Traversées répétées O(n) pour chaque insertion
- ❌ O(n²) en pire cas

**Verdict :** Acceptable pour listes petites/moyennes.

### 2.2 Merge Sort - O(n log n) ⭐

**Implémentation :**
- Divise la liste en deux moitiés
- Fusionne les deux moitiés triées récursivement

**Complexité :**
- Tous cas : O(n log n)
- Pire cas mémoire : O(n) pour fusion

**Avantages pour les listes :**
- ✅ O(n log n) garantis (optimal pour tri)
- ✅ **N'utilise PAS l'accès aléatoire** (contrairement à QuickSort)
- ✅ Fonctionne parfaitement avec structure chaînée
- ✅ Stable
- ✅ Diviser pour régner s'adapte bien aux listes

**Inconvénients pour les listes :**
- ❌ O(n) mémoire supplémentaire

**Verdict : MEILLEUR CHOIX pour listes chaînées**

### 2.3 Analyse Comparative

| Algorithme | Tableau | Liste | Raison |
|-----------|--------|-------|--------|
| **Bubble Sort** | O(n²) | O(n²) | Même performance, listes : pas d'accès aléatoire |
| **Insertion Sort** | O(n²) | O(n²) | Acceptable mais traversées coûteuses |
| **QuickSort** | O(n log n) | ❌ **Mauvais** | Besoin d'accès aléatoire (pivot) |
| **Merge Sort** | O(n log n) | ✅ **OPTIMAL** | Pas besoin accès aléatoire, O(n log n) garanti |
| **Heap Sort** | O(n log n) | ❌ **Mauvais** | Structure non adaptée aux listes |

**Conclusion :** Le Merge Sort est le meilleur choix pour les listes chaînées car il exploite la structure itérative sans nécessiter d'accès aléatoire.

---

## Partie 3 : Listes Doublement Chaînées

### 3.1 Modifications Apportées

**Nouveau répertoire :** `double_list/` avec copie des fichiers et adaptations

**Fichiers :**
- `double_list.h / double_list.c` : Listes doublement chaînées
- `elmt_t.h / elmt_t.c` : Copie locale
- `test.c` : Tests adaptés
- `Makefile` : Compilation locale

### 3.2 Définition du Type Cell

**Avant (simplement chaînée) :**
```c
typedef struct Cell {
    Elmt_t *data;
    struct Cell *next;
} Cell;
```

**Après (doublement chaînée) :**
```c
typedef struct Cell {
    Elmt_t *data;
    struct Cell *next;
    struct Cell *prev;  // Nouveau pointeur
} Cell;
```

**Invariants :**
- Premier maillon : `prev = NULL`
- Dernier maillon : `next = NULL`

### 3.3 Adaptations des Fonctions

Toutes les fonctions ont été adaptées sauf `mirror_it` et `mirror_rec` (plus d'intérêt avec chaînage bidirectionnel).

#### create_cell() - Adaptation
Initialise aussi `prev = NULL` en plus de `next = NULL`.

#### insert_first() - Adaptation
Après insertion :
- `new_cell->prev = NULL`
- Si ancienne tête existait : `old_head->prev = new_cell`

#### insert_last() - Adaptation
Avant insertion du dernier : `prev` doit pointer sur l'avant-dernier.

#### remove_cell() - Adaptation Majeure
Devient plus facile avec double chaînage :
- Savoir si on doit retirer la tête (pas besoin de parcourir depuis le début)
- Connecter `prev->next` et `next->prev` directement
- Complexité reste O(n) pour trouver le maillon

#### Autres fonctions
`search()`, `search_k()`, `sorted_search()` : pas de changements (traversée identique).

### 3.4 Avantages/Inconvénients de Double Chaînage

**Avantages :**
- ✅ Traversée bidirectionnelle
- ✅ Suppression simplifiée (pas besoin du prédécesseur)
- ✅ Opérations de swap directes
- ✅ Meilleure pour certaines structures (deques)

**Inconvénients :**
- ❌ +8 octets par cellule (sur 64-bit)
- ❌ Opérations insertion/suppression plus complexes
- ❌ Deux pointeurs à maintenir = plus de bugs possibles
- ❌ Corruption potentielle si un pointeur est mal géré

---

## Partie 4 : FIFO et Piles

Pour chacune des 8 configurations, on analyse la complexité des opérations d'ajout et de retrait.

### 4.1 Pile avec Tableau

#### Configuration A : Ajout/Retrait au DÉBUT

```
Opération     | Complexité | Raison
──────────────┼────────────┼────────────────────────────
Push (début)  | O(n)       | Doit décaler tous les éléments
Pop (début)   | O(n)       | Doit décaler tous les éléments
```

**Analyse :**
- Mauvaise performance
- Chaque push/pop requiert une recopie complète du tableau

**Optimisation possible :**
- Utiliser une file circulaire avec indices (head, tail)
- Permet O(1) si capacité suffisante

#### Configuration B : Ajout/Retrait en FIN

```
Opération     | Complexité | Raison
──────────────┼────────────┼────────────────────────────
Push (fin)    | O(1) amorti| Append direct + realloc rare
Pop (fin)     | O(1)       | Décrémente la taille
```

**Analyse :**
- ✅ Excellent pour piles
- Comportement standard des piles avec tableaux
- O(1) amorti = très efficace

**Optimisation possible :**
- Pré-allouer avec facteur 2 (capacité > taille)
- Réduit fréquence des reallocations

---

### 4.2 Pile avec Liste Chaînée

#### Configuration A : Ajout/Retrait au DÉBUT

```
Opération     | Complexité | Raison
──────────────┼────────────┼────────────────────────────
Push (début)  | O(1)       | Insertion simple en tête
Pop (début)   | O(1)       | Suppression simple en tête
```

**Analyse :**
- ✅ Excellent pour piles
- Implémentation naturelle avec listes
- Pas d'allocation répétée comme tableaux

**Avantages :**
- ✅ Mémoire utilisée proportionnelle à nombre éléments
- ✅ Pas de risque de débordement

**Inconvénients :**
- ❌ Overhead mémoire par maillon (+2 pointeurs = 16 bytes)
- ❌ Cache-friendly moins bon que tableau

#### Configuration B : Ajout/Retrait en FIN

```
Opération     | Complexité | Raison
──────────────┼────────────┼────────────────────────────
Push (fin)    | O(n)       | Traverse jusqu'à la fin
Pop (fin)     | O(n)       | Traverse pour trouver avant-dernier
```

**Analyse :**
- ❌ Très mauvais
- Chaque opération nécessite une traversée complète

**Optimisation possible :**
- **SOLUTION :** Ajouter pointeur `tail` à la structure pile
- Permet O(1) pour push, mais pop reste O(n) (besoin de prédécesseur)
- **MEILLEURE SOLUTION :** Utiliser double chaînage
- Avec `prev`, pop en fin devient O(1)

---

### 4.3 FIFO avec Tableau

#### Configuration A : Ajout au DÉBUT, Retrait en FIN

```
Opération        | Complexité | Raison
─────────────────┼────────────┼────────────────────────────
Enqueue (début)  | O(n)       | Doit décaler tous les éléments
Dequeue (fin)    | O(1)       | Accès direct dernier index
```

**Analyse :**
- ❌ Mauvais : Enqueue coûteux

#### Configuration B : Ajout en FIN, Retrait au DÉBUT

```
Opération        | Complexité | Raison
─────────────────┼────────────┼────────────────────────────
Enqueue (fin)    | O(1) amorti| Append direct
Dequeue (début)  | O(n)       | Doit décaler tous les éléments
```

**Analyse :**
- ❌ Mauvais : Dequeue coûteux

**Optimisation essentielle :**
- **File circulaire avec indices (head, tail)**
- Permet O(1) pour BOTH opérations
- Utilisation cyclique du tableau
- Reallocation nécessaire que si taille dépasse capacité

**Complexité avec file circulaire :**
```
Enqueue : O(1) amorti
Dequeue : O(1) amorti
```

---

### 4.4 FIFO avec Liste Chaînée

#### Configuration A : Ajout au DÉBUT, Retrait en FIN

```
Opération        | Complexité | Raison
─────────────────┼────────────┼────────────────────────────
Enqueue (début)  | O(1)       | Insertion simple en tête
Dequeue (fin)    | O(n)       | Traverse pour trouver avant-dernier
```

**Analyse :**
- ❌ Mauvais : Dequeue O(n)

#### Configuration B : Ajout en FIN, Retrait au DÉBUT

```
Opération        | Complexité | Raison
─────────────────┼────────────┼────────────────────────────
Enqueue (fin)    | O(n)       | Traverse pour atteindre la fin
Dequeue (début)  | O(1)       | Suppression simple en tête
```

**Analyse :**
- ❌ Mauvais : Enqueue O(n)

**Optimisation essentielle :**
- **Ajouter pointeur `tail` à la structure FIFO**
- Pointer toujours sur le dernier maillon

**Complexité optimisée :**
```
Enqueue (fin) : O(1)       (direct en tail)
Dequeue (début) : O(1)     (direct en head)
```

**Structure optimale :**
```c
typedef struct Queue {
    Cell *head;  // Pointeur vers premier maillon
    Cell *tail;  // Pointeur vers dernier maillon
} Queue;
```

---

## Partie 5 : Tableau Synthétique de Complexité

### Piles

| Implémentation | Push | Pop | Complexité moyenne |
|---|---|---|---|
| **Tableau - début** | O(n) | O(n) | ❌ Mauvais |
| **Tableau - fin** | O(1)* | O(1) | ✅ Excellent |
| **Liste - début** | O(1) | O(1) | ✅ Excellent |
| **Liste - fin** | O(n) | O(n) | ❌ Mauvais |
| **Liste - fin + tail** | O(1) | O(n)* | ⚠️ Demi-optimisé |
| **Liste - fin + double** | O(1) | O(1) | ✅ Excellent |

*O(1) amorti pour tableau avec realloc
*O(n) car besoin prédécesseur même avec tail

### Files (FIFO)

| Implémentation | Enqueue | Dequeue | Complexité moyenne |
|---|---|---|---|
| **Tableau - début/fin** | O(n) | O(1) | ❌ Mauvais |
| **Tableau - fin/début** | O(1)* | O(n) | ❌ Mauvais |
| **Tableau circulaire** | O(1)* | O(1)* | ✅ Excellent |
| **Liste - début/fin** | O(1) | O(n) | ❌ Mauvais |
| **Liste - fin/début** | O(n) | O(1) | ❌ Mauvais |
| **Liste + head/tail** | O(1) | O(1) | ✅ Excellent |

*O(1) amorti

---

## Partie 6 : Recommandations Finales

### 6.1 Pour Piles
- **Meilleur choix : Tableau en fin** (simplicity + performance)
- Alternative : Liste chaînée en tête (si mémoire dynamique préférée)

### 6.2 Pour Files FIFO
- **Meilleur choix : Tableau circulaire** (performance optimale O(1) amorti)
- Alternative : Liste chaînée + head/tail pointers (flexibilité mémoire)

### 6.3 Files d'Attente avec Priorités

**Structures de données appropriées (par ordre de préférence) :**

1. **Heap (Binary Heap)** ⭐⭐⭐
   - `Insert` : O(log n)
   - `ExtractMin` : O(log n)
   - `Complexité` : Excellente
   - **Avantage** : Opérations logarithmiques, cache-friendly
   - **Inconvénient** : Besoin accès aléatoire (mieux avec tableau)

2. **Arbre Équilibré (AVL, Red-Black)**
   - `Insert` : O(log n)
   - `ExtractMin` : O(log n)
   - **Avantage** : Flexible, supporte recherche
   - **Inconvénient** : Plus complexe à implémenter

3. **Liste triée avec pointeur head**
   - `Insert` : O(n) (recherche position + insertion)
   - `ExtractMin` : O(1) (toujours le premier)
   - **Avantage** : Simple
   - **Inconvénient** : Insert coûteux

4. **Plusieurs files (une par priorité)**
   - `Insert` : O(1) (direct dans file de priorité)
   - `ExtractMin` : O(1) (cherche première file non-vide)
   - **Avantage** : Très simple, rapide si priorités bornées
   - **Inconvénient** : Consomme mémoire proportionnelle aux priorités

**Verdict :** **Heap est le meilleur choix** pour files de priorité générales.

---

## Conclusion

Cette implémentation propose une librairie complète et robuste :
- ✅ Listes simplement chaînées avec 25+ fonctions
- ✅ Listes doublement chaînées adaptées
- ✅ Algorithmes de tri optimisés (Merge Sort recommandé)
- ✅ Implémentations de piles et files avec analyses complètes
- ✅ Recommandations pratiques pour chaque structure

**Choix algorithmiques :** Tous les choix sont justifiés par analyse de complexité et cas d'usage réels.
