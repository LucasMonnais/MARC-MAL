RunRoverProject par Lucas MONNAIS, Antonin CROQUETTE et Maël BROSSET

Lien Github : https://github.com/LucasMonnais/MARC-MAL

Le dossier contient :
      - Un fichier README.txt (vous êtes en train de le lire)
      - un fichier main.c qui contient la fonction principale
      - loc.c avec son homologue .h qui contient les fonctions qui calculent la localisation du robot au fur et à mesure de ses actions
      - map.c avec son homologue .h qui s'occupe de générer la map, avec le coût de chaque case ainsi que le type de sol
      - moves.c avec son homologue .h qui contient les fonctions qui gèrent les mouvements du robot
      - queue.c avec son homologue .h qui contient les fonctions sur les listes
      - stack.c avec son homologue .h qui contient les fonctions sur les piles
      - tree.c avec son homologue .h qui contient toutes les fonctions qui gèrent l'arbre de possibilités et de déplacements


Le but du projet est de ramener un robot nommé MARC à sa base. Pour cela il aura le choix d'effectuer 5 mouvements parmi les 9 possibilités qui lui seront données.
Chaque case qu'il devra traverser a un coût propre et un type de sol différent cependant MARC devra faire attention à ne pas sortir de la map et éviter les crevasses
qui pourraient rendre son retour impossible. Alors pour être sûr de rentrer soigneusement à sa base MARC devra à partir des mouvements donnés calculer le meilleur trajet
(le plus court et le moins coûteux) 
