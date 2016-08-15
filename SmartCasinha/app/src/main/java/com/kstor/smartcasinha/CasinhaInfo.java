package com.kstor.smartcasinha;

import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.widget.Toast;

/**
 * Created by Kstor on 14/08/2016.
 */
public class CasinhaInfo {
    protected static final void popUp(Context context){
        StringBuilder text = new StringBuilder();
        text.append("Deve-se estar conectado ao mesmo WiFi que os Nodes MCU!\n\n");
        text.append("IPs dos Nodes na rede 'casinha':\n");
        text.append("Quartao:       " + Address.QUARTAO + "\n");
        text.append("Quartinho:    " + Address.QUARTINHO + "\n");
        text.append("Cozinha:       " + Address.COZINHA + "\n");
        text.append("Banheirinho: " + Address.BANHEIRINHO + "\n\n");
        text.append("HTTP PUT <IP>/<COMANDO>\n");
        text.append("Comandos suportados:\n");
        text.append("- SWITCH_STATE\n");

        AlertDialog dialog = new AlertDialog.Builder(context).create();
        dialog.setTitle("Smart Casinha v0.1");
        dialog.setMessage(text.toString());
        dialog.setCancelable(true);
        dialog.setButton(
            "OK",
            new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialog, int id) {
                    Toast.makeText(context, "Informações visualizadas!", Toast.LENGTH_LONG);
                    dialog.cancel();
                }
            });
        dialog.show();
    }
}
