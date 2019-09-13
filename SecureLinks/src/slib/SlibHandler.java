package slib;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.eclipse.core.runtime.Platform;
import org.osgi.framework.Bundle;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

/**
 * Class is excluded from the project. All the functionality moved to SlibFBNetwork class
 * @author atanveer
 *
 */


public class SlibHandler {

	private final int FIRST_ELEMENT = 0;
	private final String SLIB_DIRECTORY = "Slib/";
	private final String TAG_META_DATA = "meta";
	private final String TAG_IN = "in";
	private final String TAG_OUT = "out";
	private final String TAG_FB_DEFINITION = "FBdef";
	private final String TAG_VAR = "Var";
	private final String TAG_VAR_TYPE = "Vartype";
	private final String TAG_NAME = "Name";
	
	private Document fbnDoc = null;
	private final String SECURE_LINK_REGEX = "@[sS][lL]\\s*\\((\\s*\\w*\\s*,\\s*\\w*\\s*,)\\s*\\w+\\s*\\)";
	
	public SlibFBNetwork instantiateFBN(String fbnName) throws Exception {
		
		SlibFBNetwork fbn = null;
		
		String fbnFileName = SLIB_DIRECTORY + fbnName + ".fbn";
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		DocumentBuilder builder = factory.newDocumentBuilder(); 
		
		fbnDoc = builder.parse(loadFBNFile(fbnFileName));
		
		if(fbnDoc != null) // Checks if we have the SLIB definition file for the specified FBN.
			fbn = loadFBN();
			
		return fbn;
	}
	
	private SlibFBNetwork loadFBN() {
		
		SlibFBNetwork fbn = null;

		fbn = new SlibFBNetwork();
		
		fbn.setFbnName(getSlibFBNetowrkName()); 
		fbn.setInFBDefinition(this.getInFBDefAttribute()); 
		fbn.setOutFbDefinition(this.getOutFBDefAttribute()); 
		fbn.setInVariable(getInFBVariable()); 
		fbn.setOutVariable(getOutFBVariable()); 
		fbn.setInVariableType(getInVariableType()); 
		fbn.setOutVariableType(getOutVariableType()); 

		return fbn;
	}
	
	private InputStream loadFBNFile(String fbnFileName) throws FileNotFoundException  {
		
		InputStream insFbn = null;
		Bundle bundle = Platform.getBundle("SecureLinks");	
		
		if(bundle == null) //check if plugin is loaded
			insFbn =  new FileInputStream(new File(fbnFileName)); // Written only because of testing as a normal java application  
		else {
			insFbn = this.getClass().getResourceAsStream("resources" + fbnFileName); //TO_DO Need to test for plugin
		}
		return insFbn;
	}
	
	/**
	 * Finds the function block network definition file (.fbn) in the Secure library (Slib)
	 * @return true if definition exists else false
	 */
	private boolean findFBNDefintion(String fbnName) {

		File f = new File(SLIB_DIRECTORY);
		File[] flist = f.listFiles();
		for(File f1 : flist)
			if(f1.getName().equals(fbnName))
				return true;
		return false;
	}
	
	private String getSlibFBNetowrkName() {
		return ((Element) ((Element) this.fbnDoc.getDocumentElement().
				getElementsByTagName(TAG_META_DATA).item(FIRST_ELEMENT))).
				getAttributes().getNamedItem(TAG_NAME).getNodeValue();
	}
	
	private String getInFBDefAttribute() {
		return ((Element) ((Element) this.fbnDoc.getDocumentElement().
				getElementsByTagName(TAG_META_DATA).item(FIRST_ELEMENT)).getElementsByTagName(TAG_IN).
				item(FIRST_ELEMENT)).getAttributes().getNamedItem(TAG_FB_DEFINITION).getNodeValue();

	}
	
	private String getOutFBDefAttribute() {
		return ((Element) ((Element) this.fbnDoc.getDocumentElement().
				getElementsByTagName(TAG_META_DATA).item(FIRST_ELEMENT)).getElementsByTagName(TAG_OUT).
				item(FIRST_ELEMENT)).getAttributes().getNamedItem(TAG_FB_DEFINITION).getNodeValue();

	}
	
	private String getInFBVariable() {
		return ((Element) ((Element) this.fbnDoc.getDocumentElement().
				getElementsByTagName(TAG_META_DATA).item(FIRST_ELEMENT)).getElementsByTagName(TAG_IN).
				item(FIRST_ELEMENT)).getAttributes().getNamedItem(TAG_VAR).getNodeValue();

	}
	
	private String getOutFBVariable() {
		return ((Element) ((Element) this.fbnDoc.getDocumentElement().
				getElementsByTagName(TAG_META_DATA).item(FIRST_ELEMENT)).getElementsByTagName(TAG_OUT).
				item(FIRST_ELEMENT)).getAttributes().getNamedItem(TAG_VAR).getNodeValue();

	}
	
	private String getInVariableType() {
		return ((Element) ((Element) this.fbnDoc.getDocumentElement().
				getElementsByTagName(TAG_META_DATA).item(FIRST_ELEMENT)).getElementsByTagName(TAG_IN).
				item(FIRST_ELEMENT)).getAttributes().getNamedItem(TAG_VAR_TYPE).getNodeValue();

	}
	
	private String getOutVariableType() {
		return ((Element) ((Element) this.fbnDoc.getDocumentElement().
				getElementsByTagName(TAG_META_DATA).item(FIRST_ELEMENT)).getElementsByTagName(TAG_OUT).
				item(FIRST_ELEMENT)).getAttributes().getNamedItem(TAG_VAR_TYPE).getNodeValue();

	}
	
}
