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

package com.android.python27;

import android.content.Context;

import com.googlecode.android_scripting.BaseApplication;
import com.googlecode.android_scripting.interpreter.InterpreterConfiguration.ConfigurationObserver;

public class ScriptApplication extends BaseApplication implements ConfigurationObserver {

//  private volatile boolean receivedConfigUpdate = false;
//  private final CountDownLatch mLatch = new CountDownLatch(1);

  private static Context context = null;
  private static String thePackageName = null;
  private static String theFilesDir = null;

  // ------------------------------------------------------------------------------------------------------

  public static Context getAppContext() {
      return ScriptApplication.context;
  }

  public static String getThePackageName() {
	  return thePackageName;
  }
	
  public static String getTheFilesDir() {
	  return theFilesDir;
  }

  // ------------------------------------------------------------------------------------------------------

  @Override
  public void onCreate() {
//    mConfiguration = new InterpreterConfiguration(this);
//    mConfiguration.registerObserver(this);
//    mConfiguration.startDiscovering(InterpreterConstants.MIME + Utils.getFileExtension("foo.py"));
		
	  // dirty way to access some needed info in GlobalConstants
	  ScriptApplication.context = getApplicationContext();
	  ScriptApplication.theFilesDir = this.getFilesDir().getAbsolutePath();
	  ScriptApplication.thePackageName = this.getPackageName();
  } 

@Override
  public void onConfigurationChanged() {
//	receivedConfigUpdate = true;
//	mLatch.countDown();
  }

//  public boolean readyToStart() {
//
//    try {
//      mLatch.await();
//    } catch (InterruptedException e) {
//      e.printStackTrace();
//    }
//
//    return receivedConfigUpdate;
//  }

}
