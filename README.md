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
la cheatsheet git: [github education](https://education.github.com/git-cheat-sheet-education.pdf)

Les tutos pratiques et rapides pour git: [egghead tutorial](https://egghead.io/lessons/misc-practical-git-create-local-repos-with-git-init)

Git est le logiciel qui permet de versionner le projet et Github est la plateforme qui stocke la version du code en ligne qui va servir de référence.

![ici l'image](/pictures/XwVzT.png)  

Pour changer le code il faut :
* cloner le repository (créer un version locale [stockée sur ton ordinateur] reliée à la version en ligne) 
* faire les changements que tu veux
* commit (mettre à jour la version locale du code)
* push (mettre à jour la version github du code)

Si tu veux faire de gros changements, je te conseille de créer une branche au repository sur le github. Cela permet de travailler sur le code, le tester et quand tout marche bien, tu peux le mettre sur le main. Si d'autres personnes veulent effectuer des changements sur le code principal, ils ne seront pas impactés par les tests que tu aura fait.

En général pour bien travailler, la branche main est toujours fonctionnelle et prête à être téléversée sur le robot, une branche dev (pour développement) est là pour stocker le code pas fini et une branche test est là pour tester le code avant de l'approuver et de le passer sur le main. A noter que chaque partie sur laquelle vous travaillez devrait avoir sa branche dev et test. Vous pouvez faire des branches avec des noms contenant des /. Cela permet par exemple des appelations telles que dev/pinces-levier et test/pinces-levier.

### Mention spéciale : Arduino
[Le Guide officiel](https://www.arduino.cc/en/Guide)

[L'extension teensyduino](https://www.pjrc.com/teensy/td_download.html)

Pour encore plus de comfort, je conseille de mettre dans les préférences un éditeur externe, c'est à dire utiliser arduino pour compiler et téléverser le code mais l'éditeur externe pour le modifier (vous voyez où je veux en venir ? Utilisez VScode !) puisque le code est majoritairement composé de fichiers Cpp et hpp et que seuls les fichiers dans le même dossier que le .ino sont lisible par Arduino, vous allez avoir besoin de deux éditeurs (Arduino et Vscode), alors autant tout regrouper dans un seul et garder Arduino pour la compilation et le téléversement. Voici un tuto pour changer les préférences Arduino : [locoduino](https://www.locoduino.org/spip.php?article207)

Si vous voulez, j'ai pas testé mais il y a une nouvelle IDE Arduino, avec autocomplétion et formattage automatique.
Si vous vous sentez l'âme aventureuse voici le lien ! [Arduino Pro IDE](https://www.arduino.cc/pro/arduino-pro-ide)


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
    * Distance de détection des capteurs (C'est la distance à partir de laquelle on estime qu'il faut s'arrêter, attention ce n'est pas en millimètres)
    * la condition pour laquelle on estime qu'il y a collision (la distance que l'on a remplie avant sert à formuler cette condition)

* Des paramètres de la motion base dans le panneau de configuration(1) (pas touche aux paramètres des moteurs !)
    * le diamètre des roues en mm
    * l'entraxe (la distance la plus courte entre les 2 points de contact des roues) 
        * Pour la mesurer rien de mieux que un plexiglas sur lequel on pose le robot pour bien mettre en avant les points de contact !


### Première étape le lancement
Alors ce soir je suis un poil salée alors je vais t'apprendre un super acronyme, c'est RTFM.  
**Read the Fine (Fucking) Manuel** 
Apparament j'étais tellement hyppe sur le robot en 3 ème année que j'ai fait des commentaires toutes les 2 lignes et j'ai reformaté tout le code pour que quand tu lises les commentaires tu comprennes le code qui va avec.  
Je vous invite donc dans la plus grande gentilesse à vous rendre dans le fichier summerbot_main.ino et lire le code XD 

### Seconde étape le fonctionnement normal

### Dernière étape l'arrêt
