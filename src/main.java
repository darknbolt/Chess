import javax.swing.*;
import java.awt.*;
import java.net.*;
import components.*;

public class main extends JFrame{
    public static void main(String[] args) {
        new main();
    }

    public main(){
        this.setResizable(false);
        this.setLayout(null);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("Chess");
        this.setContentPane(new MyPanel());
        this.setSize(1000, 1000);
        this.setVisible(true);
    }
}
