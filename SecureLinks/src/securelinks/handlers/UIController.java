package securelinks.handlers;

import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.util.List;

import javax.swing.GroupLayout;
import javax.swing.JLabel;
import javax.swing.JPanel;

import javafx.geometry.Bounds;
import javafx.geometry.Insets;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import javafx.scene.layout.TilePane;
import javafx.scene.layout.VBox;
import javafx.scene.shape.Line;
import securelinks.Connection;

public class UIController {


	public void addConnectionItemtoVbox(JPanel container, List<Connection> conList) {

		for(int i = 0; i < conList.size(); i++) {
			
			Connection con = conList.get(i);
			
			JLabel labelFBOut = new JLabel();
			labelFBOut.setText(con.outFB + "." + con.outVariable);
			labelFBOut.setFont(new Font("Calibri", Font.BOLD, 16));
			JLabel labelFBIn = new JLabel();
			labelFBIn.setFont(new Font("Calibri", Font.BOLD, 16));
			labelFBIn.setText(con.inFB + "." + con.inVariable);
			JLabel labelArrow = new JLabel("---------------------------------->");
			labelArrow.setFont(new Font("Calibri", Font.BOLD, 16));
			
			JPanel panelCon = new JPanel();
			panelCon.setLayout(new GridBagLayout());
			
			GridBagConstraints c = new GridBagConstraints();
			
			c.fill = GridBagConstraints.HORIZONTAL;
			c.gridx = 0; c.gridy = 0; c.ipadx = 10;
			panelCon.add(labelFBOut, c);
			
			c.fill = GridBagConstraints.HORIZONTAL;
			c.gridx = 1; c.gridy = 0; c.ipadx = 10;
			panelCon.add(labelArrow, c);
			
			c.fill = GridBagConstraints.HORIZONTAL;
			c.gridx = 2; c.gridy = 0; c.ipadx = 10;
			panelCon.add(labelFBIn, c);
			
			container.add(panelCon);
		}
	}
}
