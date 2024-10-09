#pragma once

class Piece {
	//VARIABLES 
protected:
	int x, y, id;
	sf::IntRect box;
	sf::Texture texture;
	sf::Sprite sprite;
	std::pair <int, int> oldPosition = std::pair<int, int>();
	bool side, alive = true;

	//CONSTRUCTOR
public:
	Piece(int x, int y, bool side, int id) : x(x), y(y), side(side), id(id) {
		oldPosition.first = x;
		oldPosition.second = y;

		texture = sf::Texture();
		texture.loadFromFile("..\\..\\..\\graphics\\Error.png");

		box = sf::IntRect(0, 0, 100, 100);

		sprite = sf::Sprite();
		sprite.setPosition(x, y);
		sprite.setTexture(texture);
		sprite.setTextureRect(box);
	}

	//METHODS 
	auto getID() -> int { return id; }
	auto getLivingStatus() -> bool { return this->alive; }
	auto setLivingStatus(bool status = false) -> void { this->alive = status; }

	auto setLocation(int x, int y) -> void {
		this->x = x;
		this->y = y;
		this->sprite.setPosition(this->x, this->y);
	}
	auto getLocation() -> std::pair<int, int> { return std::pair<int, int>(this->x, this->y); }

	auto getSprite() -> sf::Sprite { return this->sprite; }
	virtual auto isMoveLegal(std::pair <int, int> position) -> bool { return false; }
	virtual auto isThereKill(std::vector <Piece*>& vector) -> bool { return false; }

	auto setOldPosition() -> void {
		oldPosition.first = this->x;
		oldPosition.second = this->y;
	}
	auto getOldPosition() -> std::pair <int, int> { return oldPosition; }
};

class Pawn : public Piece {
	//VARIABLES
	bool moved = false;

public:

	//CONSTRUCTOR
	Pawn(int x, int y, bool side, int id) : Piece(x, y, side, id) {
		if (side) this->texture.loadFromFile("..\\..\\..\\graphics\\White\\Pawn.png");
		else this->texture.loadFromFile("..\\..\\..\\graphics\\Black\\Pawn.png");

		sprite.setTexture(texture);
	}

	//METHODS
	auto setLocation(int x, int y) -> void{
		this->x = x;
		this->y = y;
		this->sprite.setPosition(this->x, this->y);
	}
	auto isMoveLegal(std::pair <int, int> position) -> bool override{
		if (side && this->oldPosition.first == position.first && position.second == this->oldPosition.second - 200 && !moved) { this->moved = true;  return true; }
		else if (!side && this->oldPosition.first == position.first && position.second == this->oldPosition.second + 200 && !moved) { this->moved = true;  return true; }
		else if (side && this->oldPosition.first == position.first && position.second == this->oldPosition.second - 100) { this->moved = true;  return true; }
		else if (!side && this->oldPosition.first == position.first && position.second == this->oldPosition.second + 100) { this->moved = true;  return true; }
		else return false;
	}
	auto isThereKill(std::vector <Piece*>& vector) -> bool override{
		for (auto e : vector) {
			std::pair <int, int> tempLocation = (*e).getLocation();
			if (this->side && tempLocation.first == this->oldPosition.first + 100 && tempLocation.second == this->oldPosition.second - 100) {
				(*e).setLivingStatus();
				return true;
			}
			else if (this->side && tempLocation.first == this->oldPosition.first - 100 && tempLocation.second == this->oldPosition.second - 100) {
				(*e).setLivingStatus();
				return true;
			}
			else if (!this->side && tempLocation.first == this->oldPosition.first - 100 && tempLocation.second == this->oldPosition.second + 100) {
				(*e).setLivingStatus();
				return true;
			}
			else if (!this->side && tempLocation.first == this->oldPosition.first + 100 && tempLocation.second == this->oldPosition.second + 100) {
				(*e).setLivingStatus();
				return true;
			}
		}
		return false;
	}
};
class Bishop : public Piece {

public:
	Bishop(int x, int y, bool side, int id) : Piece(x, y, side, id) {
		if (side) this->texture.loadFromFile("..\\..\\..\\graphics\\White\\Bishop.png");
		else this->texture.loadFromFile("..\\..\\..\\graphics\\Black\\Bishop.png");

		sprite.setTexture(this->texture);
	}
};
class Rook : public Piece {
public:
	Rook(int x, int y, bool side, int id) : Piece(x, y, side, id) {
		if (side) this->texture.loadFromFile("..\\..\\..\\graphics\\White\\Rook.png");
		else this->texture.loadFromFile("..\\..\\..\\graphics\\Black\\Rook.png");

		sprite.setTexture(this->texture);
	}
};
class Knight : public Piece{
public:
	Knight(int x, int y, bool side, int id) : Piece(x, y, side, id) {
		if (side) this->texture.loadFromFile("..\\..\\..\\graphics\\White\\Knight.png");
		else this->texture.loadFromFile("..\\..\\..\\graphics\\Black\\Knight.png");

		sprite.setTexture(this->texture);
	}
};
class Queen : public Piece {
public:
	Queen(int x, int y, bool side, int id) : Piece(x, y, side, id) {
		if (side) this->texture.loadFromFile("..\\..\\..\\graphics\\White\\Queen.png");
		else this->texture.loadFromFile("..\\..\\..\\graphics\\Black\\Queen.png");

		sprite.setTexture(this->texture);
	}
};
class King : public Piece {
public:
	King(int x, int y, bool side, int id) : Piece(x, y, side, id) {
		if (side) this->texture.loadFromFile("..\\..\\..\\graphics\\White\\King.png");
		else this->texture.loadFromFile("..\\..\\..\\graphics\\Black\\King.png");

		sprite.setTexture(this->texture);
	}
};