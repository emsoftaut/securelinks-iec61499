package securelinks;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import javax.swing.text.StyledEditorKit.ForegroundAction;
import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

/*
 * This class reads the .sys xml file for a system. 
 * For now, it only supports 4DIAC 1.10.3 or the versions that use HOLOBLOC DTD  
 */
public class SysFileReader {
	
	private static final NullPointerException NullPointerException = null;
	private static final String E_DATA_CONNECTIONS = "DataConnections";
	private static final String E_CONNECTION = "Connection";
	private static final String E_APPLICATION = "Application";
	private static final String E_DEVICE = "Device";
	private static final String E_MAPPING = "Mapping";
	private static final String A_SRC = "Source";
	private static final String A_DST = "Destination";
	private static final String A_NAME = "Name";
	private static final String A_FROM = "From";
	private static final String A_TO = "To";
	
	
	private String sysFile = null;
	private Document system = null;
	private String selectedApplication = null;
	
	
	private Document getRoot() throws NullPointerException {
		if(system == null)
			throw NullPointerException;
		return this.system;
	}
	
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
	
	public SysFileReader(String sysFile, String application ) {
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
	
	public int getApplicationDataConnetionsCount() {
		Element app = (Element)getSelectedApplication(this.selectedApplication);
		Element dataContag = (Element)app.getElementsByTagName(E_DATA_CONNECTIONS).item(0);
		NodeList nList = dataContag.getElementsByTagName(E_CONNECTION);
		return nList.getLength();
	}
	
	public Element getApplicationDataConnetion(int index) {
		Element app = (Element)getSelectedApplication(this.selectedApplication);
		Element dataContag = (Element)app.getElementsByTagName(E_DATA_CONNECTIONS).item(0);
		Element datCon = (Element) dataContag.getElementsByTagName(E_CONNECTION).item(index);
		return datCon;
	}
	
	public NodeList getApplicationDataConnetions() {
		Element app = (Element)getSelectedApplication(this.selectedApplication);
		Element dataContag = (Element)app.getElementsByTagName(E_DATA_CONNECTIONS).item(0);
		NodeList nList = dataContag.getElementsByTagName(E_CONNECTION);
		return nList;
	}
	
	public Element getSelectedApplication(String selectedApplication) {
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
	
}
