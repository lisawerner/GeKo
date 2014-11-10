#pragma once
#include <iostream>

class Camera
{

public:
	Camera();
	Camera(std::string cameraName);
	~Camera();

	bool isActive();
	void setActive();
	void setNotActive();

	std::string getCameraName();

protected:
	std::string m_cameraName;	

	bool m_isActive;
	/* InputMap* m_inputMap

		PilotCamera(){
		InputMap input(fillMap(mapType standard));
		}
	*/

	/* Wenn eine Pilotview Kamera erstellt wird:
		- Eine InputMap extra für die Pilotview Kamera gefüllt
		- der maptype wird auf einen Standard wert gesetzt, wenn der Node noch nicht weiß, wo er sich befindet
	   Der Node weiß in welchen Zustand er sich befindet (im Wasser, an Land, in der Luft):
		- der node aktualisiert seine map mit dem mapType immer, am besten dann, wenn er seinen zustand verändert:
			- Er läuft, aktuelle map mit maptype 2 ist aktiv
			- er geht ins wasser, aktuelle map wird aktualisiert mit maptype 4 (bspw.)
		- aktualisierung wird in der renderloop vorgenommen
	   Jede Kamera hat eine Inputmap und jede Input kennt eine Kamera
		- Ableitungen von Inputhandler für jede Art von Inputmap (Menü,  pilotview, trackball usw.)
	*/
};