package securelinks;

import ui.SLView;

public class TestExecute {

	public static void main(String[] args) {
		System.out.println("Awais");
		String sysFileAbsolutePath = "C:\\Users\\atanveer\\OneDrive - AUT University\\1. D drive\\Awais\\Software Setups\\4diac-ide-incubation_1.10.3-win32.win32.x86_64\\4diac-ide\\workspace\\test\\test.sys";
		String selectedApp = "testApp";
		SLView view = new SLView(sysFileAbsolutePath, selectedApp, null);
		view.setVisible(true);
	}

}
