package com.siradze.workingwithc

import android.content.res.AssetManager
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.siradze.workingwithc.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setAssetManager(assets)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
    }



    companion object {
        // Used to load the 'workingwithc' library on application startup.
        init {
            System.loadLibrary("workingwithc")
        }
        private external fun setAssetManager(assetManager: AssetManager)
    }
}