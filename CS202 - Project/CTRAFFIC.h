#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include "CANIMAL.h"
#include "CPEOPLE.h"
#include "CVEHICLE.h"
#include "CGAME.h"
#include "CTRAFFIC.h"
using namespace std;
using namespace sf;
class LIGHT {
	int state;//0 red - 1 yellow - 2 green
public:
	LIGHT();

};
class LINE {
	LIGHT light;
public:
	LINE();

};