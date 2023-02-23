package w17014748.kf7008.tempesttutors;

import android.graphics.drawable.Drawable;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.*;

import androidx.fragment.app.Fragment;

public class TutorInfoFragment extends Fragment {

    private final static String TAG = "TUTOR_INFO_FRAGMENT";

    TextView tutorNameTV, tutorDescriptionTV;
    ImageView tutorImage;
    Button goBack_button;
    String tutorName, tutorInfo;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_tutor_info, container, false);

        // Sends out a log message for testing purposes
        Log.i(TAG, "TutorInfoFragment was reached");

        // Define the Widgets
        tutorNameTV = (TextView) view.findViewById(R.id.tutorName_info);
        tutorDescriptionTV = (TextView) view.findViewById(R.id.tutorDescription_info);
        tutorImage = (ImageView) view.findViewById(R.id.tutorImage_info);   // Left alone for now, will be used to hold the Tutor's picture
        this.goBack_button = (Button) view.findViewById(R.id.goBack_button_info);

        // Preset the fields according to the selected appointment
        Bundle bundle = this.getArguments();
        if(bundle != null) {
            tutorName = bundle.getString("tutorName", "Bundle arg: 'tutorName' could not be found");
            tutorInfo = bundle.getString("tutorInfo", "Bundle arg: 'tutorInfo' could not be found");

            Log.i(TAG, "tutorName and tutorInfo were retrieved from Bundle");
        }
        else Log.i(TAG, "Error retrieving Bundle args");

        if(tutorName != null && tutorInfo != null) {
            tutorNameTV.setText(tutorName);
            tutorDescriptionTV.setText(tutorInfo);

            Log.i(TAG, "TextViews for Tutor Name and Description have been successfully set");
        }

        // Listener for Go Back button
        goBack_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                // Simply return to previous fragment
                Log.i(TAG, "Go Back Button was clicked : Returning to TutorsListFragment");
                assert getFragmentManager() != null;
                getFragmentManager().popBackStack();
            }
        });

        return view;
    }
}
