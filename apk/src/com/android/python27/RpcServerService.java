package com.android.python27;

import android.annotation.TargetApi;
import android.app.Service;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Binder;
import android.os.Build;
import android.os.IBinder;

import com.googlecode.android_scripting.AndroidProxy;

public class RpcServerService extends Service {
  private final IBinder mBinder;

  public class LocalBinder extends Binder {
    public RpcServerService getService() {
      return RpcServerService.this;
    }
  }

  @Override
  public IBinder onBind(Intent intent) {
    return mBinder;
  }

  public RpcServerService() {
    mBinder = new LocalBinder();
  }

  @Override
  public void onCreate() {
    super.onCreate();
  }

  @TargetApi(11)
  @Override
  public void onStart(Intent intent, int startId) {
    super.onStart(intent, startId);

    if (intent.getAction().equals("com.android.python27.LAUNCH_RPC_SERVER")) {
      LaunchServerAsyncTask ll = new LaunchServerAsyncTask(intent);
		if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.HONEYCOMB_MR2) {
			ll.executeOnExecutor(AsyncTask.THREAD_POOL_EXECUTOR, "");
		}
		else {
			ll.execute();	
		}
    }
  }

  private boolean tryPort(AndroidProxy androidProxy, boolean usePublicIp, int usePort) {
    if (usePublicIp) {
      return (androidProxy.startPublic(usePort) != null);
    } else {
      return (androidProxy.startLocal(usePort) != null);
    }
  }

  public class LaunchServerAsyncTask extends AsyncTask<String, Integer, Boolean> {
	  
	  Intent i = null;
	  
	  LaunchServerAsyncTask(Intent intent) {
		this.i = intent;  
	  }
	  
	   @Override
	   protected void onPreExecute() {
	   }

	   @Override
	   protected Boolean doInBackground(String... params) {
		   launchServer(this.i, false);
		   
		   return true;
	   }

	   @Override
	   protected void onProgressUpdate(Integer... values) {
	   }

	   @Override
	   protected void onPostExecute(Boolean installStatus) {
	   }
  
 }
  
  private AndroidProxy launchServer(Intent intent, boolean requiresHandshake) {
	  
    AndroidProxy androidProxy = new AndroidProxy(this, intent, requiresHandshake);
    boolean usePublicIp = false;
    int usePort = intent.getIntExtra("com.android.python27.RPC_SERVER_PORT", 0);
    
    // If port is in use, fall back to defaut behaviour
    if (!tryPort(androidProxy, usePublicIp, usePort)) {
      if (usePort != 0) {
        tryPort(androidProxy, usePublicIp, 0);
      }
    }
    return androidProxy;
  }

}
