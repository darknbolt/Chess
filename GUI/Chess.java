import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Chess extends JFrame {
    public static void main(String[] args) {
        Chess chess = new Chess();
        ChessGUI panel = chess.getPanel();
        panel.setFrame(chess);

        JLabel one = new JLabel("1");
        one.setBounds(10, 70, 20, 20);
        JLabel two = new JLabel("2");
        two.setBounds(10, 120, 20, 20);
        JLabel three = new JLabel("3");
        three.setBounds(10, 170, 20, 20);
        JLabel four = new JLabel("4");
        four.setBounds(10, 220, 20, 20);
        JLabel five = new JLabel("5");
        five.setBounds(10, 270, 20, 20);
        JLabel six = new JLabel("6");
        six.setBounds(10, 320, 20, 20);
        JLabel seven = new JLabel("7");
        seven.setBounds(10, 370, 20, 20);
        JLabel eight = new JLabel("8");
        eight.setBounds(10, 420, 20, 20);

        JLabel a = new JLabel("A");
        a.setBounds(50, 470, 20, 20);
        JLabel b = new JLabel("B");
        b.setBounds(100, 470, 20, 20);
        JLabel c = new JLabel("C");
        c.setBounds(150, 470, 20, 20);
        JLabel d = new JLabel("D");
        d.setBounds(200, 470, 20, 20);
        JLabel e = new JLabel("E");
        e.setBounds(250, 470, 20, 20);
        JLabel f = new JLabel("F");
        f.setBounds(300, 470, 20, 20);
        JLabel g = new JLabel("G");
        g.setBounds(350, 470, 20, 20);
        JLabel h = new JLabel("H");
        h.setBounds(400, 470, 20, 20);

        chess.add(a);
        chess.add(b);
        chess.add(c);
        chess.add(d);
        chess.add(e);
        chess.add(f);
        chess.add(g);
        chess.add(h);

        chess.add(one);
        chess.add(two);
        chess.add(three);
        chess.add(four);
        chess.add(five);
        chess.add(six);
        chess.add(seven);
        chess.add(eight);

        JButton button = new JButton("Play");
        button.setBounds(550, 250, 60, 60);
        button.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                clearBoard();
                chess.repaint();
                generateBoard();
                chess.repaint();
            }
        });

        chess.add(button);
        chess.setVisible(true);
    }

    static{
        System.loadLibrary("libChess_Library");
    }
    private ChessGUI panel;
    public Chess(){
        super();

        this.setSize(650,550);
        this.setResizable(false);
        this.setTitle("Chess");
        this.setLayout(null);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        panel = new ChessGUI();
        this.setContentPane(panel);
    }
    static class ChessGUI extends JPanel{
        private Chess frame;
        private Color green, brown;
        private int tileLengthInPixels, yPointDrawnFrom, xPointDrawnFrom;
        public ChessGUI(){
            super();

            tileLengthInPixels = 50;
            yPointDrawnFrom = 60;
            xPointDrawnFrom = 30;

            green = new Color(193, 225, 193);
            brown = new Color(204, 183, 156);

            setLayout(null);
            this.addMouseListener(new MouseAdapter() {
                int startX, startY, endX, endY;
                @Override
                public void mousePressed(MouseEvent e) {
                    super.mousePressed(e);
                    startX = e.getX();
                    startY = e.getY();
                }

                @Override
                public void mouseReleased(MouseEvent e) {
                    super.mouseReleased(e);
                    endX = e.getX();
                    endY = e.getY();
                    System.out.println("Column: " + getColumn(endX) + " || Row: " + getRow(endY));
                    int startColumn = getColumn(startX), startRow = getRow(startY), endColumn = getColumn(endX), endRow = getRow(endY);
                    if(isMoveLegal(startColumn, startRow, endColumn, endRow)) {
                        movePiece(startColumn, startRow, endColumn, endRow);
                        frame.repaint();
                        if(isThereCheck()) System.out.println("There is a check");
                    }
                    if(isTherePromotion()) {
                        System.out.println("Promotion check works");
                    }
                }
            });

        }

        @Override
        public void paintComponent(Graphics g) {
            super.paintComponents(g);
            for(int row = yPointDrawnFrom, a = 0; row < yPointDrawnFrom + (tileLengthInPixels * getBoardHeight()); row += tileLengthInPixels){
                for(int column = xPointDrawnFrom; column < xPointDrawnFrom + (tileLengthInPixels * getBoardWidth()); column += tileLengthInPixels, ++a){
                    if(a % 2 != 0) {
                        g.setColor(this.brown);
                        g.fillRect(column, row, tileLengthInPixels, tileLengthInPixels);
                        g.drawImage(new ImageIcon("Graphics\\" + getTile(getRow(row + tileLengthInPixels/2), getColumn(column + tileLengthInPixels/2)) + ".png").getImage(), column, row, null);
                    }
                    else {
                        g.setColor(this.green);
                        g.fillRect(column, row, tileLengthInPixels, tileLengthInPixels);
                        g.drawImage(new ImageIcon("Graphics\\" + getTile(getRow(row + tileLengthInPixels/2), getColumn(column + tileLengthInPixels/2)) + ".png").getImage(), column, row, null);
                    }
                }
                ++a;
            }
        }
        private int getRow(int y){
            int sY = 0;
            for(int i = yPointDrawnFrom, a = 0, stopper = 0; i < yPointDrawnFrom + (tileLengthInPixels * getBoardHeight()) && stopper == 0; i += tileLengthInPixels){
                if(i < y && y < i + tileLengthInPixels){
                    sY = a;
                    ++stopper;
                }
                else ++a;
            }
            return sY;
        }
        private int getColumn(int x){
            int sX = 0;
            for(int i = xPointDrawnFrom, a = 0, stopper = 0; i < xPointDrawnFrom + (tileLengthInPixels * getBoardWidth()) && stopper == 0; i += tileLengthInPixels){
                if(i < x && x < i + tileLengthInPixels) {
                    sX = a;
                    ++stopper;
                }
                else ++a;
            }
            return sX;
        }
        public native int getTile(int y, int x);
        public void setFrame(Chess frame) {this.frame = frame;}
    }
    public ChessGUI getPanel() { return this.panel; }
    public static native void generateBoard();
    public static native void clearBoard();
    public static native boolean isMoveLegal(int startX, int startY, int endX, int endY);
    public static native void movePiece(int startX, int startY, int endX, int endY);
    public static native int getBoardWidth();
    public static native int getBoardHeight();
    public static native boolean isTherePromotion();
    public static native void setPromotion(char promotion);
    public static native boolean isThereCheck();
    public static native int[][] getBoardForJNITestPurposes();
}