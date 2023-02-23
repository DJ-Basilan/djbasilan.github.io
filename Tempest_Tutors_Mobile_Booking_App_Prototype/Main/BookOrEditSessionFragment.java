package w17014748.kf7008.tempesttutors;

import android.app.DatePickerDialog;
import android.app.TimePickerDialog;
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.text.InputType;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.*;

import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Objects;


public class BookOrEditSessionFragment extends Fragment {

    private final static String TAG = "BOOK/EDIT_SESSION_FRAGMENT";

    DBHelper myDBHelper;

    Spinner instruments_spinner, tutorName_spinner;
    ArrayAdapter<String> tutorName_adapter, instruments_adapter;
    EditText selectDate_editText, selectTime_editText;
    Button finishBooking_button, cancelBooking_button, deleteSession_button;
    TextView sessionStatus_textView;

    int session_id;
    String tutorName, instrument, time, date;
    boolean toUpdate, success = false;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_book_or_edit_session, container, false);

        // Instantiate the variables for interacting with the database
        myDBHelper = new DBHelper(getActivity());
        TutorSession session = new TutorSession();

        // Link the Fields from the layout file
        sessionStatus_textView = (TextView) view.findViewById(R.id.session_status);
        selectDate_editText = (EditText) view.findViewById(R.id.selectDate_editText);
        selectTime_editText = (EditText) view.findViewById(R.id.selectTime_editText);

        // Hides the android keyboard so that input can only be set through the Date-Time pickers
        selectDate_editText.setInputType(InputType.TYPE_NULL);
        selectTime_editText.setInputType(InputType.TYPE_NULL);

        this.finishBooking_button = (Button) view.findViewById(R.id.finishBooking_button);
        this.cancelBooking_button = (Button) view.findViewById(R.id.cancelBooking_button);
        this.deleteSession_button = (Button) view.findViewById(R.id.deleteSession_button);

        tutorName_spinner = (Spinner) view.findViewById(R.id.tutorName_dropdown);
        instruments_spinner = (Spinner) view.findViewById(R.id.instrument_dropdown);

        tutorName_adapter = new ArrayAdapter<>(getActivity(), android.R.layout.simple_list_item_1,
                getResources().getStringArray(R.array.tutor_names));
        instruments_adapter = new ArrayAdapter<>(getActivity(), android.R.layout.simple_list_item_1,
                getResources().getStringArray(R.array.instruments));

        // Assign the adapters for the spinners
        tutorName_adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        instruments_adapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);

        tutorName_spinner.setAdapter(tutorName_adapter);
        instruments_spinner.setAdapter(instruments_adapter);

        // Preset the fields according to the selected appointment
        Bundle bundle = this.getArguments();
        if(bundle != null) {
            session_id = bundle.getInt("sessionID", 0);
            toUpdate = bundle.getBoolean("update_session", false);

            Log.i(TAG, "Session ID: " + session_id + " was passed to AppointmentDetails");
        }
        else Log.i(TAG, "Error retrieving Bundle args");

        if(toUpdate)
        {
            // Change the page title and button accordingly
            sessionStatus_textView.setText("EDIT SESSION");
            this.finishBooking_button.setText("Update Session");
            this.deleteSession_button.setVisibility(View.VISIBLE);

            // Search the database for the session with said
            if (myDBHelper.getAppointById(session_id, session)) {
                Log.i(TAG, "Session ID: " + session_id + " has been found in the Database");

                // Retrieve the details of the corresponding session
                if (session.getTutorName() != null) {
                    int spinnerPos = tutorName_adapter.getPosition(session.getTutorName());
                    tutorName_spinner.setSelection(spinnerPos);
                }
                if (session.getInstrument() != null) {
                    int spinnerPos = instruments_adapter.getPosition(session.getInstrument());
                    instruments_spinner.setSelection(spinnerPos);
                }
                selectDate_editText.setText(session.getDate());
                selectTime_editText.setText(session.getTime());
            }
            else Log.i(TAG, "Session ID: " + session_id + " does not exist in the Database");
        }
        else {
            // Change the page title and button accordingly
            sessionStatus_textView.setText("NEW SESSION");
            this.finishBooking_button.setText("Book Session");
            this.deleteSession_button.setVisibility(View.GONE);
        }

        // Listener for selecting a date from calendar
        selectDate_editText.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i(TAG, "SELECT DATE Clicked : Date Picker Dialog should appear");

                // For the sake of tidiness, the functions related to this button have been moved to a separate function
                showDateDialog(selectDate_editText);
            }
        });

        // Listener for selecting a time
        selectTime_editText.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Log.i(TAG, "SELECT TIME Clicked : Time Picker Dialog should appear");

                // For the sake of tidiness, the functions related to this button have been moved to a separate function
                showTimeDialog(selectTime_editText);
            }
        });

        // Listener for finish button
        finishBooking_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                // For the sake of tidiness, the functions related to this button have been moved to a separate function
                finishButton();
            }
        });

        // Listener for cancel button
        cancelBooking_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                // Simply return to previous fragment
                returnToFrag();
            }
        });

        // Listener for delete button
        deleteSession_button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                // For the sake of tidiness, the functions related to this button have been moved to a separate function
                deleteButton();
            }
        });

        return view;
    }

    // Shows calendar when user taps/clicks on SELECT DATE
    private void showDateDialog(final EditText _dateET) {
        Calendar calendar = Calendar.getInstance();
        DatePickerDialog.OnDateSetListener dateSetListener = new DatePickerDialog.OnDateSetListener() {
            @Override
            public void onDateSet(DatePicker view, int year, int month, int dayOfMonth) {

                // Set the calendar variables
                calendar.set(Calendar.YEAR, year);
                calendar.set(Calendar.MONTH, month);
                calendar.set(Calendar.DAY_OF_MONTH, dayOfMonth);

                // Set date format
                SimpleDateFormat dateFormat = new SimpleDateFormat("dd-MMM-yy");

                // Change the Date accordingly on the EditText
                _dateET.setText(dateFormat.format(calendar.getTime()));
            }
        };

        // Create new instance of Date Picker Dialog
        new DatePickerDialog(getActivity(), dateSetListener, calendar.get(Calendar.YEAR),
                calendar.get(Calendar.MONTH), calendar.get(Calendar.DAY_OF_MONTH)).show();
    }

    // Shows time picker when user taps/clicks on SELECT TIME
    private void showTimeDialog(final EditText _timeET) {
        Calendar calendar = Calendar.getInstance();

        TimePickerDialog.OnTimeSetListener timeSetListener = new TimePickerDialog.OnTimeSetListener() {
            @Override
            public void onTimeSet(TimePicker view, int hourOfDay, int minute) {
                calendar.set(Calendar.HOUR_OF_DAY, hourOfDay);
                calendar.set(Calendar.MINUTE, minute);

                // Set time format - Hours : minutes
                SimpleDateFormat timeFormat = new SimpleDateFormat("HH:mm");

                // Change the time accordingly on the EditText
                _timeET.setText(timeFormat.format(calendar.getTime()));
            }
        };

        // Create new instance of Time Picker Dialog - Set in 24hrs format
        new TimePickerDialog(getActivity(), timeSetListener, calendar.get(Calendar.HOUR_OF_DAY),
                calendar.get(Calendar.MINUTE), true).show();
    }

    // Handles all functions related to the NEW/UPDATE SESSION Button
    private void finishButton() {

        myDBHelper = new DBHelper(getActivity());

        // Check that the EditText fields are not empty
        if(tutorName_spinner.getSelectedItemPosition() != 0 // AND
                && instruments_spinner.getSelectedItemPosition() != 0 // AND
                && selectDate_editText.length() != 0 // AND
                && selectTime_editText.length() != 0) {

            // Retrieve the session details from the text fields
            tutorName = tutorName_adapter.getItem(tutorName_spinner.getSelectedItemPosition());
            instrument = instruments_adapter.getItem(instruments_spinner.getSelectedItemPosition());
            date = selectDate_editText.getText().toString();
            time = selectTime_editText.getText().toString();

            if (!toUpdate) {     // Add new session...
                Log.i(TAG, " Button pressed : Attempting to add new session to Database");

                TutorSession session = new TutorSession(tutorName, instrument, date, time);
                success = myDBHelper.addSession(session);

                if (success) {
                    Toast.makeText(getActivity(), "New session successfully booked", Toast.LENGTH_SHORT).show();
                    returnToFrag();
                }
                else Toast.makeText(getActivity(), "Session could not be added", Toast.LENGTH_SHORT).show();
            }
            else {              // Or update selected session
                Log.i(TAG, "UPDATE SESSION Button pressed : Attempting to update selected session in Database");

                TutorSession session = new TutorSession(session_id, tutorName, instrument, date, time);
                success = myDBHelper.updateSession(session);

                if (success) {
                    Toast.makeText(getActivity(), "Session successfully updated", Toast.LENGTH_SHORT).show();
                    returnToFrag();
                }
                else Toast.makeText(getActivity(), "Session could not be updated", Toast.LENGTH_SHORT).show();
            }
        }// if() - Check that the EditText fields are not empty
        else Toast.makeText(getActivity(), "Please make sure that all fields are filled in", Toast.LENGTH_SHORT).show();
    }// finishButton()

    // Handles all functions related to the DELETE SESSION Button
    private void deleteButton() {
        Log.i(TAG, "DELETE SESSION Button pressed : Attempting to delete selected session in Database");

        myDBHelper = new DBHelper(getActivity());

        // Set as 'delete' button while an existing session is being edited...
        if(toUpdate) {
            success = myDBHelper.deleteSession(session_id);

            if (success) {
                Toast.makeText(getActivity(), "Session successfully deleted", Toast.LENGTH_SHORT).show();
                returnToFrag();
            } else
                Toast.makeText(getActivity(), "Session could not be deleted", Toast.LENGTH_SHORT).show();
        }
    }// deleteButton()

    // Function for returning to previous fragment
    private void returnToFrag() {
        Log.i(TAG, "Reached returnToFrag()");
        //reloadBookingsFrag();
        assert getFragmentManager() != null;
        getFragmentManager().popBackStack();
    }

    // This function is supposed to automatically refresh the ListView in BookingsFragment when it
    // returns FROM this Fragment but it does not work...
//    private void reloadBookingsFrag() {
//        Log.i(TAG, "Reached reloadBookingsFrag()");
//
//        Fragment currentFrag = Objects.requireNonNull(getActivity()).getSupportFragmentManager().findFragmentById(R.id.bookingsFrag_layout);
//        if (currentFrag instanceof BookingsFragment) {
//            assert getFragmentManager() != null;
//            getFragmentManager()
//                    .beginTransaction()
//                    .detach(currentFrag)
//                    .attach(currentFrag)
//                    .commit();
//        }
//    }
}