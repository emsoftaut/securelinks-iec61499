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
import org.w3c.dom.Node;
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
	private final String TAG_TYPE = "type";
	private final String TAG_NAME = "Name";
	private final String TAG_DEVICE_LEFT = "deviceLeft";
	private final String TAG_DEVICE_RIGHT = "deviceRight";
	private final String TAG_FB = "FB";
	private final String TAG_EVENT_CONNECTIONS = "EventConnections";
	private final String TAG_DATA_CONNECTIONS = "DataConnections";
	private final String TAG_CONNECTION = "Connection";
	private final String TAG_DESTINATION = "Destination";
	private final String TAG_SOURCE = "Source";
	private final String TAG_APPLICATION = "Application";
	private final String TAG_SUB_APPLICATION_NETWORK = "SubAppNetwork";
	private final String TAG_PARAMS = "params";
	private final String TAG_VARIABLE = "Variable";
	private final String TAG_DEFAULT = "default";
	private final String PARAMS_NULL = "null";
	private final String PARAMS_SPLITTER = ",";


	//private final String SECURE_LINK_REGEX = "@[sS][lL]\\s*\\((\\s*\\w*\\s*,\\s*\\w*\\s*,)\\s*\\w+\\s*\\)";
	
	private String fbnName;
	
	private String inFbDef;
	private String inFBName;
	private String inVar;
	private String inVarType;
	
	private String outFbDef;
	private String outFBName;
	private String outVar;
	private String outVarType;
	
	private Document fbnDoc = null;
	private String params = null;
	private List<FbnParameters> paramsList;
	
	private Set<String> setOfLeftDeviceFBs; 
	private Set<String> setOfRightDeviceFBs; 
	
	
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
		
		this.fbnName = loadSlibFBNetowrkName();
		this.inFBName = loadSlibInFBName();
		this.outFBName = loadSlibOutFBName();
		this.inFbDef = loadSlibInFBDefAttribute(); 
		this.outFbDef = loadSlibOutFBDefAttribute(); 
		this.inVar = loadSlibInFBVarAttValue().split("\\.")[1]; 
		this.outVar = loadSlibOutFBVarAttValue().split("\\.")[1]; 
		this.inVarType = loadSlibInVariableTypeFromFBNFile(); 
		this.outVarType = loadSlibOutVariableTypeFromFBNFile();
		loadParams();
		assignParams(this.params);
		loadDeviceMappings();
	}
	
	private InputStream loadFBNFile(String fbnName) throws IOException  {
		
		String fbnFileName = null;
		InputStream insFbn = null;
		Bundle bundle = getBundle();
		
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
	
	private void loadParams() {
		Element paramsNode = (Element) this.fbnDoc.getElementsByTagName(TAG_PARAMS).item(FIRST_ELEMENT);
		NodeList varList = paramsNode.getElementsByTagName(TAG_VARIABLE);
		
		if(varList.getLength() > 0) {
			this.paramsList = new ArrayList<FbnParameters>();
			
			for(int i = 0; i < varList.getLength(); i++) {
				String nameAttribute = varList.item(i).getAttributes().getNamedItem(TAG_NAME).getNodeValue();
				String varType = varList.item(i).getAttributes().getNamedItem(TAG_TYPE).getNodeValue();
				String defaultVal = varList.item(i).getAttributes().getNamedItem(TAG_DEFAULT).getNodeValue();
				
				FbnParameters param = new FbnParameters();
				param.setFbName(nameAttribute.split("\\.")[0]);
				param.setParamName(nameAttribute.split("\\.")[1]);
				param.setParamType(varType);
				param.setParamtVal(defaultVal);
				
				this.paramsList.add(param);
			}
		}
	}
	
	private void assignParams(String params) {
		
		if(!params.toLowerCase().equals(PARAMS_NULL)) {
			String[] pList = params.split(PARAMS_SPLITTER);
			
			for(int i = 0; i < pList.length; i++) 
				this.paramsList.get(i).setParamtVal(pList[i].trim());
		}
	}
	
	private void loadDeviceMappings() {
		loadLeftDeviceMappings();
		loadRightDeviceMappings();
	}
	
	private void loadLeftDeviceMappings() {
		
		setOfLeftDeviceFBs = new HashSet<String>();
		Element dLeft = (Element) ((Element)this.fbnDoc.getDocumentElement().
				getElementsByTagName(TAG_META_DATA).item(FIRST_ELEMENT)).
				getElementsByTagName(TAG_DEVICE_LEFT).item(FIRST_ELEMENT);
		NodeList nList = dLeft.getElementsByTagName(TAG_FB);
		for(int i = 0; i < nList.getLength(); i++) 
			addToLeftDeviceSet(nList.item(i).getAttributes().getNamedItem(TAG_NAME).getNodeValue());
	}
	
	private void loadRightDeviceMappings() {
		
		setOfRightDeviceFBs = new HashSet<String>();
		Element dLeft = (Element) ((Element)this.fbnDoc.getDocumentElement().
				getElementsByTagName(TAG_META_DATA).item(FIRST_ELEMENT)).
				getElementsByTagName(TAG_DEVICE_RIGHT).item(FIRST_ELEMENT);
		NodeList nList = dLeft.getElementsByTagName(TAG_FB);
		for(int i = 0; i < nList.getLength(); i++) 
			addToRightDeviceSet(nList.item(i).getAttributes().getNamedItem(TAG_NAME).getNodeValue());
	}
	
	private String loadSlibInFBName() {
		return loadSlibInFBVarAttValue().split("\\.")[0]; 
	}
	
	private String loadSlibOutFBName() {
		return loadSlibOutFBVarAttValue().split("\\.")[0]; 
	}
	
	private String loadSlibFBNetowrkName() {
		return ((Element) ((Element) this.fbnDoc.getDocumentElement().
				getElementsByTagName(TAG_META_DATA).item(FIRST_ELEMENT))).
				getAttributes().getNamedItem(TAG_NAME).getNodeValue();
	}
	
	private String loadSlibInFBDefAttribute() {
		return ((Element) ((Element) this.fbnDoc.getDocumentElement().
				getElementsByTagName(TAG_META_DATA).item(FIRST_ELEMENT)).getElementsByTagName(TAG_IN).
				item(FIRST_ELEMENT)).getAttributes().getNamedItem(TAG_FB_DEFINITION).getNodeValue();

	}
	
	private String loadSlibOutFBDefAttribute() {
		return ((Element) ((Element) this.fbnDoc.getDocumentElement().
				getElementsByTagName(TAG_META_DATA).item(FIRST_ELEMENT)).getElementsByTagName(TAG_OUT).
				item(FIRST_ELEMENT)).getAttributes().getNamedItem(TAG_FB_DEFINITION).getNodeValue();

	}
	
	private String loadSlibInFBVarAttValue() {
		return ((Element) ((Element) this.fbnDoc.getDocumentElement().
				getElementsByTagName(TAG_META_DATA).item(FIRST_ELEMENT)).getElementsByTagName(TAG_IN).
				item(FIRST_ELEMENT)).getAttributes().getNamedItem(TAG_VAR).getNodeValue();

	}
	
	private String loadSlibOutFBVarAttValue() {
		return ((Element) ((Element) this.fbnDoc.getDocumentElement().
				getElementsByTagName(TAG_META_DATA).item(FIRST_ELEMENT)).getElementsByTagName(TAG_OUT).
				item(FIRST_ELEMENT)).getAttributes().getNamedItem(TAG_VAR).getNodeValue();

	}
	
	private String loadSlibInVariableTypeFromFBNFile() {
		return ((Element) ((Element) this.fbnDoc.getDocumentElement().
				getElementsByTagName(TAG_META_DATA).item(FIRST_ELEMENT)).getElementsByTagName(TAG_IN).
				item(FIRST_ELEMENT)).getAttributes().getNamedItem(TAG_VAR_TYPE).getNodeValue();

	}
	
	private String loadSlibOutVariableTypeFromFBNFile() {
		return ((Element) ((Element) this.fbnDoc.getDocumentElement().
				getElementsByTagName(TAG_META_DATA).item(FIRST_ELEMENT)).getElementsByTagName(TAG_OUT).
				item(FIRST_ELEMENT)).getAttributes().getNamedItem(TAG_VAR_TYPE).getNodeValue();

	}
	
	public NodeList getFBs() {
		Element application = (Element) this.fbnDoc.getDocumentElement().
								getElementsByTagName(TAG_APPLICATION).item(FIRST_ELEMENT);
		Element subAppNet = (Element) application.getElementsByTagName(TAG_SUB_APPLICATION_NETWORK).item(FIRST_ELEMENT);
		
		NodeList FBs = subAppNet.getElementsByTagName(TAG_FB);
		return FBs; 
	}
	
	public NodeList getLeftDeviceFBs() {
		
		List<Node> leftDevFbNodes = new ArrayList<Node>();
		
		NodeList fbList = new NodeList() {
			
			@Override
			public Node item(int index) {
				return leftDevFbNodes.get(index);
			}
			
			@Override
			public int getLength() {
				return leftDevFbNodes.size();
			}
		};
		
		NodeList allFBs = getFBs();
		Set<String> deviceFBs = getLeftDeviceFbNameSet();
		
		for(int i = 0; i < allFBs.getLength(); i++) {
			if(deviceFBs.contains(allFBs.item(i).getAttributes().getNamedItem(TAG_NAME).getNodeValue()))
					leftDevFbNodes.add(allFBs.item(i));
		}
		return fbList;
	}
	
	public NodeList getRightDeviceFBs() {
		
		List<Node> rightDevFbNodes = new ArrayList<Node>();
		
		NodeList fbList = new NodeList() {
			
			@Override
			public Node item(int index) {
				return rightDevFbNodes.get(index);
			}
			
			@Override
			public int getLength() {
				return rightDevFbNodes.size();
			}
		};
		
		NodeList allFBs = getFBs();
		Set<String> deviceFBs = getRightDeviceFbNameSet();
		
		for(int i = 0; i < allFBs.getLength(); i++) {
			if(deviceFBs.contains(allFBs.item(i).getAttributes().getNamedItem(TAG_NAME).getNodeValue()))
					rightDevFbNodes.add(allFBs.item(i));
		}
		return fbList;
	}
	
	public NodeList getEventConnections() {
		Element application = (Element) this.fbnDoc.getDocumentElement().
								getElementsByTagName(TAG_APPLICATION).item(FIRST_ELEMENT);
		Element subAppNet = (Element) application.getElementsByTagName(TAG_SUB_APPLICATION_NETWORK).item(FIRST_ELEMENT);
		
		NodeList eventCons = ((Element)subAppNet.getElementsByTagName(TAG_EVENT_CONNECTIONS).item(FIRST_ELEMENT)).
									getElementsByTagName(TAG_CONNECTION);
		return eventCons; 
	}
	
	public NodeList getDataConnections() {
		Element application = (Element) this.fbnDoc.getDocumentElement().
								getElementsByTagName(TAG_APPLICATION).item(FIRST_ELEMENT);
		Element subAppNet = (Element) application.getElementsByTagName(TAG_SUB_APPLICATION_NETWORK).item(FIRST_ELEMENT);
		
		NodeList dataCons = ((Element)subAppNet.getElementsByTagName(TAG_DATA_CONNECTIONS).item(FIRST_ELEMENT)).
									getElementsByTagName(TAG_CONNECTION);
		return dataCons; 
	}
	
	public NodeList getLeftDeviceEventConnections() {
		
		List<Node> eventConNodes = new ArrayList<Node>();
		NodeList newNodeList = new NodeList() {
			@Override
			public Node item(int index) {	
				return eventConNodes.get(index);
			}
			
			@Override
			public int getLength() {
				return eventConNodes.size();
			}
		};

		NodeList nList = getEventConnections();
		
		for(int i = 0; i < nList.getLength(); i++) {
			String fbDst = nList.item(i).getAttributes().getNamedItem(TAG_DESTINATION).getNodeValue().split("\\.")[FIRST_ELEMENT];
			String fbSrc = nList.item(i).getAttributes().getNamedItem(TAG_SOURCE).getNodeValue().split("\\.")[FIRST_ELEMENT];
			Set<String> deviceFBs = getLeftDeviceFbNameSet();

			if(deviceFBs.contains(fbDst) && deviceFBs.contains(fbSrc)) {
				eventConNodes.add(nList.item(i));
			}
		}

		return newNodeList;
	}
	
	public NodeList getRightDeviceEventConnections() {
		
		List<Node> eventConNodes = new ArrayList<Node>();
		NodeList newNodeList = new NodeList() {
			@Override
			public Node item(int index) {	
				return eventConNodes.get(index);
			}
			
			@Override
			public int getLength() {
				return eventConNodes.size();
			}
		};

		NodeList nList = getEventConnections();
		
		for(int i = 0; i < nList.getLength(); i++) {
			String fbDst = nList.item(i).getAttributes().getNamedItem(TAG_DESTINATION).getNodeValue().split("\\.")[FIRST_ELEMENT];
			String fbSrc = nList.item(i).getAttributes().getNamedItem(TAG_SOURCE).getNodeValue().split("\\.")[FIRST_ELEMENT];
			Set<String> deviceFBs = getRightDeviceFbNameSet();

			if(deviceFBs.contains(fbDst) && deviceFBs.contains(fbSrc)) {
				eventConNodes.add(nList.item(i));
			}
		}

		return newNodeList;
	}
	
	public NodeList getLeftDeviceDataConnections() {
		
		List<Node> eventConNodes = new ArrayList<Node>();
		NodeList newNodeList = new NodeList() {
			@Override
			public Node item(int index) {	
				return eventConNodes.get(index);
			}
			
			@Override
			public int getLength() {
				return eventConNodes.size();
			}
		};

		NodeList nList = getDataConnections();
		
		for(int i = 0; i < nList.getLength(); i++) {
			String fbDst = nList.item(i).getAttributes().getNamedItem(TAG_DESTINATION).getNodeValue().split("\\.")[FIRST_ELEMENT];
			String fbSrc = nList.item(i).getAttributes().getNamedItem(TAG_SOURCE).getNodeValue().split("\\.")[FIRST_ELEMENT];
			Set<String> deviceFBs = getLeftDeviceFbNameSet();

			if(deviceFBs.contains(fbDst) && deviceFBs.contains(fbSrc)) {
				eventConNodes.add(nList.item(i));
			}
		}

		return newNodeList;
	}
	
public NodeList getRightDeviceDataConnections() {
		
		List<Node> eventConNodes = new ArrayList<Node>();
		NodeList newNodeList = new NodeList() {
			@Override
			public Node item(int index) {	
				return eventConNodes.get(index);
			}
			
			@Override
			public int getLength() {
				return eventConNodes.size();
			}
		};

		NodeList nList = getDataConnections();
		
		for(int i = 0; i < nList.getLength(); i++) {
			String fbDst = nList.item(i).getAttributes().getNamedItem(TAG_DESTINATION).getNodeValue().split("\\.")[FIRST_ELEMENT];
			String fbSrc = nList.item(i).getAttributes().getNamedItem(TAG_SOURCE).getNodeValue().split("\\.")[FIRST_ELEMENT];
			Set<String> deviceFBs = getRightDeviceFbNameSet();

			if(deviceFBs.contains(fbDst) && deviceFBs.contains(fbSrc)) {
				eventConNodes.add(nList.item(i));
			}
		}

		return newNodeList;
	}
	
	//////////// Getters and Setters	
	
	public String getInFBName() {
		return inFBName;
	}

	public String getOutFBName() {
		return outFBName;
	}

	public String getFbnName() {
		return fbnName;
	}

	public String getInFBDefinition() {
		return inFbDef;
	}
	
	public String getInVariable() {
		return inVar;
	}
	
	public String getInVariableType() {
		return inVarType;
	}
	
	public String getOutFbDefinition() {
		return outFbDef;
	}
	
	public String getOutVariable() {
		return outVar;
	}
	
	public String getOutVariableType() {
		return outVarType;
	}
	
	public String getParameter(int index) {
		return paramsList.get(index).getParamVal();
	}

	private void addToLeftDeviceSet(String fbName) {
		this.setOfLeftDeviceFBs.add(fbName);
	}
	
	private void addToRightDeviceSet(String fbName) {
		this.setOfRightDeviceFBs.add(fbName);
	}
	
	public Set<String> getLeftDeviceFbNameSet() {
		return this.setOfLeftDeviceFBs;
	}
	
	public Set<String> getRightDeviceFbNameSet() {
		return this.setOfRightDeviceFBs;
	}
	
	private Bundle getBundle() {
		if(Platform.isRunning()) {
			return Platform.getBundle(PLUGIN_BUNDLE_NAME);
		}
		return null;
	}
}
