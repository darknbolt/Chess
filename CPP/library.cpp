#include "Chess.h"
#include "Chess_ChessGUI.h"
#include "Gameboard.h"

//TODO - Check
//TODO - Checkmate
//TODO - IsGameOver
//TODO - Transform Pawn Into Chosen Piece

int Gameboard::oldArr[8][8] ={};
int Gameboard::arr[8][8] = {};

int Gameboard::blackKingTerritory[3][3] = {};
int Gameboard::whiteKingTerritory[3][3] = {};

int Gameboard::whiteCanAttack[8][8] = {};
int Gameboard::blackCanAttack[8][8] = {};

int Gameboard::promotionPieceX = -1;
int Gameboard::promotionPieceY = -1;

bool Gameboard::leftWhiteRookHasNotMoved = false;
bool Gameboard::rightWhiteRookHasNotMoved = false;
bool Gameboard::whiteKingHasNotMoved = false;
bool Gameboard::leftBlackRookHasNotMoved = false;
bool Gameboard::rightBlackRookHasNotMoved = false;
bool Gameboard::blackKingHasNotMoved = false;

bool Gameboard::blackIsChecked = false;
bool Gameboard::whiteIsChecked = false;

int Gameboard::playerTurn = -1;

JNIEXPORT void JNICALL Java_Chess_generateBoard
        (JNIEnv *env, jclass cl) {

    //BLACK
    Gameboard::arr[0][0] = Gameboard::BRook;
    Gameboard::arr[0][1] = Gameboard::BKnight;
    Gameboard::arr[0][2] = Gameboard::BBishop;
    Gameboard::arr[0][3] = Gameboard::BQueen;
    Gameboard::arr[0][4] = Gameboard::BKing;
    Gameboard::arr[0][5] = Gameboard::BBishop;
    Gameboard::arr[0][6] = Gameboard::BKnight;
    Gameboard::arr[0][7] = Gameboard::BRook;
    for (int i = 0; i < 8; ++i) Gameboard::arr[1][i] = Gameboard::BPawn;

    //WHITE
    Gameboard::arr[7][0] = Gameboard::WRook;
    Gameboard::arr[7][1] = Gameboard::WKnight;
    Gameboard::arr[7][2] = Gameboard::WBishop;
    Gameboard::arr[7][3] = Gameboard::WQueen;
    Gameboard::arr[7][4] = Gameboard::WKing;
    Gameboard::arr[7][5] = Gameboard::WBishop;
    Gameboard::arr[7][6] = Gameboard::WKnight;
    Gameboard::arr[7][7] = Gameboard::WRook;
    for(int i = 0; i < 8; ++i) Gameboard::arr[6][i] = Gameboard::WPawn;

    Gameboard::playerTurn = -1;

    Gameboard::leftWhiteRookHasNotMoved = true;
    Gameboard::rightWhiteRookHasNotMoved = true;
    Gameboard::whiteKingHasNotMoved = true;
    Gameboard::leftBlackRookHasNotMoved = true;
    Gameboard::rightBlackRookHasNotMoved = true;
    Gameboard::blackKingHasNotMoved = true;

    Gameboard::blackIsChecked = false;
    Gameboard::whiteIsChecked = false;
}

JNIEXPORT void JNICALL Java_Chess_clearBoard
        (JNIEnv *, jclass){
    Gameboard::clearBoard();
}

JNIEXPORT jobjectArray JNICALL Java_Chess_00024ChessGUI_getBoard
        (JNIEnv *env, jobject){
    jobjectArray objArray = env->NewObjectArray(8, env->FindClass("[I"), nullptr);

    for(auto i = 0; i < 8; ++i){
        jintArray rowArray = env->NewIntArray(8);
        env->SetIntArrayRegion(rowArray, 0, 8, reinterpret_cast<const jint*> (Gameboard::arr[i]));
        env->SetObjectArrayElement(objArray, i, rowArray);
    }

    return objArray;
}

JNIEXPORT jint JNICALL Java_Chess_00024ChessGUI_getTile
        (JNIEnv *, jobject, jint y, jint x){
    return Gameboard::arr[y][x];
}

JNIEXPORT jint JNICALL Java_Chess_getBoardWidth
        (JNIEnv *, jclass){
    return 8;
}

JNIEXPORT jint JNICALL Java_Chess_getBoardHeight
        (JNIEnv *, jclass){
    return 8;
}

JNIEXPORT jboolean JNICALL Java_Chess_isMoveLegal
        (JNIEnv *env, jclass, jint startX, jint startY, jint endX, jint endY){
    jboolean truth = Gameboard::legal(startX, startY, endX, endY);
    return truth;
}

JNIEXPORT void JNICALL Java_Chess_movePiece
        (JNIEnv *env, jclass, jint startX, jint startY, jint endX, jint endY){
    int temp = Gameboard::arr[startY][startX];
    if(temp < 0 && Gameboard::playerTurn < 0 || temp > 0 && Gameboard::playerTurn > 0) {
        Gameboard::setOldArr();
        Gameboard::arr[endY][endX] = Gameboard::arr[startY][startX];
        Gameboard::arr[startY][startX] = Gameboard::None;
        Gameboard::playerTurn *= -1;
    }
}

JNIEXPORT jboolean JNICALL Java_Chess_isTherePromotion
        (JNIEnv *, jclass){
    for(int column = 0; column < 8; ++column){
        if(Gameboard::arr[0][column] == Gameboard::WPawn) {
            Gameboard::promotionPieceX = column;
            Gameboard::promotionPieceY = 0;
            return true;
        }
        else if(Gameboard::arr[7][column] == Gameboard::BPawn) {
            Gameboard::promotionPieceX = column;
            Gameboard::promotionPieceY = 0;
            return true;
        }
    }
    return false;
}

JNIEXPORT void JNICALL Java_Chess_setPromotion
        (JNIEnv *env, jclass obj, jchar key){
    if(Java_Chess_isTherePromotion(env, obj)) {
        char c = static_cast<char> (key);
        if (Gameboard::promotionPieceY == 0) {
            if (c == 'q') Gameboard::arr[Gameboard::promotionPieceY][Gameboard::promotionPieceX] = -5;
            else if (c == 'r') Gameboard::arr[Gameboard::promotionPieceY][Gameboard::promotionPieceX] = -4;
            else if (c == 'b') Gameboard::arr[Gameboard::promotionPieceY][Gameboard::promotionPieceX] = -3;
            else if (c == 'n') Gameboard::arr[Gameboard::promotionPieceY][Gameboard::promotionPieceX] = -2;
        } else if (Gameboard::promotionPieceY == 7) {
            if (c == 'q') Gameboard::arr[Gameboard::promotionPieceY][Gameboard::promotionPieceX] = 5;
            else if (c == 'r') Gameboard::arr[Gameboard::promotionPieceY][Gameboard::promotionPieceX] = 4;
            else if (c == 'b') Gameboard::arr[Gameboard::promotionPieceY][Gameboard::promotionPieceX] = 3;
            else if (c == 'n') Gameboard::arr[Gameboard::promotionPieceY][Gameboard::promotionPieceX] = 2;
        }
        Gameboard::setOldArr();
    }
}

JNIEXPORT jobjectArray JNICALL Java_Chess_getBoardForJNITestPurposes
        (JNIEnv *env, jclass){
    jclass intArray = env->FindClass("[I");
    jobjectArray arr = env->NewObjectArray(8, intArray, nullptr);

    for(int i = 0; i < 8; ++i){
        jintArray row = env->NewIntArray(8);

        env->SetIntArrayRegion(row, 0, 8, reinterpret_cast<const jint *>(Gameboard::arr[i]));
        env->SetObjectArrayElement(arr, i, row);
        env->DeleteLocalRef(row);
    }

    return arr;
}

JNIEXPORT jboolean JNICALL Java_Chess_isThereCheck
        (JNIEnv *, jclass){
    Gameboard::check();
    return (Gameboard::whiteIsChecked || Gameboard::blackIsChecked);
}