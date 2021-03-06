package ui;

import java.util.ArrayList;
import java.util.List;

import org.eclipse.swt.widgets.Shell;
import org.eclipse.ui.IWorkbenchWindow;

import securelinks.Connection;
import slib.Compiler;

public class UIController {

	private static String sysFile;
	private static String selectedApp;
	private List<Connection> conList;
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
		Connection.loadSysFile(sysFile, selectedApp);
		return Connection.getInterDeviceDataConnections();
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
	
	public List<Connection> getUpdatedConnectionListFromUI() {
		return conList;
	}
	
	public void setUpdatedConnectionListFromUI(List<Connection> conListp) {
		conList = new ArrayList<Connection>(conListp);
	}
	
	public void SaveConnections() {
		List<Connection> conList = getUpdatedConnectionListFromUI();
		Connection.UpdateConnections(conList);
	}
	
	public boolean compileAction(Connection con) throws Exception {
		
		if(con.isValidSecureLink(con)) {
			Compiler compilerObj = new Compiler(con);
			if(compilerObj.compile())
				return true;
		}
			return false;
	}
	
}
