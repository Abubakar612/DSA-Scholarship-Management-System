#include <iostream>             // one of the basic library use for the input output stream
#include <string>              // using for the operations on the string
#include <conio.h>            // for the usage of the function like getch
#include <fstream>           // for the saving data in the file
#include <iomanip>          // for the usage of the maniplutors
using namespace std;
void main_header() {       // using manuplator for the main header of the output display
	cout << setw(133) << setfill('*') << "" << endl;
	cout << "" << setfill(' ') << setw(81) << "Scholarship management system" << setw(51) << "" << endl;
	cout << setw(133) << setfill('*') << "" << endl;
}

// for the correct input of the day month and year in the date inputs
bool isValidDate(int day, int month, int year) {
	if (year < 0 || month < 1 || month > 12 || day < 1) return false;
	int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 }; // array for the no.of days in the months like 31 in jan and so on...
	if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) daysInMonth[1] = 29; //check for the leap years
	return day <= daysInMonth[month - 1];
}
double get_valid_double(const string& prompt) {// function for the correct inputs of double value like adding cgpa of the student
	string input;
	double number;

	while (true) {
		cout << prompt;
		cin >> input;
		bool isValid = true;
		bool decimalPoint = false;
		for (char c : input) {
			if (!isdigit(c)) {// check if the number is not digit
				if (c == '.' && !decimalPoint) { // check if the ( . ) occur for the 2nd time
					decimalPoint = true;
				}
				else {
					isValid = false;
					break;
				}
			}
		}

		if (isValid) {
			number = stod(input);// changing string into digits like(1,2,3....)
			break;
		}
		else {
			cout << "Invalid input. Please enter a valid number." << endl;
			cin.clear();
			while (cin.get() != '\n'); // reset the input if the exepected digit are not added for the fresh input
		}
	}

	return number;
}
int get_valid_integer(const string& prompt) { // function for the correct input of integer
	string input;
	int number;

	while (true) {
		cout << prompt;
		cin >> input;
		bool isValid = true;
		for (char c : input) {
			if (!isdigit(c)) {      // check if the number is not digit
				isValid = false;
				break;
			}
		}

		if (isValid) {
			number = stoi(input);  // converting string into numbers
			break;
		}
		else {
			cout << "Invalid input. Please enter a number." << endl;
			cin.clear();
			while (cin.get() != '\n');  // for clearing invalid input
		}
	}

	return number;
}
class Student_Node { // making node for the student and giving data attributes to the node
public:
	string password, f_name, s_name, f_id, s_id; // data of the student node
	int id, day, month, year, income, inter_marks, matric_marks; // data for the scholarship processing
	char slash;
	Student_Node* next;
};
class Admin_Node {  // making node for the student and giving data attributes to the node
public:
	string name, password;  //for the login of the admin
	Admin_Node* next;
};
Admin_Node* admin_head = NULL;
Student_Node* head = NULL;
int generateNewID() { // auto generate id of the registering student respectively
	if (head == NULL) {
		return 001;
	}
	Student_Node* temp = head;
	while (temp->next != NULL) {
		temp = temp->next; // traversing the list to check if the id exist
	}
	int lastID = temp->id;
	lastID++; // incrementing the lastid if the  registering id already exist
	return lastID;
}
bool check_username(string name) {   // function if the username exist aready in the list to avoid duplicating the data
	Admin_Node* temp = admin_head;  //  temp for the traversing of the list
	while (temp != NULL) {
		if (temp->name == name) {  // comparison of the input name withe name existing in the list
			return false;
		}
		temp = temp->next;       // updating the temp for the list
	}
	return true;
}
class Admin { // class for the admin containig functions like registering , updating e.t.c
public:
	bool login_admin() { // function for the login of the admin
		main_header();
		string username, password;
		cout << "Enter Username: ";
		cin.ignore();  // ignore for the spacing error while having string with the space
		getline(cin, username);
		cout << "Enter Password: ";
		char ch;
		while ((ch = _getch()) != '\r') { // hiding the inputing password until the enter is added
			password += ch;
			cout << '';                // displaying () instead of the password on the output screeen
		}
		cout << endl;
		Admin_Node* temp = admin_head;
		while (temp != NULL) {
			if (temp->name == username && temp->password == password) { // comparison of the input password with the password in the lists
				cout << "\t\t Login Successful" << endl;
				return true;
			}
			temp = temp->next;
		}
		cout << "\t\t Invalid Username or Password" << endl; // if the password and username do not match with the lists
		return false;
	}
	void update_student() {   // function for updating the data of the student
		main_header();  // for displaying the header on the screen
		int id;
		bool found = false;
		char slash;
		string day, month, year;
		cout << "Enter Student ID: 03-135232-";
		cin >> id;
		Student_Node* temp = head;  // making temp for traversing the student list

		while (temp != NULL) { // traversing until the tem points to NUll
			if (id == temp->id) {   // only update the data when the id exist in the list
				found = true;
				break;
			}
			temp = temp->next;  // update the pointer temp with its next untill it becomes Null
		}
		if (!found) {
			cout << "ID does not exist" << endl;  // if id does not find
			return;
		}
		cin.ignore();
		cout << "Enter new data for the student:" << endl; // upadtind data for the students
		cout << "Enter Student Name: ";         // upadting name of the students
		getline(cin, temp->s_name);
		cout << "Father name: ";
		getline(cin, temp->f_name);           // upadting f name of the students
		while (true) {
			// updating the data of the date
			temp->day = get_valid_integer("Enter day: ");
			temp->month = get_valid_integer("Enter month: ");
			temp->year = get_valid_integer("Enter year: ");
			// inputing the data for the date for updating
			if (isValidDate(temp->day, temp->month, temp->year)) {
				cout << "Date Entered: " << temp->day << "/" << temp->month << "/" << temp->year << endl;
				break;
			}
			else {
				cout << "The date is invalid. Please try again." << endl;
			}
		}
		while (true) { // loop for entering the matric marks
			cout << "Enter Matric Marks (out of 1100): ";
			temp->matric_marks = get_valid_integer("");
			if (temp->matric_marks < 0 || temp->matric_marks > 1100) {   // condition for the valid marks input
				cout << "Invalid marks entered! Please enter a value between 0 and 1100." << endl;
			}
			else if (temp->matric_marks < 660) { // no registration if marks are below than 660
				cout << "Your Matric marks are below the 60% eligibility threshold for the scholarship." << endl;
				return;
			}
			else {
				cout << "Matric marks entered successfully." << endl;   // successfull registration
				break;
			}
		}
		while (true) {
			cout << "Enter FSC Marks (out of 1100): ";    // condition for the valid marks input
			temp->inter_marks = get_valid_integer("");
			if (temp->inter_marks < 0 || temp->inter_marks > 1100) {  // no must be below than 1101 and +z
				cout << "Invalid input! Please enter a valid number between 0 and 1100 for FSC marks." << endl;
			}
			else if (temp->inter_marks < 660) { // no register if no 660
				cout << "Your FSC marks are below the 60% eligibility criteria for scholarship consideration." << endl;
				return;
			}
			else {
				cout << "FSC marks entered successfully!" << endl;
				break;
			}
		}
		cout << "Enter income:";
		cin >> temp->income;
		ofstream student_data_out("Student_data.txt");  // saving the data in the file function of fstream
		if (!student_data_out.is_open()) {
			cout << "Error opening file" << endl;     // IF FILE NOT FOUND
			return;
		}
		Student_Node* current = head;
		while (current != NULL) {    // WRITING DATA IN THE FILE
			student_data_out << left << setw(10) << setfill(' ') << current->id
				<< setw(10) << setfill(' ') << current->password  // password enterise
				<< setw(20) << setfill(' ') << current->s_name   // first name 
				<< setw(20) << setfill(' ') << current->f_name  // father name 
				<< current->day << '/' << current->month << '/' // DATA ENTERIES 
				<< setw(20) << setfill(' ') << current->year
				<< setw(10) << setfill(' ') << current->matric_marks
				<< setw(10) << setfill(' ') << current->inter_marks
				<< setw(10) << setfill(' ') << current->income  // income enteries
				<< endl;
			current = current->next; // UPDATING THE DATA IN EACH NODE BY TRAVERSING THE CURRENT BY ITS NEXT UNTILL IT BECOMES NULL
		}
		student_data_out.close();  // closing the file
		cout << "Student data updated successfully" << endl;
		system("cls");  // for clearing the output screen after chosing the wanted operation
	}
	void delete_student() {  // function for deleting the student in the list
		main_header();     // displaying the header on the output screen
		int id;
		bool found = false;
		cout << "Enter Student ID: 03-135232-";
		id = get_valid_integer("");
		Student_Node* temp = head;
		Student_Node* prev = NULL;  // pointer for storing the adress after deleting the node of the student to avoids memory loss

		while (temp != NULL) {  // traversing the list for the deletion of the wanted student
			if (id == temp->id) {
				found = true;
				break;
			}
			prev = temp; // pointing the previous to temp after deletion
			temp = temp->next;
		}
		if (!found) { // if id donot present in the list
			cout << "ID does not exist" << endl;
			return;
		}
		if (prev == NULL) {
			head = temp->next;
		}
		else {
			prev->next = temp->next;  // in the next of the previous we are saving the temp's next to hold the rest of the list
		}
		delete temp;  // deleting the node pointed by temp
		ofstream student_data_out("Student_data.txt");   // updating data in the file
		if (!student_data_out.is_open()) {
			cout << "Error opening file" << endl;
			return;
		}
		Student_Node* current = head;
		while (current != NULL) {     // writing data in the file 
			student_data_out << left << setw(10) << setfill(' ') << current->id
				<< setw(10) << setfill(' ') << current->password  // pass word entery
				<< setw(20) << setfill(' ') << current->s_name
				<< setw(20) << setfill(' ') << current->f_name
				<< current->day << '/' << current->month << '/'
				<< setw(20) << setfill(' ') << current->year
				<< setw(10) << setfill(' ') << current->matric_marks  // marks for student 
				<< setw(10) << setfill(' ') << current->inter_marks   // marks for inter marks
				<< setw(10) << setfill(' ') << current->income
				<< endl;
			current = current->next;
		}
		student_data_out.close();
		cout << "Student deleted successfully" << endl;
		system("cls");  // clearing the screen
	}
};
class Student {
	char slash;
public:
	bool loginSuccess = false;
	void register_student() {   //  function for registering the student 
		main_header();    // for the dispaly of the header on the screen
		cout << endl << endl << endl;
		Student_Node* newNode = new Student_Node;  // making newnode for the insertion of the new student
		newNode->next = NULL;
		cin.ignore();
		newNode->id = generateNewID();
		cout << "Student ID: 03-135232-" << setw(3) << setfill('0') << newNode->id << endl;
		newNode->password = 1234;  // defining the password for the registration

		cout << endl;
		cout << "Enter Student Name: ";
		getline(cin, newNode->s_name);  // enter the name for registring
		cout << "Father name: ";
		getline(cin, newNode->f_name);
		while (true) {  // entry of the date
			newNode->day = get_valid_integer("Enter day: ");
			newNode->month = get_valid_integer("Enter month: ");
			newNode->year = get_valid_integer("Enter year: ");

			if (isValidDate(newNode->day, newNode->month, newNode->year)) {  // displaying the date if the date format is accurate
				cout << "Date Entered: " << newNode->day << "/" << newNode->month << "/" << newNode->year << endl;
				break;
			}
			else {
				cout << "The date is invalid. Please try again." << endl;
			}
		}
		while (true) {
			cout << "Enter Matric Marks (out of 1100): ";
			newNode->matric_marks = get_valid_integer("");  // marks should be + integer  and less than 1101
			if (newNode->matric_marks < 0 || newNode->matric_marks > 1100) {
				cout << "Invalid marks entered! Please enter a value between 0 and 1100." << endl;
			}
			else if (newNode->matric_marks < 660) {  // necessary to have marks greater than 659
				cout << "Your Matric marks are below the 60% eligibility threshold for the scholarship." << endl;
				return;
			}
			else {
				cout << "Matric marks entered successfully." << endl;
				break;
			}
		}
		while (true) {
			cout << "Enter FSC Marks (out of 1100): ";
			newNode->inter_marks = get_valid_integer("");

			if (newNode->inter_marks < 0 || newNode->inter_marks > 1100) { // marks should be + integer  and less than 1101
				cout << "Invalid input! Please enter a valid number between 0 and 1100 for FSC marks." << endl;
			}
			else if (newNode->inter_marks < 660) {
				cout << "Your FSC marks are below the 60% eligibility criteria for scholarship consideration." << endl;
				return;
			}
			else {
				cout << "FSC marks entered successfully!" << endl;
				break;
			}
		}
		cout << "Enter income:";
		newNode->income = get_valid_integer("");  // income must be integer
		fstream user_data_in;
		user_data_in.open("Student_data.txt", ios::app);  //using app so the saved data does not lost when we close the program
		if (!user_data_in) {
			cout << "Unable to access file" << endl;
		}
		else {  // writng the data in the file   with proper formating 
			user_data_in << left << setw(10) << setfill(' ') << newNode->id
				<< setw(10) << setfill(' ') << newNode->password
				<< setw(20) << setfill(' ') << newNode->s_name
				<< setw(20) << setfill(' ') << newNode->f_name   // using manuplators for proper formating
				<< newNode->day << '/' << newNode->month << '/'
				<< setw(20) << setfill(' ') << newNode->year
				<< setw(10) << setfill(' ') << newNode->matric_marks
				<< setw(10) << setfill(' ') << newNode->inter_marks
				<< setw(10) << setfill(' ') << newNode->income
				<< endl;
		}
		user_data_in.close();   // closing the file after writng data 
		cout << "\t\t User Registered Successfully" << endl;
		if (head == NULL) {
			newNode->next = head;
			head = newNode;
		}
		else {
			Student_Node* temp = head;
			while (temp->next != NULL) {  // traversing the student node 
				temp = temp->next;
			}
			temp->next = newNode;    // insertion at the end of the list
		}
		system("cls");   // clearing the screen 
	}
};
void disp() {      // function for displaying the  data of the student 
	Student_Node* temp = head;
	main_header();
	cout << endl << endl << endl;
	cout << setw(120) << setfill('-') << "" << endl;
	cout << "| " << setw(13) << setfill(' ') << "ID" << " | "
		<< setw(20) << setfill(' ') << "Name" << " | "
		<< setw(20) << setfill(' ') << "Father's Name" << " | " // using the maniplutors for the proper displaying the data on the output screen 
		<< setw(10) << setfill(' ') << "DOB" << " | "
		<< setw(12) << setfill(' ') << "Matric Marks" << " | "
		<< setw(12) << setfill(' ') << "Inter Marks" << " | "
		<< setw(11) << setfill(' ') << "Income" << " |" << endl;
	cout << setw(120) << setfill('-') << "" << endl;

	if (temp == NULL) {  // if no student is present in the list
		cout << "No student records available." << endl;
		return;
	}

	while (temp != NULL) {  // displaying the daTA FOR THE STUDENT
		cout << "| " << setw(10) << setfill(' ') << "03-135232-" << setw(3) << setfill('0') << temp->id << " | "
			<< setw(20) << setfill(' ') << temp->s_name << " | "
			<< setw(20) << setfill(' ') << temp->f_name << " | "
			<< setw(2) << setfill('0') << temp->day << "/"
			<< setw(2) << setfill('0') << temp->month << "/"
			<< setw(4) << temp->year << " | "
			<< setw(12) << setfill(' ') << temp->matric_marks << " | "
			<< setw(12) << setfill(' ') << temp->inter_marks << " | "
			<< setw(11) << setfill(' ') << temp->income << " |" << endl;
		cout << setw(120) << setfill('-') << "" << endl;
		// proper formating on the screen by setfiil and w function of iomanip
		temp = temp->next;
	}
}
void load_student_DataFromFile() {  // function for reading datA FROM the file having data for the student
	ifstream student_data_in("Student_data.txt");
	if (!student_data_in.is_open()) {
		cout << "Error opening file" << endl;
		return;
	}
	string file_password, f_name, s_name, f_id, s_id;
	int file_id, day, month, year, income, inter_marks, matric_marks; // making the variable for dispalyin in proper formating
	char slash;
	while (student_data_in >> setw(10) >> file_id >> setw(20) >> file_password
		>> setw(20) >> s_name >> setw(20) >> f_name
		>> setw(2) >> day >> slash >> setw(2) >> month
		>> slash >> setw(4) >> year >> setw(10) >> matric_marks
		>> setw(10) >> inter_marks >> setw(10) >> income) {
		Student_Node* newNode = new Student_Node();
		newNode->id = file_id;
		newNode->password = file_password;
		newNode->s_name = s_name;
		newNode->f_name = f_name;
		newNode->day = day;   //reading with the data from the file 
		newNode->month = month;
		newNode->year = year;
		newNode->matric_marks = matric_marks;
		newNode->inter_marks = inter_marks;
		newNode->income = income;

		if (head == NULL) {
			head = newNode;
		}
		else {
			Student_Node* temp = head;
			while (temp->next != NULL) {
				temp = temp->next;     // traversing untill the end of the list
			}
			temp->next = newNode;
		}
	}
	student_data_in.close();  // closes the file after reading the data from the file 
}
void load_admin_DataFromFile() {  // loading the data from the file having info about admin
	ifstream admin_data_in("Admin_data.txt");
	if (!admin_data_in.is_open()) {
		cout << "Error opening file" << endl;
		return;
	}
	string file_password, name;
	while (admin_data_in >> setw(10) >> name >> setw(20) >> file_password) {
		Admin_Node* newNode = new Admin_Node();
		newNode->name = name;
		newNode->password = file_password;  // reading the data from the admin file 
		if (admin_head == NULL) {
			admin_head = newNode;
		}
		else {
			Admin_Node* temp = admin_head;
			while (temp->next != NULL) {  /// traversing untill the end of the list
				temp = temp->next;
			}
			temp->next = newNode;
		}
	}
	admin_data_in.close();  // closing the file having datra of the admin after reading info 
}
struct Merit_Node {  // structure for the merit list node demanding the acdamic info of the student for awarding the scholarship
	int id;
	string name;
	string f_name;
	double CGPA;
	Merit_Node* left;  // making the left and right pointers for the avl trees 
	Merit_Node* right;
	int height;
	// ******** WE ARE USING AVL FOR THE AUTO SORTING OF DATA ACCORDING TO HIGHEST CGPA FOR AWARDING SCHOLARSHIP***8
	Merit_Node(int id, string name, string f_name, double CGPA)
		: id(id), name(name), f_name(f_name), CGPA(CGPA), left(NULL), right(NULL), height(1) {
	}
};
Merit_Node* root = NULL;
int height(Merit_Node* node) {
	return node ? node->height : 0; // returning the node if it has no child meaning if it is a leaf node 
}

int getBalance(Merit_Node* node) {   // finding balancing factor to find if the bst is unbalanced 
	return node ? height(node->left) - height(node->right) : 0;  // returning the node if balance factor is 0 meaning bst is balanced 
}
bool save_to_file(Merit_Node* node, ofstream& file) { // RECURSIVE FUNCTION FOR THE AVL
	if (node != NULL) {
		save_to_file(node->left, file);   // FUNCTION FOR SAVING THE DATA IN THE FILE 
		file << node->id << " " << node->name << " " << node->f_name << " " << node->CGPA << endl;
		save_to_file(node->right, file);
	}
	return true;
}

Merit_Node* rightRotate(Merit_Node* y) {// function for balancing the bst 
	Merit_Node* x = y->left;   // set x as the left child of y
	Merit_Node* T2 = x->right;   // store the right subtree of x temporarily
	x->right = y;// Make y the right child of x
	y->left = T2;   // T2 as the left child of y

	// if the trees is unbalance then updating the height
	y->height = max(height(y->left), height(y->right)) + 1;
	x->height = max(height(x->left), height(x->right)) + 1;
	return x;
}

Merit_Node* leftRotate(Merit_Node* x) {
	Merit_Node* y = x->right;// Make y the right child of x
	Merit_Node* T2 = y->left;//  T2 as the left child of y
	y->left = x;
	x->right = T2;
	// updating the height 
	x->height = max(height(x->left), height(x->right)) + 1;
	y->height = max(height(y->left), height(y->right)) + 1;
	return y;
}
Merit_Node* insert_merit_node(Merit_Node* root, Merit_Node* newNode, ofstream& file) {
	if (root == NULL) {  //insert the new node if root is NULL
		file << newNode->id << " " << newNode->name << " " << newNode->f_name << " " << newNode->CGPA << endl;
		return newNode; // new node as the root
	}

	if (newNode->id == root->id) {
		// if the new node s ID is already present, print a warning 
		cout << "Enrollment ID already exists." << endl;
		return root;
	}
	//  insert the new node in the left or right this is recursive conditions
	if (newNode->CGPA < root->CGPA) {
		root->left = insert_merit_node(root->left, newNode, file);   // inserting the cgpa in left if it is less than the previous inputted cgpa 
	}
	else {
		root->right = insert_merit_node(root->right, newNode, file);// inserting the cgpa in right  if it is greater  than the previous inputted cgpa
	}

	root->height = max(height(root->left), height(root->right)) + 1; // updating the height after adding new cgpa 

	int balance = getBalance(root);  // updating the balance factor

	if (balance > 1 && newNode->CGPA < root->left->CGPA) {
		return rightRotate(root); // right rotation
	}

	if (balance < -1 && newNode->CGPA > root->right->CGPA) {
		return leftRotate(root);  //  left rotatation
	}
	if (balance > 1 && newNode->CGPA > root->left->CGPA) {
		root->left = leftRotate(root->left); //left rotation on the left child
		return rightRotate(root);  // perform right rotation on the root
	}
	if (balance < -1 && newNode->CGPA < root->right->CGPA) {
		root->right = rightRotate(root->right); // right rotation on the right
		return leftRotate(root); //left rotation on the root
	}

	return root;// Return the  root node
}
struct Need_Node {  // structure of the node for awarding need based scholarship 
	int id;
	string name;
	string f_name;
	double CGPA;    // attributes f the node 
	int income;
	Need_Node* next;
	Need_Node(int id, string name, string f_name, double CGPA, int income) // constructor for intitilizing the values in of the attributes of the newnode
		: id(id), name(name), f_name(f_name), CGPA(CGPA), income(income), next(NULL) {
	}
};

Need_Node* Need_head = NULL;
//     ************** APPLYING THE MERGE SORT FOR SORTING THE DATA BASED ON THEIR INCOME *******************//
Need_Node* merge(Need_Node* left, Need_Node* right) {
	if (!left) return right;   // if the left list is empty, return the right list
	if (!right) return left;// if the right list is empty, return the left list

	if (left->income <= right->income) {    // compare the income values of the two nodes
		left->next = merge(left->next, right);  // merge the rest of the left and right lists
		return left;  // returning the left node as it has the smaller income
	}
	else {
		right->next = merge(left, right->next);  //merge the rest of the left and right lists
		return right;    // returning the right node as it has the smaller income
	}
}

Need_Node* mergeSort(Need_Node* head) {
	if (!head || !head->next) return head;

	Need_Node* slow = head;         // slow start at head
	Need_Node* fast = head->next;   // fast is the next of slow one step ahead 

	while (fast && fast->next) {
		slow = slow->next;  // for finding middle we are making these pointers 
		fast = fast->next->next;
	}

	Need_Node* mid = slow->next; // This finds the middle of the linked list
	slow->next = NULL;

	Need_Node* left = mergeSort(head);   //sorting the first half
	Need_Node* right = mergeSort(mid);// sorting the rest of the list

	return merge(left, right);  // merging the left and right halfs of the list 
}

void writeToFile(Need_Node* node) {  // writng the data in the list for the merit scholarships sorted in the avl
	ofstream file("need_data.txt", ios::app);
	if (file.is_open()) {
		file << node->id << " " << node->name << " " << node->f_name << " " << node->CGPA << " " << node->income << "\n";
		file.close();   // closing the file after writng the data 
	}
	else {
		cout << "Unable to open file" << endl;
	}
}

void writeSortedToFile() {   // writng the data in the list for the need based scholarships sorted in the merge sort 
	ofstream file("need_data.txt", ios::trunc);  // using :: trunk for removing the data from the file because the sorted data will be stored there 
	if (file.is_open()) {
		Need_Node* temp = Need_head;
		while (temp != NULL) {
			// writng the data in the list 
			file << temp->id << " " << temp->name << " " << temp->f_name << " " << temp->CGPA << " " << temp->income << "\n";
			temp = temp->next;
		}
		file.close();  // closing the file after writing the data on the list 
	}
	else {
		cout << "Unable to open file" << endl;
	}
}

bool hasApplied(int id) {  // function to prevent the student for applying the same scholarship for the second time 
	Need_Node* temp = Need_head;
	while (temp != NULL) {  // traversing the whole list having the data 
		if (temp->id == id) {  // if the id does match then the function return the true 
			return true;
		}
		temp = temp->next;
	}
	return false;    // if the id does not  match then the function return the false 
}

void loadFromFile_need() {  // function for reading the data of the need based file 
	ifstream file("need_data.txt");
	if (!file.is_open()) {
		cout << "Unable to open file" << endl;
		return;
	}

	int id, income;
	string name, f_name;
	double CGPA;
	// reading the data from the file for the need based scholarship 
	while (file >> id >> name >> f_name >> CGPA >> income) {
		Need_Node* newNode = new Need_Node(id, name, f_name, CGPA, income);
		if (Need_head == NULL) {
			Need_head = newNode;
		}
		else {
			Need_Node* temp = Need_head;
			while (temp->next != NULL) {  // traversing the whoke list 
				temp = temp->next;
			}
			temp->next = newNode;
		}
	}

	file.close();
}

void sortNeedList() {   // function for calling the need based data that is sorted by merge sort 
	Need_head = mergeSort(Need_head);
	writeSortedToFile();
}

void Need_base_apply(Student_Node* student) {  // function for the need based scholarship
	if (student->income > 100000) {  // giving the  criteria for the need based scholarship 
		cout << "Student with income more than 100000 cannot apply for this scholarship." << endl;
		cout << "Press enter to continue" << endl;
		cin.ignore();
		cin.get();
		system("cls");  // for clearing the screen 
		return;
	}

	if (hasApplied(student->id)) {  // for prevetning the dupicates 
		cout << "Student has already applied for this scholarship." << endl;
		cout << "Press enter to continue" << endl;
		cin.ignore();
		cin.get();
		system("cls");  // for clearing the screen  on thee output display 
		return;
	}

	double CGPA = get_valid_double("Enter CGPA: "); // ensuring that the cgpa must be in accurate double 
	Need_Node* newNode = new Need_Node(student->id, student->s_name, student->f_name, CGPA, student->income);

	if (Need_head == NULL) {
		Need_head = newNode;
	}
	else {
		Need_Node* temp = Need_head;
		while (temp->next != NULL) {  // traversing the whole linklist
			temp = temp->next;
		}
		temp->next = newNode;  // insertin at the end of the list
	}
	cout << "Press enter to continue" << endl;
	cin.ignore();
	cin.get();
	system("cls");  // clearing the screen for output dispaly 
	writeToFile(newNode);  // writing the data in the file whose function we have defined above 
}
struct Naval_Node {  // structure for the naval based scholarship 
	int id;
	string name;
	string f_name;
	double CGPA;
	int percentage;
	Naval_Node* next;  //attributes for the naval based 
	Naval_Node(int id, string name, string f_name, double CGPA, int percentage)
		: id(id), name(name), f_name(f_name), CGPA(CGPA), percentage(percentage), next(NULL) {
	}
};

Naval_Node* naval_head = NULL;
bool hasAppliedNaval(int id) {  /// function for not spplying the twice 
	Naval_Node* temp = naval_head;
	while (temp != NULL) {
		if (temp->id == id) {  // check for the id match 
			return true;
		}
		temp = temp->next;
	}
	return false;
}
void writeToFileNaval(Naval_Node* node) {  // writng the data in the file with this function
	ofstream file("naval_data.txt", ios::app);
	if (file.is_open()) {
		file << node->id << " " << node->name << " " << node->f_name << " " << node->CGPA << " " << node->percentage << "\n";
		file.close();   //closing the file after writnig 
	}
	else {
		cout << "Unable to open file" << endl;
	}
}

void loadFromFileNaval() {  //function for reading the data from file 
	ifstream file("naval_data.txt");
	if (!file.is_open()) {
		cout << "Unable to open file" << endl;
		return;
	}

	int id, percentage;
	string name, f_name;
	double CGPA;
	// reading the data from the file 
	while (file >> id >> name >> f_name >> CGPA >> percentage) {
		Naval_Node* newNode = new Naval_Node(id, name, f_name, CGPA, percentage);
		if (naval_head == NULL) {
			naval_head = newNode;
		}
		else {

			// traversing the whole list for reading the data from the file 
			Naval_Node* temp = naval_head;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			// inserting at the end 
			temp->next = newNode;
		}
	}

	file.close();
}
// function for givng the crtiterria for the naval sscholarship
void naval_scholarship(Student_Node* student) {
	if (hasAppliedNaval(student->id)) {  // function for preventing duplicate 
		cout << "Student has already applied for this scholarship." << endl;
		cout << "Press enter to continue" << endl;
		cin.ignore();
		cin.get();
		system("cls");  // clearing the screen on the output display
		return;
	}
	double cgpa;
	cgpa = get_valid_double("Enter CGPA: ");
	if (cgpa >= 2) {
		int op;
		while (true) {
			cout << "Select Category: " << endl;
			cout << " 1. *** Star" << endl;
			cout << " 2. **  Star" << endl; // category for the naval based scholarship
			cout << " 3. *   Star" << endl;
			op = get_valid_integer("Enter Choice: ");
			if (op == 1 || op == 2 || op == 3) {
				break;
			}
			else {
				// check if the wrong option is selected
				cout << "Wrong choice. Please try again." << endl;
			}
		}

		int percentage;
		if (op == 1) {
			// catagories and the eligibility criteria 
			percentage = 70;
			cout << "Congratulations! You will get 70% scholarship." << endl;
		}
		else if (op == 2) {
			// catagories and the eligibility criteria 
			percentage = 50;
			cout << "Congratulations! You will get 50% scholarship." << endl;
		}
		else if (op == 3) {
			// catagories and the eligibility criteria 
			percentage = 30;
			cout << "Congratulations! You will get 30% scholarship." << endl;
		}

		Naval_Node* newNode = new Naval_Node(student->id, student->s_name, student->f_name, cgpa, percentage);

		if (naval_head == NULL) {
			naval_head = newNode;
		}
		else {
			Naval_Node* temp = naval_head;
			while (temp->next != NULL) {
				temp = temp->next;
			}
			temp->next = newNode;
		}

		writeToFileNaval(newNode);// if the newnode is addedd it will be wriitten in the file of the naval scholaraship
	}
	else {
		// catagories and the eligibility criteria 
		cout << "Student With less than 2 cgpa cannot apply" << endl;
		cout << "Press enter to continue" << endl;
		cin.ignore();
		cin.get();
		system("cls"); // for clearing the screen 
		return;
	}
	cout << "Press enter to continue" << endl;
	cin.ignore();
	cin.get();
	system("cls");   // for clearing the screen for the output display 
}
class Scholarship {  // class for the mainmenu of the available scholarship and the traversal
public:
	int availble_scholarships() {
		int op;
		cout << "Available Scholarships:" << endl;
		cout << " 1. Merit Based" << endl;
		cout << " 2. Need Based" << endl;
		cout << " 3. Naval Based" << endl;
		cout << "Any other key to exit" << endl;
		op = get_valid_integer("Enter your choice: ");
		return op;
	}
	// reversing  the inorder traversal RNl for displaying the data in the increasing order 
	void reverse_in_order_traversal(Merit_Node* root) {
		if (root != NULL) {
			reverse_in_order_traversal(root->right);  // reversing the traversal
			// dspaying the rootss data 
			cout << "ID: " << root->id << ", Name: " << root->name << ", CGPA: " << root->CGPA << endl;
			reverse_in_order_traversal(root->left);  //  reversing the traversal
		}
	}

	int apply_scholarship() {   // function for applying the scholarship
		while (true) {
			int id = get_valid_integer("Enter ID: 03-135232-");
			Student_Node* temp = head;
			bool found = false;

			while (temp != NULL) {
				if (id == temp->id) {    // if student is registered then he can apply 
					found = true;
					break;
				}
				temp = temp->next;
			}

			if (!found) {
				// menu for the proper function that we have to chose 
				int op1 = get_valid_integer("Student not found\n 1. Enter again\n 2. Exit\nEnter your choice: ");

				if (op1 != 1) {
					system("cls");   // for clearing the screen 
					return 0;
				}
			}
			else {
				int op2 = availble_scholarships();
				if (op2 == 1) {
					merit_based(temp); // merit base if op2 is selected 
				}
				else if (op2 == 2) {
					Need_base_apply(temp);
					sortNeedList(); // Sort and update the need-based list after applying
				}
				else if (op2 == 3) {
					naval_scholarship(temp);  // option for the naval 
				}
				return id;
			}
		}
	}

	void merit_based(Student_Node* temp) {
		double CGPA = get_valid_double("Enter CGPA: ");
		// attributes for the merit file 
		Merit_Node* newNode = new Merit_Node(temp->id, temp->s_name, temp->f_name, CGPA);
		ofstream file("merit_data.txt", ios::app);  // writng the merits file data
		root = insert_merit_node(root, newNode, file);
		file.close();  // closing the file 
		cout << "Press enter to continue" << endl;
		cin.ignore();
		cin.get();
		system("cls");
	}
};

void load_from_file(const string& filename) {
	ifstream file(filename); // reading the data from the file 
	if (file.is_open()) {
		int id;
		string name, f_name;
		double CGPA;
		while (file >> id >> name >> f_name >> CGPA) {
			Merit_Node* newNode = new Merit_Node(id, name, f_name, CGPA);
			ofstream tempFile("temp.txt", ios::app);  // saving the dat a in thee file if the project si closed 
			root = insert_merit_node(root, newNode, tempFile); // upadting the data in the rooot 
			tempFile.close(); // closing the file  
		}
		file.close();
	}
	else {
		cout << "Unable to open file for loading." << endl; // if file not found 
	}
}
void merit_awardlist(Merit_Node* root, int& count) { // awarding the merit scholarship 
	if (root != NULL && count < 3) {
		merit_awardlist(root->right, count);
		if (count < 3) {
			// calculating the discount 
			int percentage = 75 - (count * 25);
			cout << "  03-135232- " << root->id << "       " << root->name << "                    " << root->CGPA << "          " << percentage << "%            " << endl;
			cout << setw(70) << setfill('-') << "" << endl;
			count++;
		}
		merit_awardlist(root->left, count);
	}
}
void print_top_3_merit_awardlist(Merit_Node* root) {
	// giving the scholarships to the top 3 stdnts
	main_header();
	cout << endl << endl << endl;
	cout << setw(70) << setfill('-') << "" << endl;
	cout << "| " << setw(45) << setfill(' ') << "Merit Based Award List" << setw(23) << setfill(' ') << "|" << endl;
	cout << setw(70) << setfill('-') << "" << endl;
	cout << "|   " << "ID" << setw(20) << setfill(' ') << "|  Name" << setw(22) << setfill(' ') << "|   CGPA" << setw(16) << setfill(' ') << "|  Percentage" << "     |" << endl;
	cout << setw(70) << setfill('-') << "" << endl;
	cout << setfill(' ');
	int count = 0;
	merit_awardlist(root, count); // counting if the student is 3 give them scholarship 
}
void need_awarList() {  // function for awarding the need based scholarship
	Need_Node* temp = Need_head;
	main_header();  // header for dispalying
	cout << endl << endl << endl;
	cout << setw(70) << setfill('-') << "" << endl;
	cout << "| " << setw(45) << setfill(' ') << "Need Based Award List" << setw(23) << setfill(' ') << "|" << endl;
	cout << setw(70) << setfill('-') << "" << endl;
	cout << "|   " << "ID" << setw(20) << setfill(' ') << "|  Name" << setw(22) << setfill(' ') << "|   CGPA" << setw(16) << setfill(' ') << "|  Percentage" << "     |" << endl;
	cout << setw(70) << setfill('-') << "" << endl;
	// proper formating for the display
	int count = 0;
	while (temp != NULL && count < 5) {
		cout << setw(70) << setfill('-') << "" << endl;
		cout << "|  03-135232-" << setw(3) << setfill('0') << temp->id << " | "
			<< setw(20) << setfill(' ') << temp->name << " | "
			<< setw(10) << setfill(' ') << temp->CGPA << " | "
			<< setw(10) << setfill(' ') << "100 %" << " |" << endl;
		cout << setw(70) << setfill('-') << "" << endl;
		// displaying the awarde students
		temp = temp->next;
		count++; // incremnetibg the count 
	}
}
void naval_award() {  // awarding the merit scholarship 
	Naval_Node* temp = naval_head;
	main_header();  // displaying the main header on the output screen 
	cout << endl << endl << endl;
	cout << setw(100) << setfill('-') << "" << endl;
	cout << "| " << setw(45) << setfill(' ') << "Naval Based Award List" << setw(45) << setfill(' ') << "|" << endl;
	cout << setw(100) << setfill('-') << "" << endl;
	cout << "| " << setw(10) << setfill(' ') << "ID" << " | "
		<< setw(20) << setfill(' ') << "Name" << " | "
		<< setw(15) << setfill(' ') << "CGPA" << " | "
		<< setw(20) << setfill(' ') << "Percentage" << " |" << endl;
	cout << setw(100) << setfill('-') << "" << endl;

	if (temp == NULL) {  // it mean no student is available 
		cout << "No applications for naval scholarships." << endl;
		return;
	}

	while (temp != NULL) {  // traversing the list for dispaly the data of each node 
		cout << setw(100) << setfill('-') << "" << endl;
		cout << "| " << setw(10) << setfill(' ') << "03-135232-" << temp->id << " | "
			<< setw(20) << setfill(' ') << temp->name << " | "
			<< setw(15) << setfill(' ') << temp->CGPA << " | "
			<< setw(20) << setfill(' ') << temp->percentage << " % |" << endl;
		cout << setw(100) << setfill('-') << "" << endl;
		temp = temp->next;
	}
}
void admin_header() {
	// displaying the header of the admin 
	cout << setfill(' ');
	cout << endl << endl << endl;
	cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
	cout << setw(93) << setfill(' ') << "*               1. Add Student                   *" << endl;
	cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
	cout << setw(93) << setfill(' ') << "*               2. Update Student                *" << endl;
	cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
	cout << setw(93) << setfill(' ') << "*               3. Delete Student                *" << endl;
	cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
	cout << setw(93) << setfill(' ') << "*             4. Scholarships Awarded            *" << endl;
	cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
	cout << setw(93) << setfill(' ') << "*             5. To disp All Students            *" << endl;
	cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
	cout << setw(93) << setfill(' ') << "*                  0. Exit                       *" << endl;
	cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
}
int main() {
	loadFromFileNaval();  // callig the function for the naval data 
	loadFromFile_need();  // callig the function for the need data 
	load_from_file("merit_data.txt");  // callig the function for the merit  data 
	load_student_DataFromFile();  // callig the function for the student  data 
	load_admin_DataFromFile();  // callig the function for the admin data 
	Student s;
	Admin a;
	Scholarship b;  // creating object for the the classes 
	int op, op1, op2;
starty:
	main_header();  // dispalying the main header 
	cout << endl << endl << endl;
	cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
	cout << setw(93) << setfill(' ') << "*                Choose an Option                *" << endl;
	cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
	cout << setw(93) << setfill(' ') << "*                    1. Admin                    *" << endl;
	cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
	cout << setw(93) << setfill(' ') << "*                    2. Student                  *" << endl;
	cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
	cout << setw(93) << setfill(' ') << "*             Press any key to exit              *" << endl;
	cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
	cin >> op1;
	///// main menu for display
	system("cls");
	while (true) {
		if (op1 == 1) {
		startx:
			if (a.login_admin()) {  // for the admin login 
				system("cls");
				do {
					main_header();
					admin_header();
					cin >> op2;
					system("cls");
					if (op2 == 1) {
						system("cls");
						s.register_student(); // for the student register 
					}
					else if (op2 == 2) {
						system("cls");
						a.update_student();
					}  // option for the main menu 
					else if (op2 == 3) {
						system("cls");
						a.delete_student();  // for the deltion 
					}
					else if (op2 == 4) {
						system("cls");
						main_header();
						cout << setfill(' ');
						cout << endl << endl << endl;
						// displaying the main menu
						cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
						cout << setw(93) << setfill(' ') << "*                 1. Merit Based                 *" << endl;
						cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
						cout << setw(93) << setfill(' ') << "*                 2. Need Based                  *" << endl;
						cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
						cout << setw(93) << setfill(' ') << "*                 3. Naval Based                 *" << endl;
						cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << " " << endl;
						cout << setfill(' ');
						int op3 = get_valid_integer("Choose Option: ");
						system("cls");
						if (op3 == 1) {
							system("cls");
							print_top_3_merit_awardlist(root);
							cout << "Press enter to continue" << endl;
							cin.ignore();
							cin.get();
							system("cls");   // for clearing the screen 
						}
						else if (op3 == 2) {
							system("cls");
							need_awarList();   // calling the fiunction 
							cout << "Press enter to continue" << endl;
							cin.ignore();
							cin.get();
							system("cls");
						}
						else if (op3 == 3) {
							system("cls");
							naval_award();
							cout << "Press enter to continue" << endl;
							cin.ignore();
							cin.get();
							system("cls");
						}
					}
					else if (op2 == 5) {
						main_header();
						disp();
						cout << "Press enter to continue" << endl;
						cin.ignore();
						cin.get();
						system("cls");
					}

				} while (op2 != 0);
				system("cls");
				main_header();  // displaying the header 
				cout << endl << endl << endl;
				cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
				cout << setw(93) << setfill(' ') << "*                Choose an Option                *" << endl;
				cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
				cout << setw(93) << setfill(' ') << "*                    1. Admin                    *" << endl;
				cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
				cout << setw(93) << setfill(' ') << "*                    2. Student                  *" << endl;
				cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
				cout << setw(93) << setfill(' ') << "*              Press any key to exit             *" << endl;
				cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
				cin >> op1;
				system("cls");
			}
			else {
				int x;
				// check for clearing the screen properly 
				cout << "1 to enter again" << endl;
				cout << "0 to exit" << endl;
				cin >> x;
				if (x == 1) {
					system("cls");
					goto startx; // going to start again 
				}
				else {
					cout << "Press enter to continue" << endl;
					cin.ignore();
					cin.get();
					system("cls");
					goto starty;
				}
			}
		}
		else if (op1 == 2) {
			do {
				main_header();  // calling the main header 
				cout << endl << endl << endl;
				cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
				cout << setw(93) << setfill(' ') << "*                1. To Register                  *" << endl;
				cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
				cout << setw(93) << setfill(' ') << "*              2. Apply Scholarship              *" << endl;
				cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
				cout << setw(93) << setfill(' ') << "*              Press any key to exit             *" << endl;
				cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
				op = get_valid_integer(" ");
				system("cls");
				if (op == 1) {
					main_header(); // main header on the screen
					s.register_student();
				}
				else if (op == 2) {
					main_header();
					int id = b.apply_scholarship();
				}
			} while (op != 0);
			system("cls");
			main_header();
			cout << endl << endl << endl;
			// main menu fr the first display
			cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
			cout << setw(93) << setfill(' ') << "*                Choose an Option                *" << endl;
			cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
			cout << setw(93) << setfill(' ') << "*                    1. Admin                    *" << endl;
			cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
			cout << setw(93) << setfill(' ') << "*                   2. Student                   *" << endl;
			cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
			cout << setw(93) << setfill(' ') << "*              Press any key to exit             *" << endl;
			cout << setw(43) << setfill(' ') << "" << setw(50) << setfill('*') << "" << endl;
			cin >> op1;
			system("cls");
		}
		else { // returning the  program 
			return 0;
		}
	}
	cout << endl;
	return 0;
}
