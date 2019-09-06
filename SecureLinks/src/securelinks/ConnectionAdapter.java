package securelinks;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;


public class ConnectionAdapter {
	
	private SysFileReader xmlReader;
	private String selectedApplication;
	
	public ConnectionAdapter() {

	}
	
	public boolean loadSystem(String xmlFile, String selectedApplication) {
		this.xmlReader = new SysFileReader(xmlFile, selectedApplication);
		if(this.xmlReader != null) {
			this.selectedApplication = selectedApplication;
			return true; 
		}
		else return false;
	}
	
	public List<Connection> getDataConnections() {
		
		List <Connection> connections = new ArrayList<Connection>();
		List <DeviceMappings> mappings = getDeviceMappings().stream() //filtering mappings that belong to the selected application
				.filter(m->m.from.split("\\.")[0].equals(this.selectedApplication)).collect(Collectors.toList());
		int numDataConnections = xmlReader.getApplicationDataConnetionsCount();
		
		for(int i = 0; i < numDataConnections; i++) {
			Connection con = new Connection();
	    	con.outFB = xmlReader.getSrcConnectionFBName(i);
	    	con.inFB = xmlReader.getDstConnectionFBName(i);
	    	con.outVariable = xmlReader.getSrcFBDataVariableName(i);
	    	con.inVariable = xmlReader.getDstFBDataVariableName(i);
	    	con.connectionComment = xmlReader.getConnectionCommentValue(i);
	    	
	    	for(DeviceMappings map : mappings) {
	    		if(map.from.split("\\.")[1].equals(con.outFB))
	    			con.outFBDevice = map.to.split("\\.")[0];
	    		if(map.from.split("\\.")[1].equals(con.inFB))
	    			con.inFBDevice = map.to.split("\\.")[0];
	    	}

	    	connections.add(con);
	    	//System.out.println(con.outFB +"."+ con.outVariable+"--->"+con.inFB+"."+ con.inVariable);
	    }
		    
		return connections;
	}
	
	public List<DeviceMappings> getDeviceMappings() {
		
		List<DeviceMappings> mappingsList = new ArrayList<DeviceMappings>();
		int numOfMappings = xmlReader.getDeviceMappingsCount();
		
		for(int i = 0; i < numOfMappings; i++) {
			DeviceMappings mapping = new DeviceMappings();
			mapping.from = xmlReader.getDeviceMappingFromAtr(i);
			mapping.to = xmlReader.getDeviceMappingToAtr(i);
			mappingsList.add(mapping);
		}
		return mappingsList;
	}
	
	public List<Connection> getInterDeviceDataConnections() {
		
		List <Connection> connections = getDataConnections();
		List <Connection> interDevConns = new ArrayList<Connection>();
		for(Connection con : connections) {
			if(!con.outFBDevice.equals(con.inFBDevice))
				interDevConns.add(con);
		}
		return interDevConns;
	}
	
	public void UpdateConnections(List<Connection> conList) {
		//Yahan say shuru karna hai.
	}
}
