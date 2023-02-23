package w17014748.kf7008.tempesttutors;

import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import com.google.android.material.snackbar.Snackbar;

public class SignUpFragment extends Fragment {

    private final static String TAG = "SIGNUP_FRAGMENT";

    EditText username, password, confirmPassword;
    Button createButton;

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container,
                             @Nullable Bundle savedInstanceState) {

        // Inflate the layout for this fragment
        View view = inflater.inflate(R.layout.fragment_signup, container, false);

        // Fragment elements
        username = (EditText) view.findViewById(R.id.newUsername);
        password = (EditText) view.findViewById(R.id.newPassword);
        confirmPassword = (EditText) view.findViewById(R.id.confirmPassword);
        this.createButton = (Button) view.findViewById(R.id.createButton);

        // Listen for each click
        createButton.setOnClickListener(new View.OnClickListener()
        {
            @Override
            public void onClick(View v) {

                Intent intent = new Intent(getActivity(), MainActivity.class);

                int usernameLength = username.getText().toString().length();
                int passwordLength = password.getText().toString().length();

                if (usernameLength < 6) {
                    Toast.makeText(getActivity(),"Username must be 6 or more characters long", Toast.LENGTH_SHORT).show();
                }
                else if (passwordLength < 8) {
                    Toast.makeText(getActivity(),"Password must be 8 or more characters long", Toast.LENGTH_SHORT).show();
                }
                else if (!confirmPassword.getText().toString().equals(password.getText().toString())) {
                    Toast.makeText(getActivity(),"Confirm Password does not match the Password", Toast.LENGTH_SHORT).show();
                }
                else {
                    Log.i(TAG, "Login Button Clicked - UN: \"" +
                            username.getText().toString() + "\" - PW: \"" + password.getText().toString() +
                            "\" - ConfirmPW: \"" + confirmPassword.getText().toString() + "\"");

                    intent.putExtra("username", username.getText().toString());
                    startActivity(intent);
                }
            }
        });

        return view;
    }
}
