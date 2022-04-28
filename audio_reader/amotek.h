#pragma once
#include <string>
#include <Windows.h>
/* AMOTEK typedefs */
/* Define GameMaker Booleans */
#define gmtrue 1.0;
#define gmfalse 0.0;

/* Define GameMaker datatypes*/
typedef double gmint;               // Integer for GM
typedef const char* stringToDLL;    // String passed GM --> DLL
typedef char* stringFromDLL;        // String passed DLL -- > GM
typedef double gmbool;              // Datatype for GM Boolean
// device types
#define AMO_DT_ALL 1
#define AMO_DT_MONO 2
#define AMO_DT_PERKEY_RGB 3
#define AMO_DT_DEVICETYPE_RGB 4

using namespace std; // Fight me

// amotek-core bindings: Typedefs
typedef gmbool(*pInitAmoTek)(string name); // Init 
typedef gmbool(*pAmoTekSetLights)(gmint red, gmint green, gmint blue); // set lights
typedef gmbool(*pAmoTekSetTargetDevice)(gmint devicetype); // Set target device
typedef gmbool(*pAmoTekShutdown)(); // Shutdown

HMODULE hMod = LoadLibrary(TEXT("./lib/amotekcore.dll")); // Load the DLL

// Allocate functions
pInitAmoTek initAmoTek = (pInitAmoTek)GetProcAddress(hMod, "initAmoTek");
pAmoTekSetLights AmoTekSetLights = (pAmoTekSetLights)GetProcAddress(hMod, "AmoTekSetLights");
pAmoTekSetTargetDevice AmoTekSetTargetDevice = (pAmoTekSetTargetDevice)GetProcAddress(hMod, "AmoTekSetTargetDevice");
pAmoTekShutdown AmoTekShutdown = (pAmoTekShutdown)GetProcAddress(hMod, "AmoTekShutdown");
