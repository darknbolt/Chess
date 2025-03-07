package components;
import javax.swing.*;

public class MyFrame extends JFrame {
    private String username;
    public MyFrame(){
        this.setResizable(false);
        this.setLayout(null);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setTitle("Chess");
        this.setContentPane(new UsernameLogin(this));
        this.setSize(1000, 1000);
        this.setVisible(true);
    }
    public void start(String username){
        this.username = username;
        this.setContentPane(new MyPanel());
        this.repaint();
        this.setVisible(true);
    }
}