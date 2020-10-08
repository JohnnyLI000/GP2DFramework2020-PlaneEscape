## Aerial Escape (plane escape)

Genre : Indie Game

Audience : all type

Game play and mechanics : There is a plane you control , you have to make sure it wont crash to the ground , and the plane is similar to WW1 propeller plane style . 
The plane drops naturally by the gravity if you don’t let the power the engine. When you power the engine you have to burn the fuel , if there is no fuel the plane will drop. 
There are also enemies chasing you, you have weapons to shoot them as well but if the plane get shot the plane also drops. 
So, the whole game is about how far you escape or have flown.

Player goal: try the best to survive

Key/core features: easy to play, consists of physics and great timing technique .

User interface design: start and finish button

Unique selling points: it’s very addictive to play.

API: SDL2 , FMOD
Main language: C++
IDE: vs 2017

## Integrate the third-party middleware (FMOD & SDL2) into this project. 
The extracted zip has been committed into the folder with .you should link your project relative to this extracted version of the API.
In Visual Studio 2017, right click on the Framework Project, and choose “Properties”. In the “C/C++” section, choose the “General” options. In the “Additional Include Directories” add an entry for the FMOD include headers.

This will likely be: $(SolutionDir)\API-FMOD\fmodstudioapi20011wininstaller\api\core\inc\
This will allow you to #include "fmod.hpp" in your project’s source code.

In the “Linker” section, choose the “General” options. In the “Additional Library Dependencies” add an entry for the FMOD include headers. 

This will likely be: $(SolutionDir)\API-FMOD\fmodstudioapi20011wininstaller\api\core\lib\x86\

Next, go to the “Linker”, “Input” options. In the “Additional Dependencies” add an entry for the FMOD static library. This is called fmod_vc.lib.

For SDL2 would be "SDL2_ttf.lib" "SDL2.lib" "SDL2main.lib" "SDL2_image.lib"

Now the linker will be able to link to the FMOD & SDL2 middleware when the project is built.

 ## How it looks like :
![Alt text](https://jonnnyportfolioimagebucket.s3-ap-southeast-2.amazonaws.com/Image/ezgif.com-gif-maker+(1).gif "Game")
 
