#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
#include "CANIMAL.h"
#include "CPEOPLE.h"
#include "CVEHICLE.h"
#include "CGAME.h"
#include "CTRAFFIC.h"
#include "CENEMY.h"

using namespace std;
using namespace sf;
CGAME::CGAME() { //Chuẩn bị dữ liệu cho tất cả các đối tượng

}
void CGAME::drawGame() { //Thực hiện vẽ trò chơi ra màn hình sau khi có dữ liệu

}
CGAME::~CGAME() { // Hủy tài nguyên đã cấp phát

}
CPEOPLE CGAME::getPeople() {//Lấy thông tin người

}
CVEHICLE* CGAME::getVehicle() {//Lấy danh sách các xe

}
CANIMAL* CGAME::getAnimal() { //Lấy danh sách các thú

}
void CGAME::resetGame() { // Thực hiện thiết lập lại toàn bộ dữ liệu như lúc đầu

}
void CGAME::exitGame(HANDLE) { // Thực hiện thoát Thread

}
void CGAME::startGame() { // Thực hiện bắt đầu vào trò chơi

}
void CGAME::loadGame(istream) { // Thực hiện tải lại trò chơi đã lưu

}
void CGAME::saveGame(istream) { // Thực hiện lưu lại dữ liệu trò chơi

}
void CGAME::pauseGame(HANDLE) { // Tạm dừng Thread

}
void CGAME::resumeGame(HANDLE) { //Quay lai Thread

}
void CGAME::updatePosPeople(char) { //Thực hiện điều khiển di chuyển của CPEOPLE

}
void CGAME::updatePosVehicle() { //Thực hiện cho CTRUCK & CCAR di chuyển

}
void CGAME::updatePosAnimal() {//Thực hiện cho CDINAUSOR & CBIRD di chuyển

}