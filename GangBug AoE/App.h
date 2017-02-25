#ifndef __j1APP_H__
#define __j1APP_H__

#include <iostream>
#include <list>
#include "j1PerfTimer.h"
#include "j1Timer.h"
#include "PugiXml\src\pugixml.hpp"
#include "p2SString.h"
#include "Defs.h"

// Modules
class Module;

class M_Window;
class M_Input;
class M_Render;
class M_Textures;
class M_Audio;
class M_FileSystem;
class M_Map;
class M_PathFinding;
class M_Fonts;
class M_EntityManager;
class M_GUI;


class App
{
public:

	// Constructor
	App(int argc, char* args[]);

	// Destructor
	virtual ~App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	update_status Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;
	float GetDT() const;

	void LoadGame(const char* file);
	void SaveGame(const char* file) const;
	void GetSaveGames(std::list<p2SString>& listToFill) const;

private:

	// Load config file
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	update_status PreUpdate();

	// Call modules on each loop iteration
	update_status DoUpdate();

	// Call modules after each loop iteration
	update_status PostUpdate();

	// Load / Save
	bool LoadGameNow();
	bool SavegameNow() const;

public:

	// Modules
	M_Window*			win = nullptr;
	M_Input*			input = nullptr;
	M_Render*			render = nullptr;
	M_Textures*			tex = nullptr;
	M_Audio*			audio = nullptr;
	M_FileSystem*		fs = nullptr;
	M_Map*				map = nullptr;
	M_PathFinding*		pathfinding = nullptr;
	M_Fonts*			font = nullptr;
	M_EntityManager*	entityManager = nullptr;
	M_GUI*				gui = nullptr;

	bool debug = false;
	bool quit = false;

private:

	std::list<Module*>	modules;
	int					argc;
	char**				args;

	p2SString			title;
	p2SString			organization;

	mutable bool		wantToSave = false;
	bool				wantToLoad = false;
	p2SString			loadGame;
	mutable p2SString	saveGame;

	PerfTimer			ptimer;
	uint64				frameCount = 0;
	Timer				startupTime;
	Timer				frameTime;
	Timer				lastSecFrameTime;
	uint32				lastSecFrameCount = 0;
	uint32				prevLastSecFrameCount = 0;
	float				dt = 0.0f;
	int					cappedMs = -1;
};

extern App* app;

#endif