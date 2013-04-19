package com.googlecode.android_scripting.interpreter;

import java.util.List;

public class MyInterpreter {

	private Interpreter interpreter;
	
	public MyInterpreter(Interpreter interpreter){
		this.interpreter = interpreter;
	}
	
	public Interpreter getInterpreter() {
		return this.interpreter;
	}
	
	public List<String> getArguments() {
		return interpreter.getArguments();
	}
	
}
