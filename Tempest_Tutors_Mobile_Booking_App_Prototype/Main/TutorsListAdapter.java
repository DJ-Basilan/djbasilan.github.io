package w17014748.kf7008.tempesttutors;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;

import java.util.ArrayList;


public class TutorsListAdapter extends ArrayAdapter<Tutor> {

    Context mContext;
    int mResource;


    // Holds and declares the TextViews
    static class ViewHolder
    {
        TextView tutor_idTV, tutor_nameTV;
    }

    // Constructor inherited fromm Super class
    public TutorsListAdapter(@NonNull Context context, int resource, @NonNull ArrayList<Tutor> objects) {
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
        String name = getItem(position).getName();


        // Helps with app performance as it stores the Views in memory ahead of time to help
        // increase performance when loading them in the ListView
        // If the required item has not been loaded before...
        if(convertView == null) {
            LayoutInflater inflater = LayoutInflater.from(mContext);
            convertView = inflater.inflate(mResource, parent, false);

            vHolder.tutor_idTV = (TextView) convertView.findViewById(R.id.tutor_ID);
            vHolder.tutor_nameTV = (TextView) convertView.findViewById(R.id.tutor_name);

            convertView.setTag(vHolder);     // Stores the current state(?) of the View in memory
        }
        // Otherwise just load it from memory
        else {
            vHolder = (ViewHolder) convertView.getTag();
        }

        // Insert the appointment details into the ListView
        vHolder.tutor_idTV.setText(id);
        vHolder.tutor_nameTV.setText(name);

        return convertView;
    }
}
