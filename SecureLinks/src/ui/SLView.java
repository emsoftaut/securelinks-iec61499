package ui;

import javax.swing.JPanel;
import java.awt.BorderLayout;
import javax.swing.JDialog;

import java.awt.Color;
import java.awt.Dimension;

import org.eclipse.core.runtime.Platform;
import org.eclipse.swt.widgets.Shell;
import org.osgi.framework.Bundle;

import securelinks.Connection;

import java.awt.GridLayout;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.util.List;

import javax.swing.JLabel;
import javax.swing.JOptionPane;

import java.awt.Font;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;

import javax.swing.SwingConstants;
import javax.swing.UIManager;
import javax.imageio.ImageIO;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;

public class SLView extends JDialog {
	
	private static final String TITLE = "Secure Links for IEC 61499";
	private String sysFile;
	private String selectedApp;
	private String slString;
	private JPanel mainPanel;
	
	private List<Connection> conList;
	
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
		
		loadConnections(panelCenter);
		
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
		        UIController.setUpdatedConnectionListFromUI(((SLView)e.getSource()).conList);
		    }
		});
	}
	
	
	private void loadConnections(JPanel panel) {
		UIController controller = UIController.getInstance(this.sysFile, this.selectedApp);
		this.conList = controller.getConnectionList();
		addConnectionPanel(panel, conList);
	}
	
	private void addConnectionPanel(JPanel container, List<Connection> conList) {
		try {

			for(int i = 0; i < conList.size(); i++) {
				
				Connection con = conList.get(i);
				
				JLabel labelFBOut = new JLabel();
				labelFBOut.setText(con.outFB + "." + con.outVariable);
				labelFBOut.setFont(new Font("Calibri", Font.BOLD, 12));
				JLabel labelFBIn = new JLabel();
				labelFBIn.setFont(new Font("Calibri", Font.BOLD, 12));
				labelFBIn.setText(con.inFB + "." + con.inVariable);
				JLabel labelArrow = new JLabel("---------------------------------->");
				labelArrow.setForeground(Color.RED);
				labelArrow.setFont(new Font("Calibri", Font.BOLD, 16));
				
				JPanel panelCon = new JPanel();
				panelCon.setLayout(new GridBagLayout());
	
				GridBagConstraints c = new GridBagConstraints();
				
				Box boxOutFB = createLeftBoxForConnections(labelFBOut);
				c.fill = GridBagConstraints.HORIZONTAL;
				c.gridx = 0; c.gridy = 0; c.ipadx = 10;
				panelCon.add(boxOutFB, c);
				
				c.fill = GridBagConstraints.HORIZONTAL;
				c.gridx = 1; c.gridy = 0; c.ipadx = 10;
				panelCon.add(labelArrow, c);
				
				Box boxInFB = createRightBoxForConnections(labelFBIn);
				c.fill = GridBagConstraints.HORIZONTAL;
				c.gridx = 2; c.gridy = 0; c.ipadx = 10;
				panelCon.add(boxInFB, c);
				
		
				c.fill = GridBagConstraints.HORIZONTAL;
				c.gridx = 3; c.gridy = 0; c.ipadx = 10;
				panelCon.add(addButton(panelCon, con), c);
				
				container.add(panelCon);
			}
		}
	    catch (Exception e) {
	    	JOptionPane.showMessageDialog(null, e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
	    }
	}
	
	private Box createLeftBoxForConnections(JLabel labelFBOut) throws IOException {
		
		BufferedImage wPic = null;
		Box boxOutFB = new Box(BoxLayout.X_AXIS);
		//boxOutFB.setBorder(BorderFactory.createLineBorder(Color.BLACK));
		
		Bundle bundle = Platform.getBundle("SecureLinks");	
		if(bundle == null) //check if plugin is loaded
			wPic = ImageIO.read(this.getClass().getResource("/functionblockout.png"));
		else {
			wPic = ImageIO.read(bundle.getResource("resources/functionblockout.png"));
		}
				
		JLabel wIcon = new JLabel(new ImageIcon(wPic));
		boxOutFB.add(labelFBOut);
		boxOutFB.add(Box.createRigidArea(new Dimension(5, 0)));
		boxOutFB.add(wIcon);
	
		return boxOutFB;
	}
	
	private Box createRightBoxForConnections(JLabel labelFBIn) throws IOException {
		
		BufferedImage wPic = null;
		Box boxInFB = new Box(BoxLayout.X_AXIS);
	
		Bundle bundle = Platform.getBundle("SecureLinks");	
		if(bundle == null) //check if plugin is loaded
			wPic = ImageIO.read(this.getClass().getResource("/functionblockout.png"));
		else {
			wPic = ImageIO.read(bundle.getResource("resources/functionblockout.png"));
		}

		JLabel wIcon = new JLabel(new ImageIcon(wPic));
		boxInFB.add(wIcon);
		boxInFB.add(Box.createRigidArea(new Dimension(5, 0)));
		boxInFB.add(labelFBIn);
		

		return boxInFB;
	}
	
	private JButton addButton(JPanel panelCon, Connection con) throws IOException {
		
		Image addbtn = null;
		JButton buttonAdd = new JButton();
			
		Bundle bundle = Platform.getBundle("SecureLinks");	
		if(bundle == null) //check if plugin is loaded
			addbtn = ImageIO.read(this.getClass().getResource("/addbutton.png"));
		else {
			addbtn = ImageIO.read(bundle.getResource("resources/addbutton.png"));
		}

		buttonAdd.setIcon(new ImageIcon(addbtn));
		buttonAdd.setMargin(new java.awt.Insets(0, 0, 0, 0));
		buttonAdd.setBackground(new Color(240, 240, 240));
		buttonAdd.setBorder(null);
		buttonAdd.setToolTipText("Add/Edit a secure link");
		
		buttonAdd.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				String result = (String) JOptionPane.showInputDialog(panelCon, "Secure link annotations (Starts with @SL) ", 
						"Add/Exit Secure Link", JOptionPane.PLAIN_MESSAGE, null, null, con.connectionComment);
				if(result != null)
					con.connectionComment = result;
			}
		});
		
		return buttonAdd;
	}
	
	public List<Connection> getUpdatedConnectionList() {
		return conList;
	}

}
