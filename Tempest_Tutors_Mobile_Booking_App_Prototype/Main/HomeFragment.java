package w17014748.kf7008.tempesttutors;

import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.util.Log;
import android.view.*;
import android.widget.*;

public class HomeFragment extends Fragment {

    private final static String TAG = "HOME_FRAGMENT";

    Button ourTutors, stages, aboutTempest;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_home, container, false);

        Log.i(TAG, "Reached Home Fragment");

        this.ourTutors = (Button) view.findViewById(R.id.tutors_button);
        this.stages = (Button) view.findViewById(R.id.stages_button);
        this.aboutTempest = (Button) view.findViewById(R.id.aboutTempest_button);


        // Listener for Our Tutors button - Sends user to the corresponding page
        ourTutors.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                Log.i(TAG, "Our Tutors Button was clicked : Taking user to TutorsListFragment");

                Fragment fragment = new TutorsListFragment();

                assert getFragmentManager() != null;
                getFragmentManager()
                        .beginTransaction()
                        .replace(R.id.homeFrag_container, fragment)
                        .addToBackStack(null).commit();
            }
        });

        // Listener for Stage button - Corresponding page has not been created for this demo
        stages.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i(TAG, "Stages Button was clicked : Toast message should appear");
                Toast.makeText(getActivity(), "'Stages' page currently does not exist in this prototype", Toast.LENGTH_SHORT).show();
            }
        });

        // Listener for About Tempest button - Corresponding page has not been created for this demo
        aboutTempest.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i(TAG, "About Tempest Button was clicked : Toast message should appear");
                Toast.makeText(getActivity(), "'About Tempest' page currently does not exist in this prototype", Toast.LENGTH_SHORT).show();
            }
        });

        return view;
    }
}