package slib;

import java.util.ArrayList;
import java.util.List;
import java.util.regex.Pattern;

import securelinks.Connection;
import securelinks.ConnectionAdapter;
import securelinks.SysFileOperator;

public class SlibHandler {
	
	private final String SECURE_LINK_REGEX = "@[sS][lL]\\s*\\((\\s*\\w*\\s*,\\s*\\w*\\s*,)\\s*\\w+\\s*\\)";
	
	public void loadSecureLinks(String sysFile, String selectedApp) {
		
		ConnectionAdapter adapt = new ConnectionAdapter();
		if(adapt.loadSystem(sysFile, selectedApp)) {
			List<Connection> secureLinkList = new ArrayList<Connection>();
			List<Connection> conList = adapt.getInterDeviceDataConnections();
			
			for(Connection con : conList) {
				if(Pattern.compile(SECURE_LINK_REGEX).matcher(con.connectionComment).find()) {
					secureLinkList.add(con);
				}
			}
		}
	}
}
