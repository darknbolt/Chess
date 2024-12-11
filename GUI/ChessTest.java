import static org.junit.jupiter.api.Assertions.*;

class ChessTest {
    static{
        System.loadLibrary("libChess_Library");
    }
    @org.junit.jupiter.api.Test
    void generateBoard() {
        Chess.clearBoard();
        Chess.generateBoard();
        int[][] expectedArray = { {4, 2, 3, 5, 6, 3, 2, 4},
                                  {1, 1, 1, 1, 1, 1, 1, 1},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0},
                                  {-1, -1, -1, -1, -1, -1, -1, -1},
                                  {-4, -2, -3, -5, -6, -3, -2, -4}};

        assertArrayEquals(expectedArray, Chess.getBoardForJNITestPurposes());
    }

    @org.junit.jupiter.api.Test
    void isMoveLegal() {
        Chess.clearBoard();
        Chess.generateBoard();
        assertAll(

                ()->assertEquals(true, Chess.isMoveLegal(6, 7, 5, 5)),
                ()->assertEquals(false, Chess.isMoveLegal(3, 1, 3, 5))
        );
    }

    @org.junit.jupiter.api.Test
    void movePiece() {
        Chess.clearBoard();
        Chess.generateBoard();
        if(Chess.isMoveLegal(4, 6, 4, 4)) Chess.movePiece(4, 6, 4, 4);
        if(Chess.isMoveLegal(6, 0, 5, 2)) Chess.movePiece(6, 0, 5, 2);
        if(Chess.isMoveLegal(4, 4, 4, 3)) Chess.movePiece(4, 4, 4, 3);
        if(Chess.isMoveLegal(3, 1, 3, 3)) Chess.movePiece(3, 1, 3, 3);
        if(Chess.isMoveLegal(4, 3, 3, 2)) Chess.movePiece(4, 3, 3, 2);
        if(Chess.isMoveLegal(4, 1, 3, 2)) Chess.movePiece(4, 1, 3, 2);
        int[][] expectedArray = { {4, 2, 3, 5, 6, 3, 0, 4},
                {1, 1, 1, 0, 0, 1, 1, 1},
                {0, 0, 0, 1, 0, 2, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0},
                {0, 0, 0, 0, 0, 0, 0, 0},
                {-1, -1, -1, -1, 0, -1, -1, -1},
                {-4, -2, -3, -5, -6, -3, -2, -4}};
        assertArrayEquals(expectedArray, Chess.getBoardForJNITestPurposes());
    }
}