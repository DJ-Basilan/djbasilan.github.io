package w17014748.kf7008.tempesttutors;

import android.os.Bundle;
import android.util.Log;
import android.view.*;
import android.widget.*;

import androidx.fragment.app.Fragment;

public class AccountFragment extends Fragment {

    private final static String TAG = "ACCOUNT_FRAGMENT";

    Button accountSettings_button, appSettings_button;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_account, container, false);

        this.accountSettings_button = (Button) view.findViewById(R.id.accountSettings_button);
        this.appSettings_button = (Button) view.findViewById(R.id.appSettings_button);


        accountSettings_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i(TAG, "Account Settings Button was clicked : Toast message should appear");
                Toast.makeText(getActivity(), "'Account Settings' page currently does not exist in this prototype", Toast.LENGTH_SHORT).show();
            }
        });

        appSettings_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i(TAG, "App Settings Button was clicked : Toast message should appear");
                Toast.makeText(getActivity(), "'App Settings' page currently does not exist in this prototype", Toast.LENGTH_SHORT).show();
            }
        });

        return view;
    }
}