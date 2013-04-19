/*
 * Copyright (C) 2010 Google Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not
 * use this file except in compliance with the License. You may obtain a copy of
 * the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations under
 * the License.
 */

/*
 * Copyright (C) 2012, Anthony Prieur & Daniel Oppenheim. All rights reserved.
 *
 * Original from SL4A modified to allow to embed Interpreter and scripts into an APK
 */

package com.android.python27.process;

import com.android.python27.config.GlobalConstants;
import com.googlecode.android_scripting.AndroidProxy;
import com.googlecode.android_scripting.interpreter.InterpreterConfiguration;

import java.io.File;
import java.util.List;
import java.util.Map;

public class MyScriptProcess extends PythonScriptProcess {

	  private String workingDirectory;
	  private String sdcardPackageDirectory;

	  private MyScriptProcess(File paramFile, InterpreterConfiguration paramInterpreterConfiguration, AndroidProxy paramAndroidProxy, String workingDir, String sdcardPackageDirectory) {
	    super(paramFile, paramInterpreterConfiguration, paramAndroidProxy);
	    this.workingDirectory = workingDir;
	    this.sdcardPackageDirectory = sdcardPackageDirectory;
	  }

	  public static MyScriptProcess launchScript(File script, InterpreterConfiguration configuration, final AndroidProxy proxy, Runnable shutdownHook, String workingDir, String sdcardPackageDirectory, List<String> args, Map<String, String> envVars, File binary) {
	    if (!script.exists()) {
	        throw new RuntimeException("No such script to launch.");
	      }

	    MyScriptProcess localScriptProcess = new MyScriptProcess(script, configuration, proxy, workingDir, sdcardPackageDirectory);
    	localScriptProcess.putAllEnvironmentVariables(envVars); // set our python env var
    	localScriptProcess.setBinary(binary);
	    
	    if (shutdownHook == null) {
	    	localScriptProcess.start(new Runnable() {
	          @Override
	          public void run() {
	            proxy.shutdown();
	          }
	        }, args);
	      } else {
	    	  localScriptProcess.start(shutdownHook, args);
	      }
	      return localScriptProcess;
	    }
	    
	  @Override
	  public String getWorkingDirectory() {
	    return workingDirectory;
	  }

	  @Override
	  public String getSdcardPackageDirectory() {
	    return sdcardPackageDirectory;
	  }
	  
	  
}