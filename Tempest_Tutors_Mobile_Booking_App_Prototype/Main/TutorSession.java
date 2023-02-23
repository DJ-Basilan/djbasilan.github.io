package w17014748.kf7008.tempesttutors;

public class TutorSession {

    // Database Table name
    public static final String TABLE = "TutorSession";

    // Database Table Columns names
    public static final String KEY_ID = "id";
    public static final String KEY_name = "tutor_name";
    public static final String KEY_instrument = "instrument";
    public static final String KEY_date = "date";
    public static final String KEY_time = "time";

    private int id;
    private String tutor_name, instrument, date, time;

    // Default constructor
    public TutorSession() {
        id = -1;
        tutor_name = "";
        instrument = "";
        date = "";
        time = "";
    }

    // Constructor - Used for ADDING a new Session to the Database
    public TutorSession(String tutor_name, String instrument, String date, String time) {
        this.tutor_name = tutor_name;
        this.instrument = instrument;
        this.date = date;
        this.time = time;
    }

    // Constructor - Used for UPDATING Session to the Database
    public TutorSession(int id, String tutor_name, String instrument, String date, String time) {
        this.id = id;
        this.tutor_name = tutor_name;
        this.instrument = instrument;
        this.date = date;
        this.time = time;
    }


    // Getters
    public int getId() {
        return id;
    }

    public String getTutorName() {
        return tutor_name;
    }

    public String getInstrument() {
        return instrument;
    }

    public String getDate() {
        return date;
    }

    public String getTime() {
        return time;
    }


    // Setters
    public void setId(int id) {
        this.id = id;
    }

    public void setTutorName(String tutor_name) {
        this.tutor_name = tutor_name;
    }

    public void setInstrument(String instrument) {
        this.instrument = instrument;
    }

    public void setDate(String date) {
        this.date = date;
    }

    public void setTime(String time) {
        this.time = time;
    }
}
