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

package com.android.python32;

import android.app.Notification;
import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Binder;
import android.os.Environment;
import android.os.Handler;
import android.os.IBinder;
import android.util.Log;

import com.android.python32.R;
import com.android.python32.config.GlobalConstants;
import com.android.python32.process.MyScriptProcess;
import com.googlecode.android_scripting.AndroidProxy;
import com.googlecode.android_scripting.Constants;
import com.googlecode.android_scripting.FeaturedInterpreters;
import com.googlecode.android_scripting.ForegroundService;
import com.googlecode.android_scripting.NotificationIdFactory;
import com.googlecode.android_scripting.interpreter.Interpreter;
import com.googlecode.android_scripting.jsonrpc.RpcReceiverManager;
import com.googlecode.android_scripting.interpreter.InterpreterConfiguration;
import com.googlecode.android_scripting.BaseApplication;

import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.CountDownLatch;

public class ScriptService extends ForegroundService {
	private final static int NOTIFICATION_ID = NotificationIdFactory.create();
	private final CountDownLatch mLatch = new CountDownLatch(1);
	private final IBinder mBinder;
	private MyScriptProcess myScriptProcess;
	
	private static ScriptService instance;
	private boolean killMe;
	  
	private InterpreterConfiguration mInterpreterConfiguration = null;
	private RpcReceiverManager mFacadeManager;
    private AndroidProxy mProxy;
    
    private static Context context = null;
    static {
      instance = null;
    }
    
    // ------------------------------------------------------------------------------------------------------

	public class LocalBinder extends Binder {
		public ScriptService getService() {
			return ScriptService.this;
		}
	}

    // ------------------------------------------------------------------------------------------------------

	@Override
	public void onDestroy() {
		super.onDestroy();
	}

    // ------------------------------------------------------------------------------------------------------

	public ScriptService() {
		super(NOTIFICATION_ID);
		mBinder = new LocalBinder();
	}

    // ------------------------------------------------------------------------------------------------------

	@Override
	public IBinder onBind(Intent intent) {
		return mBinder;
	}

    // ------------------------------------------------------------------------------------------------------

    public static Context getAppContext() {
        return ScriptService.context;
    }
    
    // ------------------------------------------------------------------------------------------------------

	@Override
	public void onCreate() {
		super.onCreate();
		ScriptService.context = getApplicationContext();
	}

    // ------------------------------------------------------------------------------------------------------

	private void killProcess() {
		this.killMe = true;
	    instance = null;
	    if (myScriptProcess != null) {
	    	myScriptProcess.kill();
	    }
	}

    // ------------------------------------------------------------------------------------------------------
	
	@Override
	public void onStart(Intent intent, final int startId) {
		super.onStart(intent, startId);
		
		killProcess();
		
		instance = this;
	    this.killMe = false;

		new startMyAsyncTask().execute(startId);
	}

    // ------------------------------------------------------------------------------------------------------

	  public class startMyAsyncTask extends AsyncTask<Integer, Integer, Boolean> {
		   @Override
		   protected void onPreExecute() {
		   }
	
		   @Override
		   protected Boolean doInBackground(Integer... params) {	    
			   startMyMain(params[0]);
			   
			   // TODO
			   return true;
		   }
	
		   @Override
		   protected void onProgressUpdate(Integer... values) {
		   }
	
		   @Override
		   protected void onPostExecute(Boolean installStatus) {
		   }
	   
	  }

	// ------------------------------------------------------------------------------------------------------

	private void startMyMain(final int startId) {

		String scriptName = GlobalConstants.PYTHON_MAIN_SCRIPT_NAME;
		scriptName = this.getFilesDir().getAbsolutePath() + "/" + scriptName;
		File script = new File(scriptName);
		
		// arguments
		ArrayList<String> args = new ArrayList<String>();
		args.add(scriptName);
		args.add("--foreground");

		File pythonBinary = new File(this.getFilesDir().getAbsolutePath() + "/python3/bin/python3");

		// env var
		Map<String, String> environmentVariables = null;	
		environmentVariables = new HashMap<String, String>();
		environmentVariables.put("PYTHONPATH", Environment.getExternalStorageDirectory().getAbsolutePath()+ "/" + this.getPackageName() + "/extras/python3" + ":" + this.getFilesDir().getAbsolutePath() + "/python3/lib/python3.2/lib-dynload" + ":" + this.getFilesDir().getAbsolutePath() + "/python3/lib/python3.2");		
		environmentVariables.put("TEMP", Environment.getExternalStorageDirectory().getAbsolutePath() + "/" + this.getPackageName() + "/extras/tmp");		
		environmentVariables.put("PYTHONHOME", this.getFilesDir().getAbsolutePath() + "/python3");		
		environmentVariables.put("LD_LIBRARY_PATH", this.getFilesDir().getAbsolutePath() + "/python3/lib" + ":" + this.getFilesDir().getAbsolutePath() + "/python3/lib/python3.2/lib-dynload");		
		
		// launch script
		mProxy = new AndroidProxy(this, null, true);
		mProxy.startLocal();
		mLatch.countDown();
	      
		myScriptProcess = MyScriptProcess.launchScript(script, mInterpreterConfiguration, mProxy, new Runnable() {
					@Override
					public void run() {
						//mProxy.shutdown();
						//stopSelf(startId);
						
						// hard force restart
//				        if (!ScriptService.this.killMe) {
//				        	startMyMain();				        	
//				        }

					}
				}, script.getParent(),  Environment.getExternalStorageDirectory().getAbsolutePath() + "/" + this.getPackageName(), args, environmentVariables, pythonBinary);		
	}
	
    // ------------------------------------------------------------------------------------------------------

	RpcReceiverManager getRpcReceiverManager() throws InterruptedException {
		mLatch.await();
		
		if (mFacadeManager==null) { // Facade manage may not be available on startup.
		mFacadeManager = mProxy.getRpcReceiverManagerFactory()
		.getRpcReceiverManagers().get(0);
		}
		return mFacadeManager;
	}

    // ------------------------------------------------------------------------------------------------------

	@Override
	protected Notification createNotification() {
	    Notification notification =
	        new Notification(R.drawable.icon, this.getString(R.string.loading), System.currentTimeMillis());
	    // This contentIntent is a noop.
	    PendingIntent contentIntent = PendingIntent.getService(this, 0, new Intent(), 0);
	    notification.setLatestEventInfo(this, this.getString(R.string.app_name), this.getString(R.string.loading), contentIntent);
	    notification.flags = Notification.FLAG_AUTO_CANCEL;
		return notification;
	}

	
}