package w17014748.kf7008.tempesttutors;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.util.Log;

import java.util.ArrayList;

public class DBHelper extends SQLiteOpenHelper {

    // Version number to upgrade database version - each time
    // a tables is Added or Edited table, you need to change the
    // version number.
    private static final int DATABASE_VERSION = 4;

    // Database Filename
    private static final String DATABASE_NAME = "Tempest.db";


    public DBHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {

        // All necessary tables you like to create will create here
        // Seems it's possible to create more than one table if needed
        String CREATE_TABLE_APPOINTMENT = "CREATE TABLE " + TutorSession.TABLE
                + "(" + TutorSession.KEY_ID + " INTEGER PRIMARY KEY AUTOINCREMENT, "
                + TutorSession.KEY_name + " TEXT, "
                + TutorSession.KEY_instrument + " TEXT, "
                + TutorSession.KEY_date + " TEXT, "
                + TutorSession.KEY_time + " TEXT )";

        db.execSQL(CREATE_TABLE_APPOINTMENT);
    }

    // Only gets called if the DATABASE_VERSION changes
    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {

        // Drop older table if existed, all data will be gone!!!
        db.execSQL("DROP TABLE IF EXISTS " + TutorSession.TABLE);

        // Alternative could be... Doesn't delete all the data
        //db.execSQL("ALTER TABLE " + Appointment.TABLE);

        // Create tables again
        onCreate(db);
    }

    public boolean addSession(TutorSession session) {
        Log.d("DB_HELPER", "Reached addSession()");

        ContentValues values = new ContentValues();
        SQLiteDatabase db = this.getWritableDatabase();

        values.put(TutorSession.KEY_name, session.getTutorName());
        values.put(TutorSession.KEY_instrument, session.getInstrument());
        values.put(TutorSession.KEY_date, session.getDate());
        values.put(TutorSession.KEY_time, session.getTime());

        // Inserting Row
        long result = db.insertOrThrow(TutorSession.TABLE, null, values);

        return result != -1;
    }

    public boolean deleteSession(int appoint_Id) {
        Log.d("DB_HELPER", "Reached deleteAppoint()");

        SQLiteDatabase db = this.getWritableDatabase();
        long result = db.delete(TutorSession.TABLE, TutorSession.KEY_ID + "= ?", new String[]{String.valueOf(appoint_Id)});

        return result != -1;
    }

    public boolean updateSession(TutorSession session) {
        Log.d("DB_HELPER", "Reached updateAppoint()");

        ContentValues values = new ContentValues();
        SQLiteDatabase db = this.getWritableDatabase();

        values.put(TutorSession.KEY_name, session.getTutorName());
        values.put(TutorSession.KEY_instrument, session.getInstrument());
        values.put(TutorSession.KEY_date, session.getDate());
        values.put(TutorSession.KEY_time, session.getTime());

        // It's a good practice to use parameter ?, instead of concatenate string
        long result = db.update(TutorSession.TABLE, values, TutorSession.KEY_ID + "= ?", new String[] {String.valueOf(session.getId()) });

        return result != -1;
    }

    public boolean getAppointById(int Id, TutorSession session) {
        Log.i("DB_HELPER", "Reached getAppointById() : Given ID is " + Id);

        SQLiteDatabase db = this.getReadableDatabase();
        String selectQuery =  "SELECT " +
                TutorSession.KEY_ID + "," +
                TutorSession.KEY_name + "," +
                TutorSession.KEY_instrument + "," +
                TutorSession.KEY_date + "," +
                TutorSession.KEY_time +
                " FROM " + TutorSession.TABLE
                + " WHERE " +
                TutorSession.KEY_ID + "=?";// It's a good practice to use parameter ?, instead of concatenate string
        Log.i("DB_HELPER", "SQL Query has ben readied");

        //Appointment appoint = new Appointment();

        Cursor cursor = db.rawQuery(selectQuery, new String[] { Integer.toString(Id) } );
        Log.i("DB_HELPER", "Query sent to Database");

        if (cursor.moveToFirst()) {
            do {
                session.setId(cursor.getInt(cursor.getColumnIndex(TutorSession.KEY_ID)));
                session.setTutorName(cursor.getString(cursor.getColumnIndex(TutorSession.KEY_name)));
                session.setInstrument(cursor.getString(cursor.getColumnIndex(TutorSession.KEY_instrument)));
                session.setDate(cursor.getString(cursor.getColumnIndex(TutorSession.KEY_date)));
                session.setTime(cursor.getString(cursor.getColumnIndex(TutorSession.KEY_time)));
            }
            while (cursor.moveToNext());
        }

        int check = session.getId();

        cursor.close();
        db.close();
        return Id == check;
    }


    public ArrayList<TutorSession> getAllData()
    {
        Log.i("DB_HELPER", "getAllData() reached");

        SQLiteDatabase db = this.getWritableDatabase();
        ArrayList<TutorSession> sessions = new ArrayList<>();
        String selectQuery =  "SELECT * FROM " + TutorSession.TABLE;

        // Get data from the SQL query
        Cursor cursor = db.rawQuery(selectQuery, null);
        int c_id;
        String c_name, c_instrument, c_date, c_time;

        //ArrayList<String> testList = new ArrayList<>();

        // Loop through the SQL table and insert the data into the corresponding position in the array list
        while (cursor.moveToNext()) {
            c_id = Integer.parseInt(cursor.getString(cursor.getColumnIndex(TutorSession.KEY_ID)));
            c_name = cursor.getString(cursor.getColumnIndex(TutorSession.KEY_name));
            c_instrument = cursor.getString(cursor.getColumnIndex(TutorSession.KEY_instrument));
            c_date = cursor.getString(cursor.getColumnIndex(TutorSession.KEY_date));
            c_time = cursor.getString(cursor.getColumnIndex(TutorSession.KEY_time));

            TutorSession session = new TutorSession(c_id, c_name, c_instrument, c_date, c_time);

            sessions.add(session);
            //testList.add(c_name);
        }

        db.close();
        cursor.close();

        return sessions;
    }

    // Check if the first item exists in the database - Confirms if it exists
    public boolean databaseExists() {
        Log.d("DB_HELPER", "Reached databaseExists()");

        SQLiteDatabase db = this.getWritableDatabase();
        ArrayList<TutorSession> sessions = new ArrayList<>();
        String selectQuery =  "SELECT * FROM " + TutorSession.TABLE;

        // Get data from the SQL query
        Cursor cursor = db.rawQuery(selectQuery, null);
        int c_id;
        String c_name, c_instrument, c_date, c_time;

        // Loop through the SQL table and insert the data into the corresponding position in the array list
        while (cursor.moveToNext()) {
            c_id = Integer.parseInt(cursor.getString(cursor.getColumnIndex(TutorSession.KEY_ID)));
            c_name = cursor.getString(cursor.getColumnIndex(TutorSession.KEY_name));
            c_instrument = cursor.getString(cursor.getColumnIndex(TutorSession.KEY_instrument));
            c_date = cursor.getString(cursor.getColumnIndex(TutorSession.KEY_date));
            c_time = cursor.getString(cursor.getColumnIndex(TutorSession.KEY_time));

            TutorSession session = new TutorSession(c_id, c_name, c_instrument, c_date, c_time);

            sessions.add(session);
        }

        db.close();
        cursor.close();

        return sessions.size() != 0;
    }
}