package com.kstor.smartcasinha;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

public class ControlPanel extends Activity {

    public static boolean success;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.success = true;
        setContentView(R.layout.activity_control_panel);
    }

    public void switchQuartao(View view) {
        new LightSwitch(ControlPanel.this, "Quartao").execute();
    }

    public void switchQuartinho(View view) {
        new LightSwitch(ControlPanel.this, "Quartinho").execute();
    }

    public void switchCozinha(View view) {
        new LightSwitch(ControlPanel.this, "Cozinha").execute();
    }

    public void switchBanheirinho(View view) {
        new LightSwitch(ControlPanel.this, "Banheirinho").execute();
    }

    public void showInfo(View view) {
        CasinhaInfo.popUp(ControlPanel.this);
        Toast.makeText(ControlPanel.this, "Exibindo informações", Toast.LENGTH_LONG);
    }
}
