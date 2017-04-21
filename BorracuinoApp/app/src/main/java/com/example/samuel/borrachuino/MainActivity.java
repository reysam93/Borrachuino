package com.example.samuel.borrachuino;

import android.content.Context;
import android.content.SharedPreferences;
import android.os.Bundle;

import android.os.StrictMode;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.util.Log;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.Toast;

import java.io.PrintStream;
import java.net.InetAddress;

import java.io.IOException;
import java.net.Socket;


public class MainActivity extends AppCompatActivity {

    private String TAG = "BORRACHUINO";

    private Socket mSocket;
    private EditText mIp;
    private EditText mPort;
    private Button mConnect;
    private Button mServeDrink;

    private CheckBox mIce;
    private RadioButton mShot;
    private RadioButton mShortDrink;
    private RadioButton mNormalDrink;
    private RadioButton mLongDrink;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        mIp = (EditText) findViewById(R.id.ip);
        mPort = (EditText) findViewById(R.id.port);
        mConnect = (Button) findViewById(R.id.create_socket);
        mServeDrink = (Button) findViewById(R.id.serve_drink);

        mShortDrink = (RadioButton) findViewById(R.id.short_drink);
        mNormalDrink = (RadioButton) findViewById(R.id.normal_drink);
        mLongDrink = (RadioButton) findViewById(R.id.long_drink);
        mShot = (RadioButton) findViewById(R.id.shot);
        mIce = (CheckBox) findViewById(R.id.ice);

        //initConfigParams();

        StrictMode.setThreadPolicy(new StrictMode.ThreadPolicy.Builder()
                .permitNetwork().build());


        mConnect.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // destroy old socket?
                connectToSocket();
                saveConfig();
            }
        });

        mServeDrink.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (mSocket == null || !mSocket.isConnected()) {
                    Toast.makeText(getApplicationContext(), "Connect to the server first!",
                            Toast.LENGTH_LONG).show();
                    return;
                }
                try {
                    PrintStream output = new PrintStream(mSocket.getOutputStream());
                    String msg = "";

                    // drink type
                    if (mShot.isChecked()){
                        msg = "drink:0 ";
                    } else if (mShortDrink.isChecked()) {
                        msg = "drink:1 ";
                    } else if (mNormalDrink.isChecked()) {
                        msg = "drink:2 ";
                    } else if (mLongDrink.isChecked()) {
                        msg = "drink:3 ";
                    }

                    // ice
                    if (mIce.isChecked()) {
                        msg += "ice:1\n";
                    } else {
                        msg += "ice:0\n";
                    }
                    output.print(msg);
                } catch (IOException ex) {
                    Log.e(TAG, "" + ex.getMessage());
                }
            }
        });


    }

    /**
     * Load previosly saved configuration.
     * If non configration is already server, uses default parameters
     */
    private void initConfigParams(){
        SharedPreferences sharedPref = getPreferences(Context.MODE_PRIVATE);
        String ip = sharedPref.getString(getString(R.string.ip_key_val),
                getString(R.string.default_ip));
        String port = sharedPref.getString(getString(R.string.port_key),
                getString(R.string.default_port));
        mIp.setText(ip);
        mPort.setText(port);
    }

    /**
     * Save configuration parameters for connecting to the socket
     */
    private void saveConfig() {
        SharedPreferences sharedPref = getPreferences(Context.MODE_PRIVATE);
        SharedPreferences.Editor editor = sharedPref.edit();
        editor.putString(getString(R.string.ip_key_val), mIp.getText().toString());
        editor.putString(getString(R.string.port_key), mPort.getText().toString());
        editor.apply();
    }

    /**
     * Connects with the socket server
     */
    private void connectToSocket() {
        String text = "";
        String ip = "";
        int port = 0;

        try {
            ip = mIp.getText().toString();
            port = new Integer(mPort.getText().toString());
            mSocket = new Socket(ip, port);
            text = "Connected to " + ip + ":" + port;
            Log.i(TAG, text);
            Toast.makeText(getApplicationContext(), text, Toast.LENGTH_SHORT).show();
        } catch (IOException ex) {
            text = "Not connected to " + ip + ":" + port;
            Toast.makeText(getApplicationContext(), text, Toast.LENGTH_LONG).show();
            Log.e(TAG, "" + ex.getMessage());
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }
}
