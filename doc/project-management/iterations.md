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
date :  semaine 6 (vendredi 11)

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
date :  semaine 7 (Lundi 14 - Mardi 15)

- Julien N. :
    - Mappage clavier virtual/clavier réel;
    - WavLooper;
    - Limiteur audio engine/wavrecorder;
    - Optimiser `InPort::fetch()` (en deux passes);
- Maxime :
    - Feedback dimmer;
    - WavRecorder dans fichier sélectionné, possibilité de lancer/arrêter l'enregistrement;
    - On/Off SynthPro;
    - Wires plus jolis et fond d'écran (léger et subtil, beige…);
    - Action New;
- Julien RF. :
    - Suppression des ports répliqués;
    - Feedback des ports (MouseHover);
    - Suppression des modules;
- Cyrille :
    - Delay;
    - Mixer;

Itération 7
-----------
date :  semaine 7 (Mercredi 16-vendredi 18)

- Julien N. :
    - Oscillo stabilisé;
    - Audio Engine avec bonne fréquence;
- Maxime :
    - Contrôle et présentation de sampler;
    - Icones dans box à gauche (+drag'n'drop icones);
    - Remplacer les PixmapButtonWidget (interaction pas assez PAC), par des PushButton (PAC par excellence);
    - Bouton stabilized dans oscillo;
- Julien RF. :
    - Tweaking de la présentation des dimmers (Hz, dB, %, s…);
    - Tweaking de la présentation des widgets;
- Cyrille :
    - Fixer VCA (multiplier input par somme du dimmer et control), en une passe;
    - Sampler;

Itération 8
-----------
date :  semaine 8 (lundi 21-jeudi 24)

- Julien N. :
    - Modif Audio Output données par Julien RF.

- Julien RF :
    - Bug quand on deconnecte 1ere sortie alors 2e utilisée, lors de destruction du module lié. Doit bouger module pour activer raffraichissement visuel.

- Todo :
    - Doc
    - Slides présentation
    - Demo à préparer.


 Manuel :
- Mettre les Gate en italique, et autoriser le pluriel.