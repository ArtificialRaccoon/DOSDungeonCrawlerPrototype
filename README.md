# Dungeon Crawler Prototype

![Untitled](https://github.com/ArtificialRaccoon/DOSDungeonCrawlerPrototype/blob/main/screenshot.png)

A fairly basic dungeon crawler engine prototype.  Multiple missing features.  Poorly coded since I almost never use C/C++ anymore.  I hope to peck away at this over time to add more basic functionality.

Currently runs on hardware and DOSBOX without issue (for now).  

Tooling:
- DJGPP (targetting GCC 12.1.0)
- Allegro 4.2.3.1 (Unoffical, see below)
- TBD

### To Do (Near Term)

- Interactable Switches
- Doors
- Level Transitions

### To Do (Later Term)

- Improved Tileset loader:  At the moment it is fairly memory ineffificent.  This could be easily improved, as the basis for this is already in place (simply keep a tile minimized version of the tileset in memory, use the TilEd layout to dynamically build the parts, rather than pre-build them)
- Inventory
- Character Status Screen / Equipment Screen
- Battle System: Aiming for a Wizardry/M&M/Turn-Based combat system

## Environment Setup

Install VSCode, and the [DOS-Dev](https://marketplace.visualstudio.com/items?itemName=badlogicgames.dos-dev) extension.  Clang / intellisense will complain about missing headers, etc.  Disable that if it bothers you.

## 3rd Party Libraries

- [Allegro 4.2.3.1](https://github.com/ArtificialRaccoon/allegro-4.2-xc) - Additionally, some minor changes were made to the bundled Allegro headers so they would compile under C++17.
- [Simpleson](https://github.com/gregjesl/simpleson)

## Art Attribution

- Navigation Icons by [DENZI](http://www3.wind.ne.jp/DENZI/diary/)  (CC-BY-SA)
- Other UI Icons by Bernard Walker, based upon original work by [DENZI](http://www3.wind.ne.jp/DENZI/diary/)  (CC-BY-SA)
- Heart Icon by [ED/EM](https://edslashem.itch.io/rpg-pixel-art-assets-1) ("Free", no license information provided)
- Heath/Sanity Font by [ED/EM](https://edslashem.itch.io/rpg-pixel-art-assets-1) ("Free", no license information provided)
- Brain Icon by Bernard Walker.  (CC0)
- Maze and Character Window Borders by [PIPOSCHPATZ](https://piposchpatz.itch.io/ui-borders-art-deco-pixel-art) (CC-BY-4.0)
- Background Texture by [Jestan](https://opengameart.org/content/pixel-texture-pack) (CC-BY-SA)
- Character Portraits by Corwin ZX (https://corwin-zx.itch.io/pixelart-rpg-character-portraits) CC-BY-SA

## Music Attribution

ACCION.MID - "Acción" by djsaryon
Source: https://opengameart.org/content/battle-midi
Copywrite:  CC-BY-SA

WALTZ.MID - "Waltz of the Ghosts" by Aureolus_Omicron
Source: https://opengameart.org/content/waltz-of-the-ghosts
Copywrite:  CC-BY-SA


The following MIDI files were sourced from "The Ultimate MIDI Pack" (https://opengameart.org/content/ultimate-midi-pack).  All are CC-BY-SA.

WICKED.MID - "Let the Wicked Be No More" by Lippeth
Bandcamp: https://nathanmaxx.bandcamp.com
YouTube: https://www.youtube.com/channel/UCF2k6P_IGQU36aZrtLYsoyQ
Copywrite:  CC-BY-SA

HALLS.MID - "Halls of Wandering Spirits" by Myrgharok
LAVA.MID - "On a Sea of Lava" by Myrgharok
ETERNAL.MID - "On a Sea of Lava" by Myrgharok
No Contact Information
Copywrite:  CC-BY-SA

TROUBLE.MID - "Trouble in Sight" by Bloo
Bandcamp: https://bloowuzhere.bandcamp.com/
Copywrite:  CC-BY-SA

SORROW.MID - "World of No Sorrow" by TrialD
YouTube: https://www.youtube.com/channel/UC5WpeUu5yVRYnKHGmqeyp3g
Twitter: https://twitter.com/triald1
Copywrite:  CC-BY-SA
