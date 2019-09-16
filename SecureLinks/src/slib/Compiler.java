package slib;

import securelinks.Connection;

public class Compiler {
	
	private Connection connection;
	
	public Compiler(Connection con) {
		connection = con;
	}
	public void compile() throws Exception {
		
		//line 3 - We already have connections that are mapped on different devices.
		//line 4 - Retrieve sl:sm from SLib
		SlibFBNetwork sfbn = new SlibFBNetwork();
		sfbn.instantiateFBN("SHA1", "abc, cde");
		
		Connection con = new Connection();
		

	}
}
