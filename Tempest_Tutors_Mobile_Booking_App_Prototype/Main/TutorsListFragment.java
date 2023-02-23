package w17014748.kf7008.tempesttutors;

import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;

import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import org.jetbrains.annotations.NotNull;

import java.util.ArrayList;
import java.util.Objects;

public class TutorsListFragment extends Fragment {

    private final static String TAG = "TUTORS_LIST_FRAGMENT";

    ListView tutors_listView;
    ArrayList<Tutor> tutors;
    Button goBack_button;
    TutorsListAdapter myTutorsListAdapter;
    TextView tutorId_textView;

    String tutorName, tutorInfoText;

    @Nullable
    @Override
    public View onCreateView(@NotNull LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        Log.i(TAG, "Tutors List Fragment successfully loaded");

        View view = inflater.inflate(R.layout.fragment_tutors_list, container, false);

        tutors = new ArrayList<>();

        tutors_listView = (ListView) view.findViewById(R.id.tutors_listView);
        this.goBack_button = (Button) view.findViewById(R.id.goBack_button);

        // Show the Tutors List
        populateListView();

        // Listener for the ListView items
        tutors_listView.setOnItemClickListener((AdapterView.OnItemClickListener) (parent, thisView, position, id) -> {

            // Check that the array is not empty - It shouldn't be for this prototype
            if(tutors.size() != 0)
            {
                // Get the tutor ID from the item layout
                tutorId_textView = (TextView) thisView.findViewById(R.id.tutor_ID);
                String getTutorID = tutorId_textView.getText().toString();
                int tutorID = Integer.parseInt(getTutorID);

                // Extract the corresponding Tutor object from the Tutors arraylist
                tutorName = tutors.get(tutorID).getName();
                tutorInfoText = tutors.get(tutorID).getDescription();

                // Prepare the next fragment and the data to send through
                Bundle bundle = new Bundle();
                Fragment fragment = new TutorInfoFragment();

                // Insert the data
                bundle.putString("tutorName", tutorName);
                bundle.putString("tutorInfo", tutorInfoText);
                fragment.setArguments(bundle);

                Log.i(TAG, "Item in Tutors ListView clicked : Sending Tutor: " + tutorName + " to TutorInfoFragment");

                // Go to the next fragment
                assert getFragmentManager() != null;
                getFragmentManager()
                        .beginTransaction()
                        .replace(R.id.homeFrag_container, fragment)
                        .addToBackStack(null).commit();
            }
        });

        // Listener for Go Back button
        goBack_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                // Simply return to previous fragment
                Log.i(TAG, "Go Back Button was clicked : Returning to HomeFragment");
                assert getFragmentManager() != null;
                getFragmentManager().popBackStack();
            }
        });

        return view;
    }

    // Generates nine Tutors objects and adds them to the Tutor arraylist
    private ArrayList<Tutor> addTutors()
    {
        String[] names = {"Alexis", "Ashley", "Brett", "Elaine", "James", "Lingling", "Rimiru", "Suzaku", "Zack"};

        ArrayList<Tutor> _tutors = new ArrayList<>();

        String dummyText = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, " +
                "sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. " +
                "Et egestas quis ipsum suspendisse ultrices gravida dictum fusce ut. " +
                "Malesuada fames ac turpis egestas maecenas pharetra. " +
                "Turpis tincidunt id aliquet risus feugiat. " +
                "Quis auctor elit sed vulputate mi sit amet mauris. " +
                "Augue neque gravida in fermentum et sollicitudin ac. " +
                "Enim nulla aliquet porttitor lacus luctus. " +
                "Ut venenatis tellus in metus vulputate.\n\n" +
                "Tristique senectus et netus et malesuada. " +
                "Eget duis at tellus at urna condimentum mattis pellentesque id. " +
                "Venenatis tellus in metus vulputate. " +
                "Ullamcorper dignissim cras tincidunt lobortis feugiat vivamus at augue. " +
                "Lectus arcu bibendum at varius vel pharetra vel. " +
                "Consequat nisl vel pretium lectus quam id. " +
                "Varius morbi enim nunc faucibus a pellentesque sit amet. " +
                "Viverra justo nec ultrices dui sapien eget mi proin sed. " +
                "Praesent tristique magna sit amet.";

        // Fill the Tutors ArrayList
        for(int i = 0; i < names.length; i++)
        {
            Tutor tutor = new Tutor(i, names[i], dummyText);
            _tutors.add(tutor);
        }

        return _tutors;
    }


    private void populateListView()
    {
        Log.i(TAG, "populateListView() : Attempting to fill the Tutors ListView with the Tutors ArrayList");

        // Check if the arraylist is not already full
        if (tutors.size() == 0) tutors = addTutors();

        // Do the thing
        myTutorsListAdapter = new TutorsListAdapter(Objects.requireNonNull(getActivity()).getBaseContext(), R.layout.tutors_list_item_layout, tutors);
        tutors_listView.setAdapter(myTutorsListAdapter);
    }
}
