package components;
import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

public class UsernameLogin extends JPanel {
    private JLabel usernameLabel;
    private JTextField usernameField;
    public UsernameLogin(MyFrame frame) {
        this.setLayout(null);

        this.usernameLabel = new JLabel("Username");
        this.usernameField = new JTextField();

        this.usernameField.setBounds(450, 450, 100, 40);
        this.usernameLabel.setBounds(usernameField.getX(), usernameField.getY() - 40, 100, 40);

        this.usernameField.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                if (e.getKeyChar() == KeyEvent.VK_ENTER) frame.start(usernameField.getText());
            }
        });
        usernameField.setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createLineBorder(Color.BLACK, 2),
                BorderFactory.createEmptyBorder(5, 10, 5, 10)
        ));

        this.add(usernameField);
        this.add(usernameLabel);
    }
}