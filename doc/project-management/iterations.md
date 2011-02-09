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
date : semaine 6 (7, 8 Fevrier) - 2011

- Julien N. :
    - Test unitaire sur ModuleBufferRecorder et les WaveGenerator.
    - Horloge et module Out.
- Maxime :
    - Gestion drag'n'drop;
    - Implementation graphique du potard, du sélecteur;
    - Gestion des câbles (création, destruction, etc);
- Julien RF :
    - Gestion héritage "en diamant";
    - PModuleOut ;
    - Ajout d’une property `name` aux Ports ;
    - Suppression de `OutPort::swapBuffers()` et *pull-up* de `InPort::m_buffer` et `OutPort::m_buffer` dans `Port`.
- Cyrille :
    - Réglages (potard et selecteur);
    - Intégration réglages dans VCO;

Itération 4
-----------
date :  semaine 6 (mercredi 9 - vendredi 11)

- Julien N. :
    - VCF, FilterFactory, Filtres

- Maxime :
    - C et P de VCF
    - C et P de VCA

- Julien RF :
    - Layout des modules (taille dynamique)
    - Intégration des Layout.
    - Adaptation look&feel.

- Cyrille :
    - VCA
    - ADSR

Roadmap (todo)
---------
- Retroaction.
- VCF
- adsr
- Keyboard virtuel
- Oscillo
- Items graphiques (VCO, VCF, ports, output, cable)

Tweaking
----------
- Optimiser InPort::fetch() (en deux passes).
- Penser à Normaliser le signal de la sortie Out, mais également le BufferRecorder.