package arduinoupdater;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class UpdateWindow extends JFrame {

    JButton next, prev, cancel;
    JPanel panel;

    public UpdateWindow(ActionListener parent)
    {
        super("Arduino Updater");

        Container c = getContentPane();
        c.setLayout( new BorderLayout( 30, 30 ) );

        Box boxes[] = new Box[ 4 ];

        boxes[ 0 ] = Box.createHorizontalBox();
        boxes[ 1 ] = Box.createVerticalBox();
        boxes[ 2 ] = Box.createHorizontalBox();
        boxes[ 3 ] = Box.createVerticalBox();

        boxes[0].add( new JLabel("Welcome to ZAP updater") );

        panel = new JPanel();
        prev = new JButton( "Previous");
        prev.setActionCommand("prev");
        boxes[2].add( Box.createGlue() );
        boxes[2].add( prev );
        prev.setEnabled(false);
        next = new JButton("Next");
        next.setActionCommand("next");
        boxes[2].add( next );
        cancel =new JButton("Cancel");
        cancel.setActionCommand("cancel");
        boxes[2].add( cancel);

        cancel.addActionListener(parent);
        next.addActionListener(parent);
        prev.addActionListener(parent);

        // place panels on frame

        c.add( boxes[ 0 ], BorderLayout.NORTH );
        c.add( boxes[ 1 ], BorderLayout.EAST );
        c.add( boxes[ 2 ], BorderLayout.SOUTH );
        c.add( boxes[ 3 ], BorderLayout.WEST );

        c.add( panel, BorderLayout.CENTER );

        setSize( 600, 200 );
        show();
    }

    void disableAllButtons()
    {
        //cancel.setEnabled(false);
        next.setEnabled(false);
        prev.setEnabled(false);
    }
    void enableAllButtons()
    {
        //cancel.setEnabled(false);
        next.setEnabled(true);
        prev.setEnabled(true);
    }

    public void displayMessage(String s)
    {
        panel.removeAll();
        panel.add(new JLabel(s));
        validate();
        repaint();//panel.show();
    }

};