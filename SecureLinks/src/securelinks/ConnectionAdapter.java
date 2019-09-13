package securelinks;

import java.util.ArrayList;
import java.util.List;
import java.util.regex.Pattern;
import java.util.stream.Collectors;


public class ConnectionAdapter {
	
	private SysFileOperator sysReaderWriter;
	private String selectedApplication;
	
	private final String SECURE_LINK_REGEX = "@[sS][lL]\\s*\\((\\s*\\w*\\s*,\\s*\\w*\\s*,)\\s*\\w+\\s*\\)";
	
	public ConnectionAdapter() {

	}
	
	public boolean loadSystem(String xmlFile, String selectedApplication) {
		this.sysReaderWriter = new SysFileOperator(xmlFile, selectedApplication);
		if(this.sysReaderWriter != null) {
			this.selectedApplication = selectedApplication;
			return true; 
		}
		else return false;
	}
	
	public List<Connection> getDataConnections() {
		
		List <Connection> connections = new ArrayList<Connection>();
		List <DeviceMappings> mappings = getDeviceMappings().stream() //filtering mappings that belong to the selected application
				.filter(m->m.from.split("\\.")[0].equals(this.selectedApplication)).collect(Collectors.toList());
		int numDataConnections = sysReaderWriter.getApplicationDataConnetionsCount();
		
		for(int i = 0; i < numDataConnections; i++) {
			Connection con = new Connection();
	    	con.setSourceFB(sysReaderWriter.getSrcConnectionFBName(i));
	    	con.setDestinationeFB(sysReaderWriter.getDstConnectionFBName(i));
	    	con.setSourceVariable(sysReaderWriter.getSrcFBDataVariableName(i));
	    	con.setDestinationVariable(sysReaderWriter.getDstFBDataVariableName(i));
	    	con.setConnectionComment(sysReaderWriter.getConnectionCommentValue(i));
	    	
	    	for(DeviceMappings map : mappings) {
	    		if(map.from.split("\\.")[1].equals(con.getSourceFB()))
	    			con.setSourceFBDevice(map.to.split("\\.")[0]);
	    		if(map.from.split("\\.")[1].equals(con.getDestinationFB()))
	    			con.setDestinationFBDevice(map.to.split("\\.")[0]);
	    	}

	    	connections.add(con);
	    	//System.out.println(con.outFB +"."+ con.outVariable+"--->"+con.inFB+"."+ con.inVariable);
	    }
		    
		return connections;
	}
	
	public List<DeviceMappings> getDeviceMappings() {
		
		List<DeviceMappings> mappingsList = new ArrayList<DeviceMappings>();
		int numOfMappings = sysReaderWriter.getDeviceMappingsCount();
		
		for(int i = 0; i < numOfMappings; i++) {
			DeviceMappings mapping = new DeviceMappings();
			mapping.from = sysReaderWriter.getDeviceMappingFromAtr(i);
			mapping.to = sysReaderWriter.getDeviceMappingToAtr(i);
			mappingsList.add(mapping);
		}
		return mappingsList;
	}
	
	public List<Connection> getInterDeviceDataConnections() {
		
		List <Connection> connections = getDataConnections();
		List <Connection> interDevConns = new ArrayList<Connection>();
		for(Connection con : connections) {
			if(!con.getSourceFBDevice().equals(con.getDestinationFBDevice()))
				interDevConns.add(con);
		}
		return interDevConns;
	}
	
	public void UpdateConnections(List<Connection> conList) {
		
		List <Connection> sysFileCons = getInterDeviceDataConnections();
		
		//Assuming that connections will be the same in existing system file 
		//and the modified connection list obtained from GUI
		for(int i = 0; i < sysFileCons.size(); i++) {
			Connection sysFileCon = sysFileCons.get(i);
			Connection updatedCon = conList.get(i);
			if(sysFileCon.getSourceFB().equals(updatedCon.getSourceFB()) &&
					sysFileCon.getDestinationFB().equals(updatedCon.getDestinationFB()))	 {
				sysReaderWriter.setConnectionCommentValue(i, updatedCon.getConnectionComment());
			}
		}
		
		sysReaderWriter.saveSysFile();
	}
	
	public boolean isValidSecureLink(Connection c) {
		if(Pattern.compile(SECURE_LINK_REGEX).matcher(c.getConnectionComment()).find()) 
			return true;
		else
			return false;
	}
}
