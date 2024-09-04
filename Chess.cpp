#include <SFML/Window.hpp>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Pieces.hpp"
#include <vector>

auto getProperCoordinate(int x, int y) -> std::pair <int, int>;

auto main() -> int {
	auto window = sf::RenderWindow(sf::VideoMode(1000, 1000), "Chess", sf::Style::Close, sf::ContextSettings(0, 0, 8));

	auto blackPawn1 = Pawn(20, 120, false, 1);
	auto blackPawn2 = Pawn(120, 120, false, 2);
	auto blackPawn3 = Pawn(220, 120, false, 3);
	auto blackPawn4 = Pawn(320, 120, false, 4);
	auto blackPawn5 = Pawn(420, 120, false, 5);
	auto blackPawn6 = Pawn(520, 120, false, 6);
	auto blackPawn7 = Pawn(620, 120, false, 7);
	auto blackPawn8 = Pawn(720, 120, false, 8);

	auto blackRookLeft = Rook(20, 20, false, 9);
	auto blackKnightLeft = Knight(120, 20, false, 10);
	auto blackBishopLeft = Bishop(220, 20, false, 11);
	auto blackQueen = Queen(320, 20, false, 12);
	auto blackKing = King(420, 20, false, 13);
	auto blackBishopRight = Bishop(520, 20, false, 14);
	auto blackKnightRight = Knight(620, 20, false, 15);
	auto blackRookRight = Rook(720, 20, false, 16);

	auto whitePawn1 = Pawn(20, 620, true, 17);
	auto whitePawn2 = Pawn(120, 620, true, 18);
	auto whitePawn3 = Pawn(220, 620, true, 19);
	auto whitePawn4 = Pawn(320, 620, true, 20);
	auto whitePawn5 = Pawn(420, 620, true, 21);
	auto whitePawn6 = Pawn(520, 620, true, 22);
	auto whitePawn7 = Pawn(620, 620, true, 23);
	auto whitePawn8 = Pawn(720, 620, true, 24);

	auto whiteRookLeft = Rook(20, 720, true, 25);
	auto whiteKnightLeft = Knight(120, 720, true, 26);
	auto whiteBishopLeft = Bishop(220, 720, true, 27);
	auto whiteQueen = Queen(320, 720, true, 28);
	auto whiteKing = King(420, 720, true, 29);
	auto whiteBishopRight = Bishop(520, 720, true, 30);
	auto whiteKnightRight = Knight(620, 720, true, 31);
	auto whiteRookRight = Rook(720, 720, true, 32);

	//GRABBING MECHANISM
	auto vec = std::vector <Piece*>();

	vec.push_back(&blackPawn1);
	vec.push_back(&blackPawn2);
	vec.push_back(&blackPawn3);
	vec.push_back(&blackPawn4);
	vec.push_back(&blackPawn5);
	vec.push_back(&blackPawn6);
	vec.push_back(&blackPawn7);
	vec.push_back(&blackPawn8);

	vec.push_back(&blackRookLeft);
	vec.push_back(&blackKnightLeft);
	vec.push_back(&blackBishopLeft);
	vec.push_back(&blackQueen);
	vec.push_back(&blackKing);
	vec.push_back(&blackBishopRight);
	vec.push_back(&blackKnightRight);
	vec.push_back(&blackRookRight);

	vec.push_back(&whitePawn1);
	vec.push_back(&whitePawn2);
	vec.push_back(&whitePawn3);
	vec.push_back(&whitePawn4);
	vec.push_back(&whitePawn5);
	vec.push_back(&whitePawn6);
	vec.push_back(&whitePawn7);
	vec.push_back(&whitePawn8);
	
	vec.push_back(&whiteRookLeft);
	vec.push_back(&whiteKnightLeft);
	vec.push_back(&whiteBishopLeft);
	vec.push_back(&whiteQueen);
	vec.push_back(&whiteKing);
	vec.push_back(&whiteBishopRight);
	vec.push_back(&whiteKnightRight);
	vec.push_back(&whiteRookRight);


	bool grabbed = false;
	int currentID = 0;

	while (window.isOpen()) {
		for (auto event = sf::Event(); window.pollEvent(event);) {
			if (event.type == sf::Event::Closed) window.close();
			//CHOOSING PIECE
			if (event.type == sf::Event::MouseButtonPressed){
				if (event.mouseButton.button == sf::Mouse::Left) {
					auto clicked = sf::Mouse::getPosition(window);
					int counter = 0;
					for (auto e = vec.begin(); e != vec.end() && counter == 0; ++e) if ((*e)->getSprite().getGlobalBounds().contains(sf::Vector2f(clicked.x, clicked.y))) {
						currentID = (*e)->getID();
						grabbed = true;
						++counter;
						(*e)->setOldPosition();
					}
				}
			}

			//MOVING PIECE
			if (event.type == sf::Event::MouseMoved && grabbed){
				int counter = 0;
				auto moved = sf::Mouse::getPosition(window);
				for (auto e = vec.begin(); e != vec.end() && counter == 0; ++e) if ((*e)->getID() == currentID) {
					(*e)->setLocation(moved.x - 50, moved.y - 50);
					++counter;
				}
			}

			//PLACING PIECE
			if (event.type == sf::Event::MouseButtonReleased){
				if (grabbed && currentID != 0) {
					auto released = sf::Mouse::getPosition(window);
					auto position = getProperCoordinate(released.x, released.y);
					int counter = 0;
					for (auto e = vec.begin(); e != vec.end() && counter == 0; ++e) if ((*e)->getID() == currentID) {

						if ((*e)->isMoveLegal(position)) {
							(*e)->setLocation(position.first, position.second);
							++counter;
							currentID = 0;
							grabbed = false;
						}
						else {
							auto temp = (*e)->getOldPosition();
							(*e)->setLocation(temp.first, temp.second);
							++counter;
							currentID = 0;
							grabbed = false;
						}
					}
				}
			}
		}

		
		window.clear(sf::Color(175, 75, 0, 255));

		//Grid Drawing 
		for (int i = 20, a = 0; i < 820; i += 100, ++a) {
			for (int h = 20; h < 820; h += 100, ++a) {
				sf::RectangleShape temp = sf::RectangleShape(sf::Vector2f(100, 100));
				temp.setPosition(h, i);
				if (a % 2 == 0) { temp.setFillColor(sf::Color(223, 223, 190, 255)); }
				else { temp.setFillColor(sf::Color(150, 75, 0, 255)); }
				window.draw(temp);
			}			
		}
		
		//Piece Drawing
		for (auto e : vec) window.draw(e->getSprite());

		window.display();
	}
}

auto getProperCoordinate(int x, int y) -> std::pair <int, int> {
	// 20 120 220 320 420 520 620 720
	auto pair = std::pair <int, int>();
	if (x < 420) {
		if (x < 220) {
			if (x < 120) pair.first = 20;
			else pair.first = 120;
		}
		else if (x < 320) pair.first = 220;
		else pair.first = 320;
	}
	else if (x < 620) {
		if (x < 520) pair.first = 420;
		else pair.first = 520;
	}
	else if (x < 720) pair.first = 620;
	else pair.first = 720;
		
	if (y < 420) {
		if (y < 220) {
			if (y < 120) pair.second = 20;
			else pair.second = 120;
		}
		else if (y < 320) pair.second = 220;
		else pair.second = 320;
	}
	else if (y < 620) {
		if (y < 520) pair.second = 420;
		else pair.second = 520;
	}
	else if (y < 720) pair.second= 620;
	else pair.second = 720;

	return pair;
}