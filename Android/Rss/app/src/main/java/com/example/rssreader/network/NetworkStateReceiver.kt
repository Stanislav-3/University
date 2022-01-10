package com.example.rssreader.network

import android.content.BroadcastReceiver
import android.content.Context
import android.content.Intent
import android.net.ConnectivityManager
import android.widget.Toast

class NetworkStateReceiver: BroadcastReceiver() {

    override fun onReceive(context: Context?, intent: Intent?) {
        if (isConnectedOrConnecting(context)) {
            Toast.makeText(context, "Connected to the Internet!", Toast.LENGTH_LONG).show()
        } else {
            Toast.makeText(context, "No Internet connection!", Toast.LENGTH_LONG).show()
        }
    }

    public fun isConnectedOrConnecting(context: Context?): Boolean {
        val manager = context?.getSystemService(Context.CONNECTIVITY_SERVICE) as ConnectivityManager
        val networkInfo = manager.activeNetworkInfo
        return networkInfo?.isConnectedOrConnecting?:false
    }

}