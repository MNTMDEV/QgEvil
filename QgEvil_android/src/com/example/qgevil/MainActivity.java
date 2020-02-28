package com.example.qgevil;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.EditText;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		Button btnCreate=(Button)findViewById(R.id.button1);
		btnCreate.setOnClickListener(new OnClickListener()
				{

					@Override
					public void onClick(View v) {
						// TODO Auto-generated method stub
						EditText tvName=(EditText)findViewById(R.id.editText1);
						EditText tvAft=(EditText)findViewById(R.id.editText2);
						EditText tvRes=(EditText)findViewById(R.id.editText3);
						String strName=tvName.getText().toString();
						String strAft=tvAft.getText().toString();
						tvRes.setText(getResult(strName,strAft));
					}
				});
		Button btnClear=(Button)findViewById(R.id.button2);
		btnClear.setOnClickListener(new OnClickListener(){

			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				EditText tvRes=(EditText)findViewById(R.id.editText3);
				tvRes.setText("");
			}
		
		});
	}
	private String getResult(String Name,String Aft)
	{
		StringBuffer buf=new StringBuffer(Aft);
		return Name+"\u202e"+buf.reverse()+"\u202d";
	}
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		//int id = item.getItemId();
		//if (id == R.id.action_settings) {
			//return true;
		//}
		return super.onOptionsItemSelected(item);
	}
}
