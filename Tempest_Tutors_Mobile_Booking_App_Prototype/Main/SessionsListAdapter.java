package w17014748.kf7008.tempesttutors;

import android.content.Context;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.*;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import java.util.ArrayList;


public class SessionsListAdapter extends ArrayAdapter<TutorSession> {

    Context mContext;
    int mResource;


    // Holds and declares the TextViews
    static class ViewHolder
    {
        TextView session_idTV, session_tutorNameTV, session_instrumentTV, session_descTV,
                session_dateTV, session_timeTV;
    }

    // Constructor inherited fromm Super class
    public SessionsListAdapter(@NonNull Context context, int resource, @NonNull ArrayList<TutorSession> objects) {
        super(context, resource, objects);

        mContext = context;
        mResource = resource;
    }

    @NonNull
    @Override
    public View getView(int position, @Nullable View convertView, @NonNull ViewGroup parent) {

        ViewHolder vHolder = new ViewHolder();

        // 'getItem()' here is basically the array of Session objects
        // NOTE: All fields must be String for the TextViews
        String id = Integer.toString(getItem(position).getId());

        String name = getItem(position).getTutorName();
        String instrument = getItem(position).getInstrument();
        String desc = instrument + " Tutoring\nfrom " + name;

        String date = getItem(position).getDate();
        String time = getItem(position).getTime();


        // Create an Appointment object with the details retrieved from 'getItem()'
        //Appointment appoint = new Appointment(id, name, age, time);

        // Helps with app performance as it stores the Views in memory ahead of time to help
        // increase performance when loading them in the ListView
        // If the required item has not been loaded before...
        if(convertView == null) {
            LayoutInflater inflater = LayoutInflater.from(mContext);
            convertView = inflater.inflate(mResource, parent, false);
            vHolder.session_idTV = (TextView) convertView.findViewById(R.id.session_ID);

            vHolder.session_tutorNameTV = (TextView) convertView.findViewById(R.id.session_tutorName);
            vHolder.session_instrumentTV = (TextView) convertView.findViewById(R.id.session_instrument);
            vHolder.session_descTV = (TextView) convertView.findViewById(R.id.session_desc);

            vHolder.session_dateTV = (TextView) convertView.findViewById(R.id.session_date);
            vHolder.session_timeTV = (TextView) convertView.findViewById(R.id.session_time);

            convertView.setTag(vHolder);     // Stores the current state(?) of the View in memory
        }
        // Otherwise just load it from memory
        else {
            vHolder = (ViewHolder) convertView.getTag();
        }

        // Insert the appointment details into the ListView
        vHolder.session_idTV.setText(id);
        vHolder.session_tutorNameTV.setText(name);
        vHolder.session_instrumentTV.setText(instrument);
        vHolder.session_descTV.setText(desc);
        vHolder.session_dateTV.setText(date);
        vHolder.session_timeTV.setText(time);


        return convertView;
    }
}
