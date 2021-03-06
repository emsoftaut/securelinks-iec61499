package securelinks;

import java.io.File;
import java.util.ArrayList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.OutputKeys;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
//import org.w3c.dom.ls.DOMImplementationLS;


/*
 * This class reads the .sys xml file for a system. 
 * For now, it only supports 4DIAC 1.10.3 or the versions that use HOLOBLOC DTD  
 */
public class SysFileOperator {
	
	private final int FIRST_ELEMENT = 0;
	private final String E_DATA_CONNECTIONS = "DataConnections";
	private final String E_EVENT_CONNECTIONS = "EventConnections";
	private final String E_CONNECTION = "Connection";
	private final String E_APPLICATION = "Application";
	private final String E_SUB_APPLICATION = "SubAppNetwork";
	private final String E_DEVICE = "Device";
	private final String E_RESOURCE = "Resource";
	private final String E_MAPPING = "Mapping";
	private final String E_FB = "FB";
	private final String E_PARAMETER = "Parameter";
	private final String E_FBNETWORK = "FBNetwork";
	private final String A_VALUE = "Value";
	private final String A_SRC = "Source";
	private final String A_DST = "Destination";
	private final String A_NAME = "Name";
	private final String A_FROM = "From";
	private final String A_TO = "To";
	private final String A_COMMENT = "Comment";
	
	private Document system = null;
	private String sysFile = null;
	private String selectedApplication = null;
	
	
	/*
	 * We do this because DOM parser throws a fatal error for HOLOBLOC DTD that fordiac uses. 
	 * Apparently, there shouldn't be <?xml> tag in that DTD. 
	 * Solution copied from stackoverflow.com
	 */
	private void turnOffDTDValidation(DocumentBuilderFactory factory) throws ParserConfigurationException {
		factory.setValidating(false);
		factory.setNamespaceAware(true);
		factory.setFeature("http://xml.org/sax/features/namespaces", false);
		factory.setFeature("http://xml.org/sax/features/validation", false);
		factory.setFeature("http://apache.org/xml/features/nonvalidating/load-dtd-grammar", false);
		factory.setFeature("http://apache.org/xml/features/nonvalidating/load-external-dtd", false);
	}
	
	public SysFileOperator(String sysFile, String application ) {
		try {
			this.sysFile = sysFile;
			this.selectedApplication =  application;
			DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
			
			turnOffDTDValidation(factory);
			
			DocumentBuilder builder = factory.newDocumentBuilder(); 
			system = builder.parse(new File(this.sysFile)); 
		} catch (Exception e) {
			System.out.println("Exception caught by Secure Links: " + e.getMessage());
		}
	}
	
	public void addFBParameter(String device, String fbName, String fbParam, String paramVal) {
		addFBParametersToApp(fbName, fbParam, paramVal);
		addFBParamtersToDevice(device, fbName, fbParam, paramVal);
	}
	
	private void addFBParametersToApp(String fbName, String fbParamName, String paramVal) {
		Element app = getSelectedApplication(selectedApplication);
		Element subapp = (Element) app.getElementsByTagName(E_SUB_APPLICATION).item(FIRST_ELEMENT);
		NodeList fbList = subapp.getElementsByTagName(E_FB);
		
		for(int i = 0; i < fbList.getLength(); i ++) {
			Node fb = fbList.item(i);
			if(fb.getAttributes().getNamedItem(A_NAME).getNodeValue().equals(fbName)) {
				addParameterNodeToFB(fb, fbParamName, paramVal);
				break;
			}
		}
	}
	
	private void addFBParamtersToDevice(String deviceName, String fbName, String fbParamName, String paramVal) {
		Node dev = getDeviceNode(deviceName);
		
		Node fbNetwork = ((Element)dev).getElementsByTagName(E_FBNETWORK).item(FIRST_ELEMENT);
		NodeList devFbConList = ((Element)fbNetwork).getElementsByTagName(E_FB);
		
		for(int i = 0; i < devFbConList.getLength(); i ++) {
			Node fb = devFbConList.item(i);
			if(fb.getAttributes().getNamedItem(A_NAME).getNodeValue().equals(fbName)) {
				addParameterNodeToFB(fb, fbParamName, paramVal);
				break;
			}
		}
	}
	
	private void addParameterNodeToFB(Node fbNode, String paramName, String paramVal) {
		NodeList fbParamsList = ((Element)fbNode).getElementsByTagName(E_PARAMETER);
		Node param = null;
		
		for(int j = 0; j < fbParamsList.getLength(); j++) //check if the parameter already exists. if yes, then just update the value
			if(fbParamsList.item(j).getAttributes().getNamedItem(A_NAME).getNodeValue().equals(paramName)) {
				param = fbParamsList.item(j);
				((Element)param).setAttribute(A_VALUE, paramVal);
				break;
			}
		
		if(param == null) { //if there is no existing parameter by this name, then create a new parameter node
			param = createFBParameterElement(paramName, paramVal);
			fbNode.appendChild(param);
		}
		//System.out.println(((DOMImplementationLS)system.getImplementation()).createLSSerializer().writeToString(fbNode));
	}
	
	private Element createFBParameterElement(String fbParam, String paramVal) {
		Element parameter = system.createElement(E_PARAMETER);
		parameter.setAttribute(A_NAME, fbParam);
		parameter.setAttribute(A_VALUE, paramVal);
		
		return parameter;
	}
	
	public void addFBsfromSlibFBN(NodeList slibFBs) {
		Element app = getSelectedApplication(selectedApplication);
		for(int i = 0; i < slibFBs.getLength(); i++) {
			Node subapp = app.getElementsByTagName(E_SUB_APPLICATION).item(FIRST_ELEMENT);
			subapp.insertBefore(system.importNode(slibFBs.item(i), false), 
					app.getElementsByTagName(E_FB).item(FIRST_ELEMENT));
		}
	}
	
	public void addEventConnectionsToSelectedApp(NodeList slibEventCons) {
		for(int i = 0; i < slibEventCons.getLength(); i++)
			addSingleEventConnectionToSelectedApp(slibEventCons.item(i));
	}
	
	public void addSingleEventConnectionToSelectedApp(Node n) {
		Element app = getSelectedApplication(selectedApplication);
		Element subapp = (Element) app.getElementsByTagName(E_SUB_APPLICATION).item(FIRST_ELEMENT);
		Node eventCons = subapp.getElementsByTagName(E_EVENT_CONNECTIONS).item(FIRST_ELEMENT);
		Node refNode = 	((Element)eventCons).getElementsByTagName(E_CONNECTION).item(FIRST_ELEMENT);
		
		if(n.getOwnerDocument().equals(system)) 
			eventCons.insertBefore(n, refNode);
		else
			eventCons.insertBefore(system.importNode(n, false), refNode);
	}
	
	public void addDataConnectionsToSelectedApp(NodeList slibDataCons) {
		for(int i = 0; i < slibDataCons.getLength(); i++)
			addSingleDataConnectionToSelectedApp(slibDataCons.item(i));
	}
	
	public void addSingleDataConnectionToSelectedApp(Node n) {
		Element app = getSelectedApplication(selectedApplication);
		Element subapp = (Element) app.getElementsByTagName(E_SUB_APPLICATION).item(FIRST_ELEMENT);
		Node dataCons = subapp.getElementsByTagName(E_DATA_CONNECTIONS).item(FIRST_ELEMENT);
		Node refNode = 	((Element)dataCons).getElementsByTagName(E_CONNECTION).item(FIRST_ELEMENT);
		
		if(n.getOwnerDocument().equals(system)) 
			dataCons.insertBefore(n, refNode);
		else
			dataCons.insertBefore(system.importNode(n, false), refNode);
	}
	
	private Node getDeviceNode(String deviceName) {
		Node dev = null; 
		NodeList devs = system.getElementsByTagName(E_DEVICE);
		
		for(int i = 0; i < devs.getLength(); i++) //finding specified device node 
			if(devs.item(i).getAttributes().getNamedItem(A_NAME).getNodeValue().equals(deviceName)) {
				dev = devs.item(i);
				break;
			}
		return dev;
	}
	
	public void addSlibFBsToDevice(NodeList fbList, String deviceName) { 
		for(int i = 0; i < fbList.getLength(); i++) 
			addSingleSlibFBToDevice(fbList.item(i), deviceName);
	}
	
	public void addSingleSlibFBToDevice(Node n, String deviceName) {
		Node dev = getDeviceNode(deviceName);
		
		Node fbNetwork = ((Element)dev).getElementsByTagName(E_FBNETWORK).item(FIRST_ELEMENT);
		NodeList devFbConList = ((Element)fbNetwork).getElementsByTagName(E_FB);

		if(devFbConList.getLength() != 0) { // although this should never be == 0
			Node refNode = devFbConList.item(FIRST_ELEMENT);
			if(n.getOwnerDocument().equals(system)) 
				fbNetwork.insertBefore(n, refNode);
			else
				fbNetwork.insertBefore(system.importNode(n, false), refNode);
		}
	}
	
	public void addSlibEventConnectionsToDevice(NodeList eventConList, String deviceName) {
		Node dev = getDeviceNode(deviceName); 

		Node fbNetwork = ((Element)dev).getElementsByTagName(E_FBNETWORK).item(FIRST_ELEMENT);
		NodeList devEvenConList = ((Element)fbNetwork).getElementsByTagName(E_EVENT_CONNECTIONS);
		
		Node devEventConnections = null;
		
		if(devEvenConList.getLength() == 0) { // if there are no event connections mapped to this device, we create EventConnections element
			devEventConnections = createEventConnectionsElement(eventConList);
			fbNetwork.insertBefore(devEventConnections, fbNetwork.getLastChild());
		}
		else {
			for(int i = 0; i < eventConList.getLength(); i++)
				addSingleEventConnectionToDevice(eventConList.item(i), deviceName);
		}
	}
	
	public void addSingleEventConnectionToDevice(Node n, String deviceName) {
		Node dev = getDeviceNode(deviceName);
		
		Node fbNetwork = ((Element)dev).getElementsByTagName(E_FBNETWORK).item(FIRST_ELEMENT);
		NodeList devEvenConList = ((Element)fbNetwork).getElementsByTagName(E_EVENT_CONNECTIONS);
		
		Node devEventConnections = devEvenConList.item(FIRST_ELEMENT);
		Node refNode =  ((Element)devEventConnections).getElementsByTagName(E_CONNECTION).item(FIRST_ELEMENT); 
		
		if(n.getOwnerDocument().equals(system)) 
			devEventConnections.insertBefore(n, refNode);
		else
			devEventConnections.insertBefore(system.importNode(n, false), refNode);
	}
	
	public void addSlibDataConnectionsToDevice(NodeList dataConList, String deviceName) {
		Node dev = getDeviceNode(deviceName); 
	
		Node fbNetwork = ((Element)dev).getElementsByTagName(E_FBNETWORK).item(FIRST_ELEMENT);
		NodeList devDataConList = ((Element)fbNetwork).getElementsByTagName(E_DATA_CONNECTIONS);
		
		Node devDataConnections = null;
		
		if(devDataConList.getLength() == 0) { // if there are no data connections mapped to this device, we create DataConnections element
			devDataConnections = createDataConnectionsElement(dataConList);
			fbNetwork.insertBefore(devDataConnections, fbNetwork.getLastChild());
		}
		else {
			for(int i = 0; i < dataConList.getLength(); i++)
				addSingleDataConnectionToDevice(dataConList.item(i), deviceName);
		}
	}
	
	public void addSingleDataConnectionToDevice(Node n, String deviceName) {
		Node dev = getDeviceNode(deviceName);
		
		Node fbNetwork = ((Element)dev).getElementsByTagName(E_FBNETWORK).item(FIRST_ELEMENT);
		NodeList devDataConList = ((Element)fbNetwork).getElementsByTagName(E_DATA_CONNECTIONS);
		
		Node devDataConnections = devDataConList.item(FIRST_ELEMENT);;
		Node refNode =  ((Element)devDataConnections).getElementsByTagName(E_CONNECTION).item(FIRST_ELEMENT);;
		
		if(n.getOwnerDocument().equals(system)) 
			devDataConnections.insertBefore(n, refNode);
		else
			devDataConnections.insertBefore(system.importNode(n, false), refNode);
	}
	
	private Element createEventConnectionsElement(NodeList conList) {
		Element evenConnections = system.createElement(E_EVENT_CONNECTIONS);
		
		for(int i = 0; i < conList.getLength(); i++) {
			Node con = conList.item(i).cloneNode(false);
			system.adoptNode(con);
			evenConnections.appendChild(con);
		}
			
		return evenConnections;
	}
	
	private Element createDataConnectionsElement(NodeList conList) {
		Element dataConnections = system.createElement(E_DATA_CONNECTIONS);
		
		for(int i = 0; i < conList.getLength(); i++) {
			Node con = conList.item(i).cloneNode(false);
			system.adoptNode(con);
			dataConnections.appendChild(con);
		}	
		return dataConnections;
	}
	
	public void removeConnection(String source, String destination) {
		NodeList nList = getApplicationDataConnetions();
		
		for(int i = 0; i < nList.getLength(); i++) {
			String src = nList.item(i).getAttributes().getNamedItem(A_SRC).getNodeValue();
			String dst = nList.item(i).getAttributes().getNamedItem(A_DST).getNodeValue();
			if(src.equals(source) && dst.equals(destination)) {
				Node conToRemove = nList.item(i);
				if(conToRemove.getPreviousSibling().getNodeType() == Node.TEXT_NODE &&
						conToRemove.getPreviousSibling().getNodeValue().trim().length() == 0)
					conToRemove.getParentNode().removeChild(conToRemove.getPreviousSibling());
				conToRemove.getParentNode().removeChild(nList.item(i));
			}
		}
	}
	
	public int getApplicationDataConnetionsCount() {
		Element app = (Element)getSelectedApplication(this.selectedApplication);
		Element dataContag = (Element)app.getElementsByTagName(E_DATA_CONNECTIONS).item(0); //because this is only element
		NodeList nList = dataContag.getElementsByTagName(E_CONNECTION);
		return nList.getLength();
	}
	
	private Element getApplicationDataConnetion(int index) {
		Element app = (Element)getSelectedApplication(this.selectedApplication);
		Element dataContag = (Element)app.getElementsByTagName(E_DATA_CONNECTIONS).item(0);
		Element datCon = (Element) dataContag.getElementsByTagName(E_CONNECTION).item(index);
		return datCon;
	}
	
	private NodeList getApplicationDataConnetions() {
		Element app = (Element)getSelectedApplication(this.selectedApplication);
		Element dataContag = (Element)app.getElementsByTagName(E_DATA_CONNECTIONS).item(0);
		NodeList nList = dataContag.getElementsByTagName(E_CONNECTION);
		return nList;
	}
	
	private Element getSelectedApplication(String selectedApplication) {
		Element application = null;
		Element root = system.getDocumentElement();
		NodeList nList = root.getElementsByTagName(E_APPLICATION);
	
		for(int i = 0; i < nList.getLength(); i++) {
			Node n = nList.item(i);
			if(n.getAttributes().getNamedItem(A_NAME).getNodeValue().equals(selectedApplication)) {
				application = (Element) n;
				break;
			}
		}
		return application;
	}
	
	public String getConnectionCommentValue(int index) {
		return getApplicationDataConnetion(index).getAttribute(A_COMMENT);
	}
	
	public void setConnectionCommentValue(int index, String val) {
		 getApplicationDataConnetion(index).setAttribute(A_COMMENT, val);
	}
	
	private String getSrcAttributeValue(int index) {
		return getApplicationDataConnetion(index).getAttribute(A_SRC);
	}
	
	private String getDstAttributeValue(int index) {
		return getApplicationDataConnetion(index).getAttribute(A_DST);
	}
	
	public String getSrcConnectionFBName(int index) {
			return getSrcAttributeValue(index).split("\\.")[0]; //format of string in xml is FB.Var
	}
	
	public String getDstConnectionFBName(int index) {
		return getDstAttributeValue(index).split("\\.")[0]; //format of string in xml is FB.Var
	}
	
	public String getSrcFBDataVariableName(int index) {
		return getSrcAttributeValue(index).split("\\.")[1]; 
	}
	
	public String getDstFBDataVariableName(int index) {
		return getDstAttributeValue(index).split("\\.")[1]; 
	}
	
	public ArrayList<String> getDeviceNames() {
		ArrayList<String> devices = new ArrayList<String>();
		Element root = system.getDocumentElement();
		NodeList nList = root.getElementsByTagName(E_DEVICE);
		for(int i = 0; i < nList.getLength(); i++) 
			devices.add(nList.item(i).getAttributes().getNamedItem(A_NAME).getNodeValue());
		return devices;
	}
	
	public int getDeviceMappingsCount() {
		Element root = system.getDocumentElement();
		NodeList nList = root.getElementsByTagName(E_MAPPING);
		return nList.getLength();
	}
	
	public String getDeviceMappingFromAtr(int index) {
		String from = null;
		Element root = system.getDocumentElement();
		NodeList nList = root.getElementsByTagName(E_MAPPING);
		if(nList.getLength() > index) {
			from = nList.item(index).getAttributes().getNamedItem(A_FROM).getNodeValue();
		}
		return from;
	}
	
	public String getDeviceMappingToAtr(int index) {
		String to = null;
		Element root = system.getDocumentElement();
		NodeList nList = root.getElementsByTagName(E_MAPPING);
		if(nList.getLength() > index) {
			to = nList.item(index).getAttributes().getNamedItem(A_TO).getNodeValue();
		}
		return to;
	}
	
	public void insertMapping(String devName, String FbName) {
		Element mapping = system.createElement(E_MAPPING); 
		String fromVal = selectedApplication + "." + FbName;
		String toVal = devName + "." + getDeviceResource(devName) + "." + FbName;
		mapping.setAttribute(A_FROM, fromVal);
		mapping.setAttribute(A_TO, toVal);
		Node refNode = system.getElementsByTagName(E_MAPPING).item(FIRST_ELEMENT);
		system.getDocumentElement().insertBefore(mapping, refNode);
	}
	
	public String getDeviceResource(String devName) {
		Element root = system.getDocumentElement();
		NodeList nList = root.getElementsByTagName(E_DEVICE);
		
		for(int i = 0; i < nList.getLength(); i++) {
			if(nList.item(i).getAttributes().getNamedItem(A_NAME).getNodeValue().equals(devName)) {
				return ((Element)nList.item(i)).getElementsByTagName(E_RESOURCE).item(FIRST_ELEMENT).
														getAttributes().getNamedItem(A_NAME).getNodeValue();
			}
		}
		return null; 
	}
	
	public void addMappedConnection(String devName, String source, String destination) {
		Element con = system.createElement(E_CONNECTION);
		con.setAttribute(A_COMMENT, "Secure link source");
		con.setAttribute(A_DST, destination);
		con.setAttribute(A_SRC, source);
		
		Node conCopy = con.cloneNode(false);
		
		addSingleDataConnectionToSelectedApp(con);
		addSingleDataConnectionToDevice(conCopy, devName);
	
		
		//System.out.println(((DOMImplementationLS)system.getImplementation()).createLSSerializer().writeToString(con));
	}
	
	public void saveSysFile() {
		try {
			TransformerFactory transformerFactory = TransformerFactory.newInstance();
			Transformer transformer = transformerFactory.newTransformer();
			if(system != null) {
				DOMSource source = new DOMSource(this.system);
				StreamResult result = new StreamResult(new File(this.sysFile));
				transformer.setOutputProperty(OutputKeys.METHOD, "xml");
				transformer.setOutputProperty(OutputKeys.INDENT, "yes");
				transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "2");
				transformer.transform(source, result); 
				//result.getOutputStream().close();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}
	
	
	public void close() {
		
	}
}
