#pragma once
#include <cmath>
#include <vector>

class Gameboard{
public:
    static int oldArr[8][8];
    static int arr[8][8];

    static int whiteKingTerritory[3][3];
    static int blackKingTerritory[3][3];

    static int promotionPieceX;
    static int promotionPieceY;

    static int blackCanAttack[8][8];
    static int whiteCanAttack[8][8];

    static bool leftWhiteRookHasNotMoved;
    static bool rightWhiteRookHasNotMoved;
    static bool whiteKingHasNotMoved;
    static bool leftBlackRookHasNotMoved;
    static bool rightBlackRookHasNotMoved;
    static bool blackKingHasNotMoved;

    static bool whiteIsChecked, blackIsChecked;

    static int playerTurn;
    enum Pieces {None = 0, BPawn = 1, BKnight = 2, BBishop = 3, BRook = 4, BQueen = 5, BKing = 6,
                            WPawn = -1, WKnight = -2, WBishop = -3, WRook = -4, WQueen = -5, WKing = -6};
    static auto legal(int startX, int startY, int endX, int endY) -> bool{
        int piece = arr[startY][startX];

        switch(piece){
            case BPawn:
                return isBlackPawnLegal(startX, startY, endX, endY);

            case WPawn:
                return isWhitePawnLegal(startX, startY, endX, endY);

            case BRook:
            case WRook:
                return (isHorizontalVerticalLegal(startX, startY, endX, endY));

            case BKnight:
            case WKnight:
                return isKnightLegal(startX, startY, endX, endY);

            case BBishop:
            case WBishop:
                return isDiagonalLegal(startX, startY, endX, endY);

            case BQueen:
            case WQueen:
                return (isHorizontalVerticalLegal(startX, startY, endX, endY) || isDiagonalLegal(startX, startY, endX, endY));

            case BKing:
            case WKing:
                return (isKingLegal(startX, startY, endX, endY));
                //analyzeKingTerritory(startX, startY);

            default:
                return false;
        }
    }

    static auto isDiagonalLegal(int startX, int startY, int endX, int endY) -> bool{
        int piece = Gameboard::arr[startY][startX];
        int destination = Gameboard::arr[endY][endX];

        if(abs(startX - endX) != abs(startY - endY)) return false;

        int incrementationV = startY < endY ? 1 : -1;
        int incrementationH = startX < endX ? 1 : -1;

        int x = startX + incrementationH;
        int y = startY + incrementationV;
        while(x != endX && y != endY){
            if(Gameboard::arr[y][x] != Gameboard::None) return false;
            x += incrementationH;
            y += incrementationV;
        }

        if(destination == Gameboard::None) return true;
        else if(piece < Gameboard::None){
            if(destination > Gameboard::None && destination != Gameboard::BKing) return true;
            else return false;
        }
        else if(piece > Gameboard::None){
            if(destination < Gameboard::None && destination != Gameboard::WKing) return true;
            else return false;
        }
        return false;
    }
    static auto isHorizontalVerticalLegal(int startX, int startY, int endX, int endY) -> bool{
        int piece = Gameboard::arr[startY][startX];
        int destination = Gameboard::arr[endY][endX];

        int incrementationV = startY < endY ? 1 : -1;
        int incrementationH = startX < endX ? 1 : -1;

        if(startX == endX){
            int y = startY + incrementationV;
            while (y != endY){
                if(Gameboard::arr[y][startX] != Gameboard::None) return false;
                y += incrementationV;
            }
            if(destination == Gameboard::None) {
                if(Gameboard::arr[startY][startX] == WRook && startY == 7 && startX == 0) leftWhiteRookHasNotMoved = false;
                if(Gameboard::arr[startY][startX] == WRook && startY == 7 && startX == 7) rightWhiteRookHasNotMoved = false;

                if(Gameboard::arr[startY][startX] == BRook && startY == 0 && startX == 0) leftBlackRookHasNotMoved = false;
                if(Gameboard::arr[startY][startX] == BRook && startY == 0 && startX == 7) rightBlackRookHasNotMoved = false;

                return true;
            }
            else if(piece < Gameboard::None) {
                if(destination > Gameboard::None && destination != Gameboard::BKing) {
                    if(Gameboard::arr[startY][startX] == WRook && startY == 7 && startX == 0) leftWhiteRookHasNotMoved = false;
                    if(Gameboard::arr[startY][startX] == WRook && startY == 7 && startX == 7) rightWhiteRookHasNotMoved = false;

                    if(Gameboard::arr[startY][startX] == BRook && startY == 0 && startX == 0) leftBlackRookHasNotMoved = false;
                    if(Gameboard::arr[startY][startX] == BRook && startY == 0 && startX == 7) rightBlackRookHasNotMoved = false;

                    return true;
                }
                else return false;
            }
            else if(piece > Gameboard::None){
                if(destination < Gameboard::None && destination != Gameboard::WKing) {
                    if(Gameboard::arr[startY][startX] == WRook && startY == 7 && startX == 0) leftWhiteRookHasNotMoved = false;
                    if(Gameboard::arr[startY][startX] == WRook && startY == 7 && startX == 7) rightWhiteRookHasNotMoved = false;

                    if(Gameboard::arr[startY][startX] == BRook && startY == 0 && startX == 0) leftBlackRookHasNotMoved = false;
                    if(Gameboard::arr[startY][startX] == BRook && startY == 0 && startX == 7) rightBlackRookHasNotMoved = false;

                    return true;
                }
                else return false;
            }
        }
        else if(startY == endY){
            int x = startX + incrementationH;
            while (x != endX){
                if(Gameboard::arr[startY][x] != Gameboard::None) return false;
                x += incrementationH;
            }
            if(destination == Gameboard::None) {
                if(Gameboard::arr[startY][startX] == WRook && startY == 7 && startX == 0) leftWhiteRookHasNotMoved = false;
                if(Gameboard::arr[startY][startX] == WRook && startY == 7 && startX == 7) rightWhiteRookHasNotMoved = false;

                if(Gameboard::arr[startY][startX] == BRook && startY == 0 && startX == 0) leftBlackRookHasNotMoved = false;
                if(Gameboard::arr[startY][startX] == BRook && startY == 0 && startX == 7) rightBlackRookHasNotMoved = false;

                return true;
            }
            else if(piece < Gameboard::None) {
                if(destination > Gameboard::None && destination != Gameboard::BKing) {
                    if(Gameboard::arr[startY][startX] == WRook && startY == 7 && startX == 0) leftWhiteRookHasNotMoved = false;
                    if(Gameboard::arr[startY][startX] == WRook && startY == 7 && startX == 7) rightWhiteRookHasNotMoved = false;

                    if(Gameboard::arr[startY][startX] == BRook && startY == 0 && startX == 0) leftBlackRookHasNotMoved = false;
                    if(Gameboard::arr[startY][startX] == BRook && startY == 0 && startX == 7) rightBlackRookHasNotMoved = false;

                    return true;
                }
                else return false;
            }
            else if(piece > Gameboard::None){
                if(destination < Gameboard::None && destination != Gameboard::WKing) {
                    if(Gameboard::arr[startY][startX] == WRook && startY == 7 && startX == 0) leftWhiteRookHasNotMoved = false;
                    if(Gameboard::arr[startY][startX] == WRook && startY == 7 && startX == 7) rightWhiteRookHasNotMoved = false;

                    if(Gameboard::arr[startY][startX] == BRook && startY == 0 && startX == 0) leftBlackRookHasNotMoved = false;
                    if(Gameboard::arr[startY][startX] == BRook && startY == 0 && startX == 7) rightBlackRookHasNotMoved = false;

                    return true;
                }
                else return false;
            }
        }
        return false;
    }

    static auto isBlackPawnLegal(int startX, int startY, int endX, int endY) -> bool{
        int destination = Gameboard::arr[endY][endX];

        if(startX == endX && startY == 1 && endY == 3 && Gameboard::arr[2][startX] == Gameboard::None) return true;
        else if(startX == endX && startY + 1 == endY && Gameboard::arr[endY][startX] == Gameboard::None) return true;
        else if(destination < Gameboard::None && destination != Gameboard::WKing && startY + 1 == endY && (startX + 1 == endX || startX - 1 == endX)) return true;
        else if(startY == 4 && Gameboard::oldArr[endY+1][endX] == Gameboard::WPawn && Gameboard::arr[endY+1][endX] == Gameboard::None && Gameboard::arr[endY-1][endX] == Gameboard::WPawn) {
            Gameboard::arr[endY-1][endX] = Gameboard::None;
            return true;
        }
        return false;
    }
    static auto isWhitePawnLegal(int startX, int startY, int endX, int endY) -> bool{
        int destination = Gameboard::arr[endY][endX];

        if(startX == endX && startY == 6 && endY == 4 && Gameboard::arr[5][startX] == Gameboard::None) return true;
        else if(startX == endX && startY - 1 == endY && Gameboard::arr[endY][startX] == Gameboard::None) return true;
        else if(destination > Gameboard::None && destination != Gameboard::BKing && startY - 1 == endY && (startX + 1 == endX || startX - 1 == endX)) return true;
        else if(startY == 3 && Gameboard::oldArr[endY-1][endX] == Gameboard::BPawn && Gameboard::arr[endY-1][endX] == Gameboard::None && Gameboard::arr[endY+1][endX] == Gameboard::BPawn) {
            Gameboard::arr[endY+1][endX] = Gameboard::None;
            return true;
        }
        return false;
    }
    static auto isKnightLegal(int startX, int startY, int endX, int endY) -> bool{
        int piece = Gameboard::arr[startY][startX];
        int destination = Gameboard::arr[endY][endX];

        if(endY > -1 && endY < 8 && endX > -1 && endX < 8){
            if(startY - 2 == endY || startY + 2 == endY){
                if(startX - 1 == endX || startX + 1 == endX) {
                    if(destination == Gameboard::None) return true;
                    else if(piece < Gameboard::None && destination > Gameboard::None && destination != Gameboard::BKing) return true;
                    else if(piece > Gameboard::None && destination < Gameboard::None && destination != Gameboard::WKing) return true;
                    return false;
                }
            }
            else if(startY - 1 == endY || startY +1 == endY){
                if(startX - 2 == endX || startX + 2 == endX){
                    if(destination == Gameboard::None) return true;
                    else if(piece < Gameboard::None && destination > Gameboard::None && destination != Gameboard::BKing) return true;
                    else if(piece > Gameboard::None && destination < Gameboard::None && destination != Gameboard::WKing) return true;
                    return false;
                }
            }
        }
        return false;
    }
    static auto isKingLegal(int startX, int startY, int endX, int endY) -> bool{
        if(startX == endX && abs(startY - endY) == 1) {
            if(Gameboard::arr[startY][startX] == Gameboard::WKing) whiteKingHasNotMoved = false;
            else if(Gameboard::arr[startY][startX] == Gameboard::BKing) blackKingHasNotMoved = false;
            return true;
        }
        else if(startY == endY && abs(startX - endX) == 1) {
            if(Gameboard::arr[startY][startX] == Gameboard::WKing) whiteKingHasNotMoved = false;
            else if(Gameboard::arr[startY][startX] == Gameboard::BKing) blackKingHasNotMoved = false;
            return true;
        }
        else if(abs(startX - endX) == 1 && abs(startY - endY) == 1) {
            if(Gameboard::arr[startY][startX] == Gameboard::WKing) whiteKingHasNotMoved = false;
            else if(Gameboard::arr[startY][startX] == Gameboard::BKing) blackKingHasNotMoved = false;
            return true;
        }
        else if(Gameboard::arr[7][5] == Gameboard::None && Gameboard::arr[7][6] == Gameboard::None && Gameboard::arr[startY][startX] == Gameboard::WKing){
            if(Gameboard::whiteKingHasNotMoved && Gameboard::arr[7][4] == WKing && Gameboard::rightWhiteRookHasNotMoved && Gameboard::arr[7][7] == WRook){
                whiteKingHasNotMoved = false;
                rightWhiteRookHasNotMoved = false;
                Gameboard::arr[7][6] = WKing;
                Gameboard::arr[7][5] = WRook;
                Gameboard::arr[7][4] = None;
                Gameboard::arr[7][7] = None;
                Gameboard::playerTurn *= -1;
                return true;
            }
            return false;
        }
        else if(Gameboard::arr[7][1] == None && Gameboard::arr[7][2] == None && Gameboard::arr[7][3] == None && Gameboard::arr[startY][startX] == Gameboard::WKing){
            if(Gameboard::whiteKingHasNotMoved && Gameboard::arr[7][4] == WKing && Gameboard::leftWhiteRookHasNotMoved && Gameboard::arr[7][0] == WRook){
                whiteKingHasNotMoved = false;
                leftWhiteRookHasNotMoved = false;
                Gameboard::arr[7][0] = None;
                Gameboard::arr[7][2] = WKing;
                Gameboard::arr[7][3] = WRook;
                Gameboard::arr[7][4] = None;
                Gameboard::playerTurn *= -1;
                return true;
            }
            return false;
        }
        else if(Gameboard::arr[0][5] == Gameboard::None && Gameboard::arr[0][6] == Gameboard::None && Gameboard::arr[startY][startX] == Gameboard::BKing){
            if(Gameboard::blackKingHasNotMoved && Gameboard::arr[0][4] == BKing && Gameboard::rightBlackRookHasNotMoved && Gameboard::arr[0][7] == BRook){
                blackKingHasNotMoved = false;
                rightBlackRookHasNotMoved = false;
                Gameboard::arr[0][6] = BKing;
                Gameboard::arr[0][5] = BRook;
                Gameboard::arr[0][4] = None;
                Gameboard::arr[0][7] = None;
                Gameboard::playerTurn *= -1;
                return true;
            }
            return false;
        }
        else if(Gameboard::arr[0][1] == None && Gameboard::arr[0][2] == None && Gameboard::arr[0][3] == None && Gameboard::arr[startY][startX] == Gameboard::BKing){
            if(Gameboard::blackKingHasNotMoved && Gameboard::arr[0][4] == BKing && Gameboard::leftBlackRookHasNotMoved && Gameboard::arr[0][0] == BRook){
                blackKingHasNotMoved = false;
                leftBlackRookHasNotMoved = false;
                Gameboard::arr[0][0] = None;
                Gameboard::arr[0][2] = BKing;
                Gameboard::arr[0][3] = BRook;
                Gameboard::arr[0][4] = None;
                Gameboard::playerTurn *= -1;
                return true;
            }
            return false;
        }
        else return false;
    }

    static auto isOutOfBounds(int x, int y) -> bool{
        return (y > -1 && y < 8 && x > -1 && x < 8);
    }
    static auto kingSurrounding() ->void{

    }
    static auto check() -> void{
        int whiteX = 0, whiteY = 0, blackX, blackY;
        for(auto row = 0, stopper = 0; row < 8 && stopper < 2; ++row){
            for(auto column = 0; column < 8 && stopper < 2; ++column){
                if(Gameboard::arr[row][column] == WKing){
                    whiteY = row;
                    whiteX = column;
                    ++stopper;
                }else if(Gameboard::arr[row][column] == BKing){
                    blackY = row;
                    blackX = column;
                    ++stopper;
                }
            }
        }
        int whiteCounter = 0, blackCounter = 0;
        for(int row = 0; row < 8; ++row){
            for(int column = 0; column < 8; ++column){
                if(legal(column, row, whiteX, whiteY)) Gameboard::whiteIsChecked = true;
                else ++whiteCounter;
                if(legal(column, row, blackX, blackY)) Gameboard::blackIsChecked = true;
                else ++blackCounter;
            }
        }
        if(whiteCounter == 64) whiteIsChecked = false;
        if(blackCounter == 64) blackIsChecked = false;
    }

    static auto clearBoard() -> void{
        for(int i = 0; i < 8; ++i){
            for(int j = 0; j < 8; ++j){
                Gameboard::arr[i][j] = Gameboard::None;
                Gameboard::oldArr[i][j] = Gameboard::None;
            }
        }
    }
    static auto setOldArr() -> void{
        for(int i = 0; i < 8; ++i){
            for(int j = 0; j < 8; ++j){
                Gameboard::oldArr[i][j] = Gameboard::arr[i][j];
            }
        }
    }
};