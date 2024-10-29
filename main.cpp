

#include "PasswordStrengthChecker.cpp"

int main() {
    // Create an instance of PasswordStrengthChecker
    PasswordStrengthChecker checker;

    // Set password requirements
    checker.setMinLength(8);              // Set minimum length to 8
    checker.setRequiredUppercase(true);   // Require at least one uppercase letter
    checker.setRequiredLowercase(true);   // Require at least one lowercase letter
    checker.setRequiredDigit(true);       // Require at least one digit
    checker.setRequiredSpecial(true);     // Require at least one special character

    // Ask the user to enter a password
    std::string userPassword;
    std::cout << "Enter a password to check: ";
    std::cin >> userPassword;

    // Set the user's password in the checker
    checker.setPassword(userPassword);

    // Check if the password is valid
    if (checker.isPasswordValid()) {
        std::cout << "Password is valid!" << std::endl;

        // Calculate and print the score if the password is valid
        int score = checker.calculateScore();
        std::cout << "Password score: " << score << "/6\n";

        // Provide feedback based on the score
      
        if (score < 3) {
            std::cout << "Bad Password\n";
        }
        else if (score == 4) {
            std::cout << "Medium Password\n";
        }
        else if (score >= 5) {
            std::cout << "Good Password\n";
        }
    }
    else {
        std::cout << "Password is invalid:\n" << checker.getFeedback() << std::endl;
    }

    return 0;
}