Itérations
==========

Contenu des différentes itérations du projet.

Itération 1
-----------
date : semaine 5 - 2011

- Cyrille :
    - Implémentation VCO, VCF;
- Julien N. :
    - Implémentation dummy stratégie du VCO et du VCF;
    - Implémentation du Square Wavegenerator;
- Julien RF. :
    - Implémentation du module;
- Maxime :
    - Intégration du framework de test.

Itération 2
-----------
date : semaine 5 - 2011

- Julien RF. et Julien N. :
    - Implémentation du Sequencer;
- Julien N. :
    - WaveGenerator square/saw/sinus/triangle;
    - AudioDeviceProvider;
    - ModuleBufferRecorder;
- Maxime :
    - Début d'implémentation de l'UI.

Itération 3
-----------
date : semaine 6 - 2011

- Julien N. :
    - Test unitaire sur ModuleBufferRecorder et les WaveGenerator.
    - Horloge et module Out.
    - Mettre Init en virtuelle dans module buffer recorder.
- Maxime :
    - Gestion drag'n'drop;
    - Implementation graphique du potard, du sélecteur;
    - Gestion des câbles (création, destruction, etc);
- Julien RF :
    - Gestion héritage "en diamant";
    - PModuleOut ;
    - Ajout d’une property `name` aux Ports ;
- Cyrille :
    - Réglages (potard et selecteur);
    - Intégration réglages dans VCO;
    - VCA;

Roadmap (todo)
---------
- VCA (juste une multiplication)
- VCF
- adsr
- Keyboard virtuel
- Oscillo
- Items graphiques (VCO, VCF, ports, output, cable)

Tweaking
----------
- Optimiser InPort::fetch() (en deux passes).
- Penser à Normaliser le signal de la sortie Out, mais également le BufferRecorder.