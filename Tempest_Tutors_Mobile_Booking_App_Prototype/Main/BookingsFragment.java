package w17014748.kf7008.tempesttutors;

import android.os.Bundle;
import android.util.Log;
import android.view.*;
import android.widget.*;

import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import java.util.ArrayList;
import java.util.Objects;

public class BookingsFragment extends Fragment {

    private final static String TAG = "BOOKINGS_FRAGMENT";

    DBHelper myDBHelper;

    ListView sessions_listView;
    ArrayList<TutorSession> sessions;
    Button bookSession_button, refreshList_button;
    SessionsListAdapter mySessionsListAdapter;
    TextView sessionId_textView;

    boolean allowShow, toUpdate = false;


    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        Log.i(TAG, "Bookings Fragment successfully loaded");

        // Inflate the layout for this fragment
        View fragView = inflater.inflate(R.layout.fragment_bookings, container, false);

        myDBHelper = new DBHelper(getActivity());

        sessions = new ArrayList<>();
        sessions_listView = (ListView) fragView.findViewById(R.id.sessionsListView);
        this.bookSession_button = (Button) fragView.findViewById(R.id.bookSessionButton);
        this.refreshList_button = (Button) fragView.findViewById(R.id.refreshListButton);

        // Check if database exists
        if (myDBHelper.databaseExists()) {
            Log.i(TAG, "Database already exists, filling the Sessions ListView");
            populateListView();
            allowShow = true;
        }
        else {
            Log.i(TAG, "Database does not exist yet");
        }

        // Listener for the items in the Sessions ListView - Takes user to the Book or Edit Session page
        // Only works when the appointments array list is populated and if allowShow has been flagged
        sessions_listView.setOnItemClickListener((AdapterView.OnItemClickListener) (parent, thisView, position, id) -> {

            if(sessions.size() != 0 && allowShow) {

                toUpdate = true;

                sessionId_textView = (TextView) thisView.findViewById(R.id.session_ID);
                String session_id = sessionId_textView.getText().toString();

                Bundle bundle = new Bundle();
                Fragment fragment = new BookOrEditSessionFragment();

                bundle.putInt("sessionID", Integer.parseInt(session_id));
                bundle.putBoolean("update_session", toUpdate);
                fragment.setArguments(bundle);

                assert getFragmentManager() != null;
                getFragmentManager()
                        .beginTransaction()
                        .replace(R.id.bookingsFrag_container, fragment)
                        .addToBackStack(null).commit();

            }
        });

        // Listen for Book Session click
        bookSession_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i(TAG, "\"Book a Session\" Button clicked");

                Fragment fragment = new BookOrEditSessionFragment();
                assert getFragmentManager() != null;
                getFragmentManager()
                        .beginTransaction()
                        .replace(R.id.bookingsFrag_container, fragment, "BookOrEditFrag")
                        .addToBackStack(null).commit();
            }
        });

        // Listen for Refresh List click
        refreshList_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i(TAG, "Resfresh List button clicked : Attempting to refresh Sessions list");

                //myDBHelper = new DBHelper(getActivity());

                if (myDBHelper.databaseExists()) {
                    Log.i(TAG, "Checking if database exists");

                    populateListView();
                    allowShow = true;
                    Toast.makeText(getActivity(), "List has been refreshed", Toast.LENGTH_SHORT).show();
                }
                else {
                    Log.i(TAG, "Database does not exist");
                    Toast.makeText(getActivity(), "You currently have no sessions booked", Toast.LENGTH_SHORT).show();
                }
            }
        });

        return fragView;
    }

    private void populateListView()
    {
        Log.i(TAG, "populateListView() : Attempting to fill 'appointments' array list with data retrieved from SQL query");

        sessions = myDBHelper.getAllData();

        mySessionsListAdapter = new SessionsListAdapter(Objects.requireNonNull(getActivity()).getBaseContext(), R.layout.booked_session_item_layout, sessions);
        sessions_listView.setAdapter(mySessionsListAdapter);
    }

    private void reloadFragment()
    {
        Log.i(TAG, "Reached reloadFragment()");

        Fragment currentFrag = Objects.requireNonNull(getActivity()).getSupportFragmentManager().findFragmentById(R.id.bookingsFrag_layout);
        if (currentFrag instanceof BookingsFragment) {
            assert getFragmentManager() != null;
            getFragmentManager()
                    .beginTransaction()
                    .detach(currentFrag)
                    .attach(currentFrag)
                    .commit();
        }
    }
}