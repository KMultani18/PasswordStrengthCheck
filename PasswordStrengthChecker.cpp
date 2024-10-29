

#include <string>
#include <fstream>
#include <iostream> 

using namespace std;

class PasswordStrengthChecker {
private:
	std::string password; //holds password being checked
	std::string feedback; //why password may be invalid

	int minLength; //min len for pass
	int score; //for pswd strength

	bool requireUppercase; //one uppercase? 
	bool requireLowercase; //one lowercase? 
	bool requireDigit; //digit required? 
	bool requireSpecial; //special character require? 
	


public: 
	void setPassword (const std::string& pw) {
		password = pw; 
	}

	void setMinLength(int length) {
		if (length >= 1) {
			minLength = length; 
		}
		else {
			minLength = 8;
			feedback = "Minimum length cannot be less than 1. Setting default to 8.\n";
		}
	}

	void setRequiredUppercase(bool flag) {
		requireUppercase = flag; 

	}

	void setRequiredLowercase(bool flag) {
		requireLowercase = flag; 
	}

	void setRequiredSpecial(bool flag) {
		requireSpecial = flag; 
	}

	void setRequiredDigit(bool flag) {
		requireDigit = flag; 
	}

	//check for common password
	bool isPasswordValid() {

		feedback = "";
	
		if (password.length() < minLength) {
			feedback += "Password is too short.\n";
		}

		if (isCommon()) {
			feedback += "Password is too common.\n"; 
		}

		//initalize flags to track pswd
		bool hasUppercase = false; 
		bool hasLowercase = false; 
		bool hasDigit = false; 
		bool hasSpecial = false; 

		//iteratre through the password and check for required character types
		for (char ch : password) {
			if (isupper(ch)) {
				hasUppercase = true;
			}
			if (islower(ch)) {
				hasLowercase = true; 
			}
			if (isdigit(ch)) {
				hasDigit = true; 
			}
			if (ispunct(ch)) {
				hasSpecial = true;
			}
		}

		//check if uppercase is required and there
		if (requireUppercase && !hasUppercase) {
			feedback += "Password must contain at least one uppercase.\n"; 
		}

		// check for lowercase 
		if (requireLowercase && !hasLowercase) {
			feedback += "Password must contain at least one lowercase.\n";
		}

		if (requireDigit && !hasDigit) {
			feedback += "Password must contain atleast one digit.\n"; 
		}

		if (requireSpecial && !hasSpecial) {
			feedback += "Password must contain at least one special character.\n"; 
		}
		
		if (feedback.empty()) {
			feedback = "Password is valid.";
			return true;
		} else {
			return false; 
		}

	}

	
	bool isCommon() {
		std::ifstream file("most-common.txt");
		if (!file.is_open()) {
			std::cerr << "Error: Could not open most-common.txt file\n";
			return false;
		}

		std::string commonPassword; 
		while (std::getline(file, commonPassword)) {
			if (password == commonPassword) {
				file.close(); 
				return true; //password found common
			}
		}

		file.close(); 
		return false; //password is is not common 
	}

	int calculateScore() {
		score = 0; // Reset score

		// Check each password criterion and increment score
		if (password.length() >= minLength) score++;

		bool hasUppercase = false, hasLowercase = false;
		bool hasDigit = false, hasSpecial = false;

		// Check character types
		for (char ch : password) {
			if (isupper(ch)) hasUppercase = true;
			if (islower(ch)) hasLowercase = true;
			if (isdigit(ch)) hasDigit = true;
			if (ispunct(ch)) hasSpecial = true;
		}

		if (requireUppercase && hasUppercase) score++;
		if (requireLowercase && hasLowercase) score++;
		if (requireDigit && hasDigit) score++;
		if (requireSpecial && hasSpecial) score++;
		if (!isCommon()) score++;  // Reward if not a common password

		return score; // Return the final score (up to 6)
	}

	bool checkLength() {
		return password.length() >= minLength; 
	}

	bool containsUppercase() {
		for (char ch : password) {
			if (isupper(ch)) {
				return true; 
			}
		}
		return false; 
	}

	bool containsLowercase() {
		for (char ch : password) {
			if (islower(ch)) {
				return true;
			}
		}
		return false; 
	}

	bool containsDigit() {
		for (char ch : password) {
			if (isdigit(ch)) {
				return true; 
			}
		}
		return false; 
	}

	bool containsSpecial() {
		for (char ch : password) {
			if (ispunct(ch)) {
				return true; 
			}
		}
		return false; 
	}

	std::string getFeedback() const {
		return feedback; 
	}
};