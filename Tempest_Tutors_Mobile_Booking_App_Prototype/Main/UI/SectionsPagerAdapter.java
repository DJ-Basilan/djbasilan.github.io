package w17014748.kf7008.tempesttutors.ui.main;

import android.content.Context;

import androidx.annotation.Nullable;
import androidx.annotation.StringRes;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentPagerAdapter;

import w17014748.kf7008.tempesttutors.R;
import w17014748.kf7008.tempesttutors.LoginFragment;
import w17014748.kf7008.tempesttutors.SignUpFragment;
import w17014748.kf7008.tempesttutors.HomeFragment;
import w17014748.kf7008.tempesttutors.BookingsFragment;
import w17014748.kf7008.tempesttutors.AccountFragment;

/**
 * A [FragmentPagerAdapter] that returns a fragment corresponding to
 * one of the sections/tabs/pages.
 */
public class SectionsPagerAdapter extends FragmentPagerAdapter {

    @StringRes
    private static int[] TAB_TITLES = {};
    private final Context mContext;

    private int count = 0;
    String activityName;

    public SectionsPagerAdapter(Context context, FragmentManager fm, int[] tabs, String activityName) {
        super(fm);
        mContext = context;

        // Changed the original constructor to allow for tabs to be defined in the Activity classes
        count = tabs.length;
        TAB_TITLES = tabs;
        this.activityName = activityName;
    }

    @Override
    public Fragment getItem(int position) {
        // getItem is called to instantiate the fragment for the given page.
        // Return a PlaceholderFragment (defined as a static inner class below).
        Fragment fragment = null;

        if(activityName.equals("StartActivity")) {
            switch (position) {
                case 0:
                    fragment = new LoginFragment();
                    break;
                case 1:
                    fragment = new SignUpFragment();
                    break;
            }
        }
        if(activityName.equals("MainActivity")) {
            switch (position) {
                case 0:
                    fragment = new HomeFragment();
                    break;
                case 1:
                    fragment = new BookingsFragment();
                    break;
                case 2:
                    fragment = new AccountFragment();
                    break;
            }
        }
        return fragment;
    }

    @Nullable
    @Override
    public CharSequence getPageTitle(int position) {
        return mContext.getResources().getString(TAB_TITLES[position]);
    }

    @Override
    public int getCount() {
        // Show 2 total pages.
        return count;
    }
}