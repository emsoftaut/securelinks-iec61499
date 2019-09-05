package securelinks;

import java.util.List;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IProject;
import org.eclipse.core.resources.ResourcesPlugin;
import org.eclipse.fordiac.ide.application.editors.ApplicationEditor;
import org.eclipse.fordiac.ide.model.libraryElement.AutomationSystem;
import org.eclipse.fordiac.ide.systemmanagement.SystemManager;
import org.eclipse.ui.IEditorPart;
import org.eclipse.ui.IWorkbenchWindow;

public class FordiacIDE {
	private IWorkbenchWindow window;
	private final String SYSTEM_FILE_EXT = ".sys";
	private String selectedApplication = null;

	public FordiacIDE(IWorkbenchWindow window) {
		this.window = window;
	}
	
	private String getApplicationEditorProjectPath(IProject proj) {
		return proj.getWorkspace().getRoot().getLocation().toString() + proj.getFullPath().toString();
	}
	
	private IProject getProjectFromApplicationEditor(IEditorPart activeEditor) {
		IProject activeEditorProject = null;
		ApplicationEditor activeApplicationEditor = null;
		if(activeEditor instanceof ApplicationEditor) {	//we are concerned with application editor
			activeApplicationEditor = (ApplicationEditor) activeEditor;
			activeEditorProject = activeApplicationEditor.getSystem().getProject();
		}
		return activeEditorProject;
	}
	
	/**
	 * Get full project path that contains the selected FB network application  ----- MIGHT NOT NEED IT
	 * */
	private String getProjectPathFromEditor() {
		String projectPath = null;
		IProject activeEditorProject = getProjectFromApplicationEditor(window.getActivePage().getActiveEditor()); //we are concerned with application editor
		if(activeEditorProject != null) {	
			String appEditorProjectPath = getApplicationEditorProjectPath(activeEditorProject);
			String workspacePath = ResourcesPlugin.getWorkspace().getRoot().getLocation().toString();
			List<AutomationSystem> systems = SystemManager.INSTANCE.getSystems(); 
			
			/*Get the project for which the active editor belongs to.*/
			for(int i = 0; i < systems.size();i++) {
				AutomationSystem system = systems.get(i);
				projectPath = workspacePath + system.getProject().getFullPath().toString();
				if(projectPath.equals(appEditorProjectPath)) 
					break;
				else 
					projectPath = null;
			}	
		}
		return projectPath;
	}
	
	public IFile getSysFile() {
		IProject proj = getProjectFromApplicationEditor(window.getActivePage().getActiveEditor());
		IFile sysFile = proj.getFile(proj.getName() + SYSTEM_FILE_EXT);
		return sysFile;
	}
	
	public boolean isRequiredFBApplication() {
		String projectPath = null;
		IProject activeEditorProject = getProjectFromApplicationEditor(window.getActivePage().getActiveEditor()); //we are concerned with application editor
		if(activeEditorProject != null) {	
			String appEditorProjectPath = getApplicationEditorProjectPath(activeEditorProject);
			String workspacePath = ResourcesPlugin.getWorkspace().getRoot().getLocation().toString();
			List<AutomationSystem> systems = SystemManager.INSTANCE.getSystems(); 
			
			/*Get the project for which the active editor belongs to.*/
			for(int i = 0; i < systems.size();i++) {
				AutomationSystem system = systems.get(i);
				projectPath = workspacePath + system.getProject().getFullPath().toString();
				if(projectPath.equals(appEditorProjectPath)) {
					setSelectedApplication(window.getActivePage().getActiveEditor());
					return true;
				}
			}	
		}
		return false;
	}
	
	public void setSelectedApplication(IEditorPart activeEditor) {
		this.selectedApplication = activeEditor.getTitle();
	}
	
	public String getSelectedApplication() {
		return this.selectedApplication;
	}
}
