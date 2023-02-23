package w17014748.kf7008.tempesttutors;

// Used for creating Tutor objects
public class Tutor {

    private int id;
    private String name;
    private String description;

    // Default constructor
    public Tutor()
    {
        id = -1;
        name = "";
        description = "";
    }

    // Constructor with parameters
    public Tutor(int id, String name, String description)
    {
        this.id = id;
        this.name = name;
        this.description = description;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getDescription() {
        return description;
    }

    public void setDescription(String description) {
        this.description = description;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }
}
