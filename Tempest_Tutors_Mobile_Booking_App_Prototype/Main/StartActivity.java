package w17014748.kf7008.tempesttutors;

import android.content.Intent;
import android.os.Bundle;

import com.google.android.material.tabs.TabLayout;

import androidx.annotation.StringRes;
import androidx.viewpager.widget.ViewPager;
import androidx.appcompat.app.AppCompatActivity;

import android.util.Log;
import android.view.View;

import w17014748.kf7008.tempesttutors.ui.main.SectionsPagerAdapter;


public class StartActivity extends AppCompatActivity implements View.OnClickListener {

    public int[] tabNames = {R.string.tab_text_login, R.string.tab_text_signup};

//    EditText username, password;
//    Button loginButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_start);

        SectionsPagerAdapter sectionsPagerAdapter = new SectionsPagerAdapter(this, getSupportFragmentManager(),
                tabNames, "StartActivity");
        ViewPager viewPager = findViewById(R.id.login_view_pager);
        viewPager.setAdapter(sectionsPagerAdapter);
        TabLayout tabs = findViewById(R.id.login_tabs);
        tabs.setupWithViewPager(viewPager);
//        FloatingActionButton fab = findViewById(R.id.fab);
//
//        fab.setOnClickListener(new View.OnClickListener() {
//            @Override
//            public void onClick(View view) {
//                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH_LONG)
//                        .setAction("Action", null).show();
//            }
//        });

//        // Fragment elements
//        username = (EditText) viewPager.findViewById(R.id.loginUsername);
//        password = (EditText) viewPager.findViewById(R.id.loginPassword);
//        loginButton = (Button) viewPager.findViewById(R.id.loginButton);
    }

    @Override
    public void onClick(View view) {

    }
}