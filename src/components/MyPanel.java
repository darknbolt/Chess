package components;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MyPanel extends JPanel {
    private MyButton connect, host;
    public MyPanel(){
        this.setLayout(null);

        this.connect = new MyButton("Connect");
        this.host = new MyButton("Host");

        this.connect.setBounds(450, 450, 100, 40);
        this.host.setBounds(450, 510, 100, 40);

        this.connect.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {

            }
        });
        this.host.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                
            }
        });

        this.add(connect);
        this.add(host);
        this.setVisible(true);
    }
}