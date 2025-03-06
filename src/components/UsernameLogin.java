package components;
import javax.swing.*;

public class UsernameLogin extends JPanel {
    private JLabel usernameLabel;
    private JTextField usernameField;
    public UsernameLogin(){
        this.usernameLabel = new JLabel("Username");
        this.usernameField = new JTextField();

        this.usernameField.setBounds(this.getWidth()/3, this.getHeight()/3, 100, 40);
        this.usernameLabel.setBounds(usernameField.getX(), usernameField.getY()-60, 100, 40);

        this.add(usernameField);
        this.add(usernameLabel);
    }
}