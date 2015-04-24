Gestion des communication inter-processeur
==========================================


Ce dépot contient tout le code en rapport avec les protocoles de communication.
Pour l'instant, seul l'uart est supporté, mais il pourrait tout à fait être
possible d'ajouter d'autre backend par la suite (bus spi, …)

--------------------------------------------------------------------------------

PROTOCOLE HAUT NIVEAU :

Note :
    Il est conseillé d'utiliser le protocole texte, car celui-ci est plus
    simple à debogger qu'un protocole binaire.

* texte : cf description dans text_reception.h
    * text_reception.h : API de reception
    * text_reception.c : implementation

* binaire : cf description dans reception_binaire.h
    * reception_binaire.h : API pour l'emmission
    * emission_binaire.h  : API pour la reception
    * reception_binaire.c : implementation
    * emission_binaire.c  : implementation
    * unit_test_binaire.c : test automatique

--------------------------------------------------------------------------------

PRIMITIVES BAS NIVEAU :

Note :
    les projets externe à ce dépôt ne doivent pas dépendre de ces primitives
    Tout ce qui est dépendant du hardware doit se trouver dans ces fichiers.

* uart
    * uart_hardware.h : API
    * uart_hardware_pc.c : implementation minimaliste pour pc

TO DO :
    * fusionner uart.h et uart_hardware.h
    * renommer uart.c en uart_hardware_pic.c + faire les adaptation necessaire
