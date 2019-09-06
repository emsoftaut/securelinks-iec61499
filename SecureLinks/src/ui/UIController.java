package ui;

import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.imageio.ImageIO;
import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.GroupLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JComponent;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.SwingConstants;
import javax.swing.plaf.nimbus.NimbusStyle;

import org.eclipse.swt.widgets.Shell;
import org.eclipse.ui.IWorkbenchWindow;

import javafx.geometry.Bounds;
import javafx.geometry.Insets;
import javafx.scene.control.Label;
import javafx.scene.layout.HBox;
import javafx.scene.layout.TilePane;
import javafx.scene.layout.VBox;
import javafx.scene.shape.Line;
import securelinks.Connection;
import securelinks.ConnectionAdapter;

public class UIController {

	private String slString;
	private static String sysFile;
	private static String selectedApp;
	private static List<Connection> conList;
	private ConnectionAdapter conAdpt;
	
	private static UIController instance;
	
	SLView view;
	
	private UIController() {}
	
	public static UIController getInstance(String sysFilep, String selectedAppp) {
		if(instance == null) {
			instance = new UIController();
		}
		sysFile = sysFilep;
		selectedApp = selectedAppp;
		return instance;
	}

	public List<Connection> getConnectionList() {
		conAdpt =  new ConnectionAdapter();
	    conAdpt.loadSystem(sysFile, selectedApp);
		return conAdpt.getInterDeviceDataConnections();
	}
	
	public void loadSecureLinkGUI(IWorkbenchWindow window) {
		if(sysFile != null && selectedApp != null ) {
			Shell shell = null;
			if(window != null)
				shell = window.getShell();
			view = new SLView(sysFile, selectedApp, shell);
			view.setVisible(true);
		}
	}
	
	public static List<Connection> getUpdatedConnectionListFromUI() {
		return conList;
	}
	
	public static void setUpdatedConnectionListFromUI(List<Connection> conListp) {
		conList = new ArrayList<Connection>(conListp);
	}
	
	public void SaveConnections() {
		List<Connection> conList = getUpdatedConnectionListFromUI();
		conAdpt.UpdateConnections(conList);
	}
	
}
