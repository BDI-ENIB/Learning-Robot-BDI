# Learning-Robot-BDI
<!--![hey](https://img.shields.io/github/commit-activity/m/BDI-ENIB/Learning-Robot-BDI?style=for-the-badge)
à insérer quand j'aurai trouvé un truc qui marche-->

Ce projet a pour but d'introduire à la robotique les membres du pôle robot du BDI.
Il a été conçu pour être facilement compris, changé et amélioré donc n'hésitez pas à ajouter votre pierre à l'édifice !
L'objectif est de participer à la coupe de France de Robotique à la fin de l'année  ;)
## I-Préparer et comprendre l'environnement

le Learning Robot a été conçu avec une teensy 3.5.

Le code est en C++, compilé via arduino (avec l'extension teensyduino).

Pour mettre en commun le code et tracer les différentes versions, nous utilisons git et github.

Si vous ne connaissez pas un des logiciels, je vous l'explique plus bas, aucun soucis X)
Sinon vérifiez bien que vous avez tous les logiciels pour coder et passez directement au [chapitre suivant](https://github.com/BDI-ENIB/Learning-Robot-BDI#ii-le-fonctionnement-du-robot-en-bref) :)

Je recommande pour bien travailler sur ce projet d'avoir : 
* un compte github (avec une adresse mail perso si vous voulez garder les accès au projet même après être diplômé)
* git 
* une version récente d'Arduino **venant du site officiel**.
* l'extension teensyduino 
* VScode avec une extension git pour commit et push au minimum (au hasard gitlens)

### Mention spéciale : git et github
la sheetcheat git: [github education](https://education.github.com/git-cheat-sheet-education.pdf)

Les tutos pratiques et rapides pour git: [egghead tutorial](https://egghead.io/lessons/misc-practical-git-create-local-repos-with-git-init)

Git est le logiciel qui permet de versionner le projet et Github est la plateforme qui stocke la version du code en ligne qui va servir de référence.

Pour changer le code il faut :
* cloner le repository (créer un version locale [stockée sur ton ordinateur] reliée à la version en ligne) 
* faire les changements que tu veux
* commit (mettre à jour la version locale du code)
* push (mettre à jour la version github du code)

Si tu veux faire de gros changements, je te conseille de créer une branche au repository sur le github. Cela permet de travailler sur le code, le tester et quand tout marche bien, tu peux le mettre sur le main. Si d'autres personnes veulent effectuer des changements sur le code principal, ils ne seront pas impactés par les tests que tu aura fait.

### Mention spéciale : Arduino
[Le Guide officiel](https://www.arduino.cc/en/Guide)

[L'extension teensyduino](https://www.pjrc.com/teensy/td_download.html)

Pour encore plus de comfort, je conseille de mettre dans les préférences un éditeur externe, c'est à dire utiliser arduino pour compiler et téléverser le code mais l'éditeur externe pour le modifier (vous voyez où je veux en venir ? Utilisez VScode !) puisque le code est majoritairement composé de fichiers Cpp et hpp et que seuls les fichiers dans le même dossier que le .ino sont lisible par Arduino, vous allez avoir besoin de deux éditeurs (Arduino et Vscode), alors autant tout regrouper dans un seul et garder Arduino pour la compilation et le téléversement. Voici un tuto pour changer les préférences Arduino : [locoduino](https://www.locoduino.org/spip.php?article207)


### Mention spéciale : VSCode
[Les shortcuts qui font plaisir](https://code.visualstudio.com/shortcuts/keyboard-shortcuts-windows.pdf)

Ahhh VSCode. Si ça se voit pas je l'aime bien. Vous pouvez prendre un autre éditeur bien sûr mais celui ci permet de vite installer une extension git qui permet de commit et push et de ne plus taper les commandes dans un terminal !



## II-Le fonctionnement du robot en bref

Pour comprendre les agissements du robot, il faut comprendre le découpage général du code. Voici les 4 grandes parties !

### Etape 0 la plus importante, La préparation !
Eh oui ! Pour aller tout droit et être à peu près correct dans les angles, il faut savoir 2-3 mesures.
C'est à refaire chaque année minimum, encore mieux après chaque grand déplacement du robot (et oui le trimballer toute une aprèm pour des portes ouvertes ou autre ça compte)

Tout les paramètres à vérifier sont dans le summerbot-main-clean.ino

Vous allez avoir besoin: 

* Des paramètres du match dans le panneau de configuration(1)
    * La longueur du match en millisecondes (Le robot s'arrête après)
    * le point de départ dans votre système de repère absolu
        * Il n'est pas utile pour le moment MAIS il est à garder vous décidez de changer l'IA ou de finir un certain système de repérage absolu (demandez à Evan si vous avez pas la ref). Comme c'est une amélioration très intéressante pour toute personne s'intéressant un tant soit peu au code, je vous prie de la garder.(exemple : créer une IA qui en fonction de la position fait une action, ce qui permet de ne pas être coincé par le robot adverse puisqu'il y aurait possibilité de changer de tâche)

* Des paramètres des capteurs dans le panneau de configuration(1)

* Des paramètres des moteurs dans le panneau de lancement(2)
    * l'entraxe (la distance la plus courte entre les 2 points de contact des roues) 
            * Pour la mesurer rien de mieux que un plexiglas sur lequel on pose le robot pour bien mettre en avant les points de contact !


### Première étape le lancement


### Seconde étape le fonctionnement normal

### Dernière étape l'arrêt
