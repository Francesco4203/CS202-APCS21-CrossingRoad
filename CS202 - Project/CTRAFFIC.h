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

//Constructor set image for object


class LIGHT {
	int state;//1 red - 2 yellow - 3 green
	int red, yellow, green;//time of a state, 2-3s for yellow
public:
	LIGHT() = delete;//default NOT available
	LIGHT(int mode);// 1 2 3 - easy medium hard
};

class LINE {
	LIGHT light;
	int direction;//1 left --> right; 2 left <-- right
public:
	LINE() = delete;//default NOT available
	LINE(int mode);// 1 2 3 - easy medium hard
};