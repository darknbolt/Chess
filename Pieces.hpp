#pragma once

struct Piece {
protected:
	int x, y, id;
	sf::IntRect box;
	sf::Texture texture;
	sf::Sprite sprite;
	std::pair <int, int> oldPosition = std::pair<int, int>();
	bool side, alive = true;
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
	auto operator*()  {

	}

	auto getID() -> int { return id; }
	auto setLocation(int x, int y) -> void {
		this->x = x;
		this->y = y;
		this->sprite.setPosition(this->x, this->y);
	}
	auto getLocation() -> std::pair<int, int> { return std::pair<int, int>(this->x, this->y); }
	auto getSprite() -> sf::Sprite { return this->sprite; }
	virtual auto isMoveLegal(std::pair <int, int> position) -> bool { return true; }
	auto setOldPosition() -> void {
		oldPosition.first = this->x;
		oldPosition.second = this->y;
	}
	auto getOldPosition() -> std::pair <int, int> { return oldPosition; }
};
struct Pawn : Piece {
private:
	bool moved = false;
public:
	Pawn(int x, int y, bool side, int id) : Piece(x, y, side, id) {
		if (side) this->texture.loadFromFile("..\\..\\..\\graphics\\White\\Pawn.png");
		else this->texture.loadFromFile("..\\..\\..\\graphics\\Black\\Pawn.png");

		sprite.setTexture(texture);
	}

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
};
struct Bishop : Piece {
public:
	Bishop(int x, int y, bool side, int id) : Piece(x, y, side, id) {
		if (side) this->texture.loadFromFile("..\\..\\..\\graphics\\White\\Bishop.png");
		else this->texture.loadFromFile("..\\..\\..\\graphics\\Black\\Bishop.png");

		sprite.setTexture(this->texture);
	}
};
struct Rook : Piece {
public:
	Rook(int x, int y, bool side, int id) : Piece(x, y, side, id) {
		if (side) this->texture.loadFromFile("..\\..\\..\\graphics\\White\\Rook.png");
		else this->texture.loadFromFile("..\\..\\..\\graphics\\Black\\Rook.png");

		sprite.setTexture(this->texture);
	}
};
struct Knight : Piece{
public:
	Knight(int x, int y, bool side, int id) : Piece(x, y, side, id) {
		if (side) this->texture.loadFromFile("..\\..\\..\\graphics\\White\\Knight.png");
		else this->texture.loadFromFile("..\\..\\..\\graphics\\Black\\Knight.png");

		sprite.setTexture(this->texture);
	}
};
struct Queen : Piece {
public:
	Queen(int x, int y, bool side, int id) : Piece(x, y, side, id) {
		if (side) this->texture.loadFromFile("..\\..\\..\\graphics\\White\\Queen.png");
		else this->texture.loadFromFile("..\\..\\..\\graphics\\Black\\Queen.png");

		sprite.setTexture(this->texture);
	}
};
struct King : Piece {
public:
	King(int x, int y, bool side, int id) : Piece(x, y, side, id) {
		if (side) this->texture.loadFromFile("..\\..\\..\\graphics\\White\\King.png");
		else this->texture.loadFromFile("..\\..\\..\\graphics\\Black\\King.png");

		sprite.setTexture(this->texture);
	}
};