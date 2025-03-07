package components;
import javax.swing.*;
import java.awt.*;

public class MyButton extends JButton {
    public MyButton(String text){
        this.setText(text);
        this.setBorder(BorderFactory.createCompoundBorder(
                BorderFactory.createLineBorder(Color.BLACK, 2),
                BorderFactory.createEmptyBorder(5, 10, 5, 10)
        ));
    }
}
