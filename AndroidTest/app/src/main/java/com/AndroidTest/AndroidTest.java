
package com.AndroidTest;

import android.app.Activity;
import android.widget.TextView;
import android.os.Bundle;

public class AndroidTest extends Activity
{
    /** �۾��� ó�� ������� �� ȣ��˴ϴ�. */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        /* TextView�� ����� �ؽ�Ʈ�� "Hello world"�� �����մϴ�.*/
        TextView  tv = new TextView(this);
        tv.setText("Hello World!");
        setContentView(tv);
    }
}
