package com.googlecode.android_scripting.facade;

import android.util.Log;

import com.android.python27.config.GlobalConstants;
import com.googlecode.android_scripting.facade.FacadeManager;
import com.googlecode.android_scripting.jsonrpc.RpcReceiver;
import com.googlecode.android_scripting.rpc.Rpc;
import com.googlecode.android_scripting.rpc.RpcMinSdk;
import com.googlecode.android_scripting.rpc.RpcParameter;

import java.util.concurrent.CountDownLatch;

@RpcMinSdk(4)
public class ACustomFacade extends RpcReceiver {
	  
  private final CountDownLatch mOnInitLock;

  public ACustomFacade(FacadeManager manager) {
    super(manager);
    mOnInitLock = new CountDownLatch(1);
    mOnInitLock.countDown();
  }

  public void shutdown() {
  }

  // Usage example from Python code:
  // 
  // import android
  // droid = android.Android()
  // droid.aHelloFonction("hello rpc")
  @Rpc(description = "Print hello in logcat")
  public void aHelloFonction(@RpcParameter(name = "message") String message) throws InterruptedException {
    mOnInitLock.await();
    Log.i(GlobalConstants.LOG_TAG, "ACustomFacade received: " + message);
  }
}