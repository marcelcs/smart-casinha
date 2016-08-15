package com.kstor.smartcasinha;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;
import android.os.AsyncTask;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.concurrent.TimeUnit;

/**
 * Created by Kstor on 14/08/2016.
 */

public class LightSwitch extends AsyncTask<String, Void, Void> {

    private final Context context;
    private String location;
    private String address;
    private ProgressDialog progress;
    private Boolean success;

    public LightSwitch(Context c, String location){
        this.context = c;
        this.location = location;
        this.success = true;
    }

    @Override
    protected void onPreExecute(){
        progress = new ProgressDialog(this.context);
        progress.setMessage("Loading");
        progress.show();
    }

    @Override
    protected Void doInBackground(String... params) {
        try {

            if (this.location.equals("Quartao")){
                this.address = Address.QUARTAO_IP;
            } else if (this.location.equals("Quartinho")) {
                this.address = Address.QUARTINHO_IP;
            } else if (this.location.equals("Cozinha")){
                this.address = Address.COZINHA_IP;
            } else if (this.location.equals("Banheirinho")){
                this.address = Address.BANHEIRINHO_IP;
            } else {
                Toast.makeText(this.context, "Local inválido!", Toast.LENGTH_LONG).show();
                return null;
            }

            URL url = new URL(this.address);
            this.success = true;

            HttpURLConnection connection = (HttpURLConnection)url.openConnection();
            connection.setRequestMethod("PUT");

            int responseCode = connection.getResponseCode();

            System.out.println("\nSending 'PUT' request to URL : " + url);
            System.out.println("Response Code : " + responseCode);

            final StringBuilder output = new StringBuilder("Request URL " + url);
            //output.append(System.getProperty("line.separator") + "Request Parameters " + urlParameters);
            output.append(System.getProperty("line.separator")  + "Response Code " + responseCode);
            output.append(System.getProperty("line.separator")  + "Type " + "PUT");
            BufferedReader br = new BufferedReader(new InputStreamReader(connection.getInputStream()));
            String line = "";
            StringBuilder responseOutput = new StringBuilder();
            System.out.println("output===============" + br);
            while((line = br.readLine()) != null ) {
                responseOutput.append(line);
            }
            br.close();

            output.append(System.getProperty("line.separator") + "Response " + System.getProperty("line.separator") + System.getProperty("line.separator") + responseOutput.toString());

            Activity controlPanel = (Activity) this.context;
            controlPanel.runOnUiThread(new Runnable() {
                @Override
                public void run() {
                    System.out.println(output);
                    progress.dismiss();
                }
            });

        } catch (Exception e) {
            this.success = false;
            //e.printStackTrace();
        } finally {
            if ( progress!=null && progress.isShowing() ){
                progress.cancel();
            }
        }

        return null;
    }

    @Override
    protected void onPostExecute(Void stuff){
        Activity screen = (Activity)this.context;
        if (this.success) {
            Toast.makeText(screen, this.location+": Estado Trocado!", Toast.LENGTH_LONG).show();
        } else {
            Toast.makeText(screen, this.location+": Alguma coisa deu errado", Toast.LENGTH_LONG).show();
            this.success = true;
        }
    }

}