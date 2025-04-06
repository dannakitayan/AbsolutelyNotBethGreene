#ifndef ANBG_ENGINE
#define ANBG_ENGINE

//AbsolutelyNotBethGreene Engine is a simple 2D engine for Corpse Party Repeated Call (Recall);
//You may also make your own "Corpse Party" like game;
//I have used AbsolutelyNotBethGreene name, but it isn't mine. The owner is https://x.com/Luna_Lovestruck;
//I did this because I am so grateful to her for being the first person who decided to help me with the game. 
//For her kindness I decided to name the engine after her;
//Thank you Luna :)
//Also thank you ChatGPT for helping me improve my C language skills, you are a great teacher!
// 
//The ANBG Engine programmer is Dannaki "Lain" Kobayashi; 

#ifdef _WIN32
#ifdef ANBG_EXPORTS
#define ANBG_API __declspec(dllexport)
#else
#define ANBG_API __declspec(dllimport)
#endif
#else
#define ANBG_API
#endif

#endif