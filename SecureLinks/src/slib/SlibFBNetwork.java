package slib;

import java.util.List;

public class SlibFBNetwork {
	
	public String fbName;
	
	public class In {
		public String inFbDef;
		public String inVar;
		public String inVarType;
	}
	
	public class Out {
		public String outFbDef;
		public String outVar;
		public String outVarType;
	}
	
	public class Params {
		String paramName;
		String paramType;
		String paramValue;
	}
	
	private List<Params> paramsList;
}
