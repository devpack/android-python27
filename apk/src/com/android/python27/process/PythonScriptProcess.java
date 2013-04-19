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

import android.util.Log;

import com.googlecode.android_scripting.AndroidProxy;
import com.googlecode.android_scripting.interpreter.InterpreterConfiguration;
import com.googlecode.android_scripting.interpreter.MyInterpreter;

import java.io.File;

public class PythonScriptProcess extends InterpreterProcess
{
  private final File mScript;

  public PythonScriptProcess(File paramFile, InterpreterConfiguration paramInterpreterConfiguration, AndroidProxy paramAndroidProxy) {
    super(new MyInterpreter( null ) , paramAndroidProxy);
    this.mScript = paramFile;
    setName(paramFile.getName());
    
    String str = "";
//    if(paramInterpreterConfiguration.getInterpreterForScript("foo.py") != null) {
//    	str = paramInterpreterConfiguration.getInterpreterForScript("foo.py").getScriptCommand();
//    }
    Object[] arrayOfObject = new Object[1];
    arrayOfObject[0] = paramFile.getAbsolutePath();
    setCommand(String.format(str, arrayOfObject));
  }

  public String getPath() {
    return this.mScript.getPath();
  }
}