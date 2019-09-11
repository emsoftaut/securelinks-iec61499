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
	    	con.outFB = sysReaderWriter.getSrcConnectionFBName(i);
	    	con.inFB = sysReaderWriter.getDstConnectionFBName(i);
	    	con.outVariable = sysReaderWriter.getSrcFBDataVariableName(i);
	    	con.inVariable = sysReaderWriter.getDstFBDataVariableName(i);
	    	con.connectionComment = sysReaderWriter.getConnectionCommentValue(i);
	    	
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
			if(!con.outFBDevice.equals(con.inFBDevice))
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
			if(sysFileCon.outFB.equals(updatedCon.outFB) &&
					sysFileCon.inFB.equals(updatedCon.inFB))	 {
				sysReaderWriter.setConnectionCommentValue(i, updatedCon.connectionComment);
			}
		}
		
		sysReaderWriter.saveSysFile();
	}
	
	public boolean isValidSecureLink(Connection c) {
		if(Pattern.compile(SECURE_LINK_REGEX).matcher(c.connectionComment).find()) 
			return true;
		else
			return false;
	}
}
