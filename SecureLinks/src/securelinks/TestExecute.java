package securelinks;

import java.util.List;
import java.util.UUID;

import org.eclipse.core.resources.ResourcesPlugin;

import ui.SLView;
import ui.UIController;

public class TestExecute {

	public static void main(String[] args) {
	
		//String sysFileAbsolutePath = "C:\\Users\\atanveer\\OneDrive - AUT University\\1. D drive\\Awais\\Software Setups\\4diac-ide-incubation_1.10.3-win32.win32.x86_64\\4diac-ide\\workspace\\test\\test.sys";
		String sysFileAbsolutePath = "C:\\Users\\Awais\\OneDrive - AUT University\\1. D drive\\Awais\\Software Setups\\4diac-ide-incubation_1.10.3-win32.win32.x86_64\\4diac-ide\\workspace\\test\\test.sys";
		String selectedApp = "testApp";
		
		UIController uiController = UIController.getInstance(sysFileAbsolutePath, selectedApp);
		uiController.loadSecureLinkGUI(null);

		//uiController.SaveConnections();

	}

}
