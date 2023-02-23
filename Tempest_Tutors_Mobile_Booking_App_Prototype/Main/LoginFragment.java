package w17014748.kf7008.tempesttutors;

import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.*;
import android.widget.*;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import com.google.android.material.snackbar.Snackbar;

public class LoginFragment extends Fragment {

    private final static String TAG = "LOGIN_FRAGMENT";

    EditText username, password;
    Button loginButton;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {

        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_login, container, false);

        // Fragment elements
        username = (EditText) view.findViewById(R.id.loginUsername);
        password = (EditText) view.findViewById(R.id.loginPassword);
        this.loginButton = (Button) view.findViewById(R.id.loginButton);

        // Listen for each click
        loginButton.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v) {

                // Username and password extracted from the TextViews
                String input_username = username.getText().toString();
                String input_password = password.getText().toString();

                // Username and password for the prototype demo
                String demo_username = "username1";
                String demo_password = "password2";

                // Check that valid data is entered into the appropriate fields
                if(input_password.equals(demo_password) && input_username.equals(demo_username)) {

                    Log.i(TAG, "Login Button Clicked - UN: " + input_username + " - PW: " + input_password);
                    Intent intent = new Intent(getActivity(), MainActivity.class);
                    intent.putExtra("username", input_username);
                    startActivity(intent);
                }
                else {
                    // Inform the user what to do...
                    Toast.makeText(getActivity(), "For this demo please enter\nUsername: username1\nPassword: password2", Toast.LENGTH_SHORT).show();
                }
            }
        });

        return view;
    }
}
