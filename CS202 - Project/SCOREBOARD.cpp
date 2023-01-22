#include "SCOREBOARD.h"
SCOREBOARD::SCOREBOARD() {
	texture.loadFromFile("resource/menuscoreboard.png");
	object.setTexture(texture);
	object.setPosition(0, 0);
	playerName = playTime = vector<Text>(6);
	font.loadFromFile("font/000OneTwoPunchBB-Regular.otf");
	topscore.clear();
	for (int i = 0; i < 6; i++) {
		playerName[i].setFont(font);
		playerName[i].setFillColor(Color::Yellow);
		playTime[i].setFont(font);
		playTime[i].setFillColor(Color::Yellow);
		playerName[i].setPosition(600, 290 + 100 * i);
		playTime[i].setPosition(1050, 290 + 100 * i);
	}
}
SCOREBOARD::~SCOREBOARD() {

}
void SCOREBOARD::add(int time, string name) {
	topscore.push_back({ time, name });
	sort(topscore.begin(), topscore.end());
	while (topscore.size() > 6) topscore.pop_back();
	for (int i = 0; i < topscore.size(); i++) {
		playerName[i].setString(topscore[i].second);
		playTime[i].setString(to_string(topscore[i].first) + "s");
	}
}
void SCOREBOARD::show(RenderWindow* app) {
	app->draw(object);
	for (int i = 0; i < playerName.size(); i++) {
		app->draw(playerName[i]);
		app->draw(playTime[i]);
	}
}
void SCOREBOARD::load() {
	ifstream f("Data/scoreboard.txt");
	int n;
	f >> n;
	for (int i = 0; i < n; i++) {
		int time;
		string name;
		f >> time >> name;
		add(time, name);
	}
	f.close();
}
void SCOREBOARD::save() {
	ofstream f("Data/scoreboard.txt");
	f << topscore.size() << '\n';
	for (auto c : topscore) {
		f << c.first << ' ' << c.second << '\n';
	}
	f.close();
}
void SCOREBOARD::clear() {
	ofstream f("Data/scoreboard.txt");
	f << 0;
	f.close();
	topscore.clear();
	playerName.clear();
	playTime.clear();
}