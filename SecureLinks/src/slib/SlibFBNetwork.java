package slib;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;

import org.eclipse.core.runtime.Platform;
import org.osgi.framework.Bundle;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;

public class SlibFBNetwork {
	
	private final String PLUGIN_BUNDLE_NAME = "SecureLinks";
	
	private final int FIRST_ELEMENT = 0;
	private final String SLIB_DIRECTORY = "Slibrary/";
	private final String FBN_FILE_EXT = ".fbn";
	private final String TAG_META_DATA = "meta";
	private final String TAG_IN = "in";
	private final String TAG_OUT = "out";
	private final String TAG_FB_DEFINITION = "FBdef";
	private final String TAG_VAR = "Var";
	private final String TAG_VAR_TYPE = "Vartype";
	private final String TAG_NAME = "Name";
	private final String TAG_DEVICE_LEFT = "deviceLeft";
	private final String TAG_DEVICE_RIGHT = "deviceRight";
	private final String TAG_FB = "FB";
	private final String PARAMS_NULL = "null";
	private final String PARAMS_SPLITTER = ",";


	//private final String SECURE_LINK_REGEX = "@[sS][lL]\\s*\\((\\s*\\w*\\s*,\\s*\\w*\\s*,)\\s*\\w+\\s*\\)";
	
	private String fbnName;
	
	private String inFbDef;
	private String inVar;
	private String inVarType;
	
	private String outFbDefinition;
	private String outVar;
	private String outVarType;
	
	private Document fbnDoc = null;
	private String params = null;
	private List<String> paramsList;
	
	private Set<String> setLeftDeviceFBs; 
	private Set<String> setRightDeviceFBs; 
	
	
	public boolean instantiateFBN(String fbnName, String params) throws Exception {
	
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		DocumentBuilder builder = factory.newDocumentBuilder(); 
		
		fbnDoc = builder.parse(loadFBNFile(fbnName));
		
		if(fbnDoc != null) { // Checks if we have the SLIB definition file for the specified FBN.
			this.params = params;
			loadFBN();
			return true;
		}
		return false;
	}
	
	private void loadFBN() {
		
		setFbnName(getSlibFBNetowrkName()); 
		setInFBDefinition(getInFBDefAttribute()); 
		setOutFbDefinition(getOutFBDefAttribute()); 
		setInVariable(getInFBVariable()); 
		setOutVariable(getOutFBVariable()); 
		setInVariableType(getInVariableTypeFromFBNFile()); 
		setOutVariableType(getOutVariableTypeFromFBNFile()); 
		assignParams(this.params);
		loadDeviceMappings();
	}
	
	private InputStream loadFBNFile(String fbnName) throws IOException  {
		
		String fbnFileName = null;
		InputStream insFbn = null;
		Bundle bundle = Platform.getBundle(PLUGIN_BUNDLE_NAME);	
		
		if(bundle == null) { //check if plugin is loaded
			fbnFileName = SLIB_DIRECTORY + fbnName + FBN_FILE_EXT;
			insFbn =  new FileInputStream(new File(fbnFileName)); // Written only because of testing as a normal java application  
		}
		else {
			fbnFileName = "/" + SLIB_DIRECTORY + fbnName + FBN_FILE_EXT;
			insFbn =  bundle.getEntry(fbnFileName).openConnection().getInputStream();
		}
		return insFbn;
	}
	
	private void assignParams(String params) {
		
		if(!params.toLowerCase().equals(PARAMS_NULL)) {
			
			paramsList =  new ArrayList<String>();
			String[] pList = params.split(PARAMS_SPLITTER);
			
			for(int i = 0; i < pList.length; i++) 
				addToParamsList(pList[i].trim());
		}
	}
	
	private void loadDeviceMappings() {
		loadLeftDeviceMappings();
		loadRightDeviceMappings();
	}
	
	private void loadLeftDeviceMappings() {
		
		setLeftDeviceFBs = new HashSet<String>();
		Element dLeft = (Element) ((Element)this.fbnDoc.getDocumentElement().
				getElementsByTagName(TAG_META_DATA).item(FIRST_ELEMENT)).
				getElementsByTagName(TAG_DEVICE_LEFT).item(FIRST_ELEMENT);
		NodeList nList = dLeft.getElementsByTagName(TAG_FB);
		for(int i = 0; i < nList.getLength(); i++) 
			addToLeftDeviceSet(nList.item(i).getAttributes().getNamedItem(TAG_NAME).getNodeValue());
	}
	
private void loadRightDeviceMappings() {
		
		setRightDeviceFBs = new HashSet<String>();
		Element dLeft = (Element) ((Element)this.fbnDoc.getDocumentElement().
				getElementsByTagName(TAG_META_DATA).item(FIRST_ELEMENT)).
				getElementsByTagName(TAG_DEVICE_RIGHT).item(FIRST_ELEMENT);
		NodeList nList = dLeft.getElementsByTagName(TAG_FB);
		for(int i = 0; i < nList.getLength(); i++) 
			addToRightDeviceSet(nList.item(i).getAttributes().getNamedItem(TAG_NAME).getNodeValue());
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
	
	private String getInVariableTypeFromFBNFile() {
		return ((Element) ((Element) this.fbnDoc.getDocumentElement().
				getElementsByTagName(TAG_META_DATA).item(FIRST_ELEMENT)).getElementsByTagName(TAG_IN).
				item(FIRST_ELEMENT)).getAttributes().getNamedItem(TAG_VAR_TYPE).getNodeValue();

	}
	
	private String getOutVariableTypeFromFBNFile() {
		return ((Element) ((Element) this.fbnDoc.getDocumentElement().
				getElementsByTagName(TAG_META_DATA).item(FIRST_ELEMENT)).getElementsByTagName(TAG_OUT).
				item(FIRST_ELEMENT)).getAttributes().getNamedItem(TAG_VAR_TYPE).getNodeValue();

	}
	
	//////////// Getters and Setters	
	
	public String getFbnName() {
		return fbnName;
	}

	private void setFbnName(String fbName) {
		this.fbnName = fbName;
	}

	public String getInFBDefinition() {
		return inFbDef;
	}
	
	private void setInFBDefinition(String inFbDef) {
		this.inFbDef = inFbDef;
	}
	
	public String getInVariable() {
		return inVar;
	}
	
	private void setInVariable(String inVar) {
		this.inVar = inVar;
	}
	
	public String getInVariableType() {
		return inVarType;
	}
	
	private void setInVariableType(String inVarType) {
		this.inVarType = inVarType;
	}

	public String getOutFbDefinition() {
		return outFbDefinition;
	}
	
	private void setOutFbDefinition(String outFbDefinition) {
		this.outFbDefinition = outFbDefinition;
	}
	
	public String getOutVariable() {
		return outVar;
	}
	
	private void setOutVariable(String outVar) {
		this.outVar = outVar;
	}
	
	public String getOutVariableType() {
		return outVarType;
	}
	
	private void setOutVariableType(String outVarType) {
		this.outVarType = outVarType;
	}

	public String getParameter(int index) {
		return paramsList.get(index);
	}

	private void addToParamsList(String p) {
		this.paramsList.add(p);
	}
	
	private void addToLeftDeviceSet(String fbName) {
		this.setLeftDeviceFBs.add(fbName);
	}
	
	private void addToRightDeviceSet(String fbName) {
		this.setRightDeviceFBs.add(fbName);
	}
}
