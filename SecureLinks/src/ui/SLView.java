package ui;

import javax.swing.JFrame;
import javax.swing.JPanel;
import java.awt.BorderLayout;
import javax.swing.JButton;
import javax.swing.JDialog;

import java.awt.Color;
import java.awt.Component;

import javax.swing.border.LineBorder;

import org.eclipse.swt.widgets.Shell;

import securelinks.Connection;
import securelinks.ConnectionAdapter;
import securelinks.handlers.UIController;

import java.awt.GridLayout;
import java.awt.Window;
import java.util.List;

import javax.swing.JLabel;
import java.awt.Font;
import javax.swing.SwingConstants;
import javax.swing.UIManager;
import javax.swing.BoxLayout;
import javax.swing.GroupLayout;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;
import javax.swing.JTextField;
import javax.swing.JTextArea;

public class SLView extends JDialog {
	
	private static final String TITLE = "Secure Links for IEC 61499";
	private String sysFile;
	private String selectedApp;
	private JPanel mainPanel;
	
	public SLView(String sysFile, String selectedApp, Shell shell) throws NullPointerException {
		
				
		JPanel panelTop = new JPanel();
		panelTop.setBorder(null);
		panelTop.setBackground(UIManager.getColor("Panel.background"));
		getContentPane().add(panelTop, BorderLayout.NORTH);
		panelTop.setLayout(new GridLayout(1, 1, 0, 0));
		
		JPanel panelTopPanel = new JPanel();
		panelTop.add(panelTopPanel);
		
		JLabel lblTitleStr = new JLabel("Inter-Device mapped Connections for Application:");
		panelTopPanel.add(lblTitleStr);
		lblTitleStr.setHorizontalAlignment(SwingConstants.CENTER);
		lblTitleStr.setFont(new Font("Calibri", Font.BOLD, 16));
		
		JLabel lblApplicationName = new JLabel(selectedApp);
		lblApplicationName.setForeground(Color.RED);
		lblApplicationName.setFont(new Font("Calibri", Font.PLAIN, 16));
		panelTopPanel.add(lblApplicationName);
		
		JPanel panelCenter = new JPanel();
		getContentPane().add(panelCenter, BorderLayout.CENTER);
		panelCenter.setLayout(new BoxLayout(panelCenter, BoxLayout.Y_AXIS));

		if(sysFile != null && selectedApp != null) {
			this.sysFile = sysFile;
			this.selectedApp = selectedApp;
			this.setTitle(TITLE);
			this.setSize(600, 400);
			this.setDefaultCloseOperation(DISPOSE_ON_CLOSE);
			if(shell != null)
				this.setLocation(shell.getLocation().x + 200, shell.getLocation().y + 200);
			this.setModalityType(ModalityType.APPLICATION_MODAL);
			this.setModal(true);
		}
		else
			throw new NullPointerException();
		
		addConnectionsFromApplication(panelCenter);
	}

	public void addConnectionsFromApplication(JPanel panelCenter) {
		
		ConnectionAdapter conAdpt =  new ConnectionAdapter();
	    conAdpt.loadSystem(sysFile, selectedApp);
	    
	    List<Connection> conList = conAdpt.getInterDeviceDataConnections();
		
		UIController controller = new UIController();
		controller.addConnectionItemtoVbox(panelCenter, conList);
	}
}
