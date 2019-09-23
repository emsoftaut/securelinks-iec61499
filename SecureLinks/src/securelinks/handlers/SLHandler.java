package securelinks.handlers;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.ui.IWorkbenchWindow;
import org.eclipse.ui.handlers.HandlerUtil;

import securelinks.FordiacIDE;
import ui.UIController;


public class SLHandler extends AbstractHandler {
	
	private static IWorkbenchWindow window;
	
	@Override
	public Object execute(ExecutionEvent event) throws ExecutionException {
		window = HandlerUtil.getActiveWorkbenchWindowChecked(event);		
		FordiacIDE ideOps = new FordiacIDE(window); 
		
		if(ideOps.isRequiredFBApplication()) {
			String sysFileAbsolutePath = ideOps.getSysFilePath();
			String selectedApp = ideOps.getSelectedApplication();
		
			UIController ui =  UIController.getInstance(sysFileAbsolutePath, selectedApp);
			ui.loadSecureLinkGUI(window);
			
			//MessageDialog.openInformation(window.getShell(), "Debug", "System file: " + sysFileAbsolutePath + " Selecetd app: " + selectedApp);
		}
		else
			MessageDialog.openInformation(window.getShell(), "Debug", 
					"Selected editor is not an application or does not belong to a loadedd project" );

		return null;
	}
	
}	