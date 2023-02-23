package w17014748.kf7008.tempesttutors;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;
import androidx.viewpager.widget.ViewPager;

import com.google.android.material.snackbar.Snackbar;
import com.google.android.material.tabs.TabLayout;

import w17014748.kf7008.tempesttutors.ui.main.SectionsPagerAdapter;


public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    public int[] tabNames = {R.string.tab_text_home, R.string.tab_text_bookings,
            R.string.tab_text_account};

    @Override
    public void onCreate(@Nullable Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        SectionsPagerAdapter sectionsPagerAdapter = new SectionsPagerAdapter(this, getSupportFragmentManager(),
                tabNames, "MainActivity");
        ViewPager viewPager = findViewById(R.id.main_view_pager);
        viewPager.setAdapter(sectionsPagerAdapter);
        TabLayout tabs = findViewById(R.id.menu_tabs);
        tabs.setupWithViewPager(viewPager);

        Intent intent = getIntent();
        String user = intent.getStringExtra("username");

        Toast.makeText(this, "Welcome " + user, Toast.LENGTH_SHORT).show();
    }

    @Override
    public void onClick(View v) {

    }
}
