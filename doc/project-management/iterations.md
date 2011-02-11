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
    - Test unitaire sur ModuleBufferRecorder et les WaveGenerator;
    - Horloge et module Out;
- Maxime :
    - Gestion drag'n'drop;
    - Implementation graphique du potard, du sélecteur;
    - Gestion des câbles (création, destruction, etc);
- Julien RF :
    - Gestion héritage "en diamant";
    - PModuleOut;
    - Ajout d’une property `name` aux Ports;
    - Suppression de `OutPort::swapBuffers()` et *pull-up* de `InPort::m_buffer` et `OutPort::m_buffer` dans `Port`;
- Cyrille :
    - Réglages (potard et selecteur);
    - Intégration réglages dans VCO.

Itération 4
-----------
date :  semaine 6 (mercredi 9 - jeudi 10)

- Julien N. :
    - VCF;
    - Filtres (LP, HP…);
    - FilterFactory;
    - LFO;
- Maxime :
    - Contrôle et Présentation de VCF, VCA et LFO;
    - Adaptation look&feel;
    - Retroaction;
    - Intégration du layout dans les présentations de modules;
- Julien RF :
    - Layout des modules (taille dynamique);
    - Réplication des ports;
    - Intégration du layout dans VCO;
- Cyrille :
    - VCA;
    - ADSR.

Itération 5
-----------
date :  semaine 6 (vendredi 11 - )

- Julien N. :
    - Oscillo;
    - Keyboard virtuel;
- Maxime :
    - PushButton (qui gere press/release) à ajouter aux interfaces (retrigger ADSR);
    - Présentation et contrôle ADSR, WavRecorder, Delay;
    - Refactoring des noms de modules;
- Julien RF. :
    - Refactoring VPort/Port;
- Cyrille :
    - ADSR;
    - Doc.

Itération 6
-----------
date :  semaine 7 (Lundi 14-)

- Julien N. :
    - Mappage clavier virtual/clavier réel.
    - ?
- Maxime :
    - Feedback dimmer, interaction dimmer avec clavier (pour précision).
    - WaveRecorder dans fichier selectionné.
    - On/Off SynthPro.
- Julien RF. :
    - Suppression des ports répliqués;
    - Feedback des ports (MouseHover);
    - Wire plus jolis;
- Cyrille :
    - Delay;
    - Mixer;

Roadmap (todo)
---------
- Oscillo stabilisé;
- Molette Oscillo (zoom Y);
- Symétrie de l'audio engine.
- Fond d'écran (léger et subtil);
- Icones dans Dockbars (et drag'n'drop d'icones);
- Bouton on/off du synthé;
- Entrée MIDI;

Tweaking
----------
- **Refactoring noms et dossiers**;
- Optimisation Filtres (multiplications, ou voir site);
- Optimiser `InPort::fetch()` (en deux passes);
- Penser à Normaliser le signal de la sortie Out, mais également le BufferRecorder.
