#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

class cgpa_invalid  //1
{
    string error;
public:
    cgpa_invalid(string error) : error(error) {}
    void display_error()
    {
        cout << error << endl;
    }
};

// Forward declaration of PlacementRecord class for friend function
class PlacementRecord;
class PlacementCoordinator;


// Base class: Person
class Person { //2
protected:
    string name;
    int age;
    string number;
    string location;
    string dob;

public:
    Person(string name, int age, string number, string location, string dob)
        : name(name), age(age), number(number), location(location), dob(dob) {}

    virtual ~Person() {}

    string getName() {
        return name;
    }

    virtual void displayDetails() = 0; // Pure virtual function for abstraction
};

// Derived class: Student
class Student : public Person { //3
private:
    int regNo;
    static int num;
    int studentID;
    vector<string> skills;
    float GPA;

public:
    Student(string name, int age, string number, string location, string dob, int studentID, float GPA)
        : Person(name, age, number, location, dob), studentID(studentID), GPA(GPA) {
        regNo = ++num;
         if (GPA < 4) {
            throw cgpa_invalid("GPA must be more than 4.0.");
        }
    }

    void addSkill(string skill) {
        skills.push_back(skill);
    }

    void updateGPA(float newGPA) {
        if (newGPA < 4) {
            throw cgpa_invalid("GPA must be more than 4.0.");
        }
        GPA = newGPA;
    }

    void displayDetails() {
        cout << "Student Name: " << name << endl;
        cout << "Student ID: " << studentID << endl;
        cout << "Registration Number: " << regNo << endl;
        cout << "Age: " << age << endl;
        cout << "Phone Number: " << number << endl;
        cout << "Location: " << location << endl;
        cout << "Date Of Birth: " << dob << endl;
        cout << "GPA: " << GPA << endl;
        cout << "Skills: ";
        for (int i = 0; i < skills.size(); i++) {
            cout << i + 1 << ". " << skills[i] << " ";
        }
        cout << endl;
    }
    int getstudentID()
    {
        return studentID;
    }
};
int Student::num = 0;

// Base class: Company
class Company { //4
private:
    int companyID;
    string name;
    string city;

    vector<string> requiredSkills;

public:
    int jobOpenings;
    Company(int companyID, string name, string city, int jobOpenings)
        : companyID(companyID), name(name), city(city), jobOpenings(jobOpenings) {}

    void addJobOpening(string skill) {
        requiredSkills.push_back(skill);
    }

    void displayDetails() {
        cout << "Company ID: " << companyID << endl;
        cout << "Company Name: " << name << endl;
        cout << "Company Location: " << city << endl;
        cout << "Job Openings: " << jobOpenings << endl;
     //   cout << "Required Skills: ";
      //  for (int i = 0; i < requiredSkills.size(); i++) {
       //     cout << i + 1 << ". " << requiredSkills[i] << " ";
       // }
        cout << endl;
    }

    int getID() {
        return companyID;
    }

    string getName() {
        return name;
    }

    // Friend function to access jobOpenings
    friend void accessJobOpenings(Company company, PlacementCoordinator coordinator);
};

// Base class: PlacementRecord
class PlacementRecord { //5
protected:
    Student* student;
    Company* company;
    string status;

public:
    PlacementRecord(Student* student, Company* company, string status)
        : student(student), company(company), status(status) {}

    virtual void displayDetails() {
        cout << "Student Name: " << student->getName() << endl;
        cout << "Company Name: " << company->getName() << endl;
        cout << "Status: " << status << endl;
    }
};

// Derived class: InternshipRecord
class InternshipRecord : public PlacementRecord {
private:
    string position;
    int duration;

public:
    InternshipRecord(Student* student, Company* company, string status, string position, int duration)
        : PlacementRecord(student, company, status), position(position), duration(duration) {}

    void displayDetails() {
        cout << "Internship Position: " << position << endl;
        cout << "Duration: " << duration << " months" << endl;
        PlacementRecord::displayDetails(); // Late binding
    }
};

// Derived class: JobOffer
class JobOffer : public PlacementRecord { //6
private:
    string position;
    float salary;

public:
    JobOffer(Student* student, Company* company, string status, string position, float salary)
        : PlacementRecord(student, company, status), position(position), salary(salary) {}

    void displayDetails() {
        cout << "Job Position: " << position << endl;
        cout << "Salary: Rs" << salary << endl;
        PlacementRecord::displayDetails(); // Late binding
    }
};

// Derived class: PlacementCoordinator
class PlacementCoordinator : public Person {  //7
private:
    int coordinatorID;

public:
    PlacementCoordinator(string name, int age, string number, string location, string dob, int coordinatorID)
        : Person(name, age, number, location, dob), coordinatorID(coordinatorID) {}

    void displayDetails() {
        cout << "Placement Coordinator Name: " << name << endl;
        cout << "Coordinator ID: " << coordinatorID << endl;
    }

    // Friend function to access jobOpenings of Company
    friend void accessJobOpenings(Company company, PlacementCoordinator coordinator);
};

// Function to access jobOpenings of Company
void accessJobOpenings(Company company, PlacementCoordinator& coordinator) {
    cout << "Coordinator " << coordinator.getName() << " accessed job openings of Company " << company.getName() << ": " << company.jobOpenings << endl;
}

// class: Interview
class Interview { //8
private:
    string interviewer;
    string date;
    string result;

public:
    Interview(string interviewer, string date, string result)
        : interviewer(interviewer), date(date), result(result) {}

    void displayDetails() {
        cout << "Interviewer: " << interviewer << endl;
        cout << "Date: " << date << endl;
        cout << "Result: " << result << endl;
    }
};

// class: Resume
class Resume { //9
private:
    Student* student;
    string content;

public:
    Resume(Student* student, string& content)
        : student(student), content(content) {}

    void displayDetails() {
        cout << "Student Name: " << student->getName() << endl;
        cout << "Resume Content: " << content << endl;
    }
};

// class: Event
class Event { //10
private:
    int eventID;
    string name;
    string date;

public:
    Event(int eventID, string& name, string& date)
        : eventID(eventID), name(name), date(date) {}

    void displayDetails() {
        cout << "Event ID: " << eventID << endl;
        cout << "Event Name: " << name << endl;
        cout << "Event Date: " << date << endl;
    }
    string getdate()
    {
        return date;
    }
};

// class: Notification
class Notification { //11
private:
    Person* recipient;
    string content;
    string date;

public:
    Notification(Person* recipient, string content, string date)
        : recipient(recipient), content(content), date(date) {}

    void displayDetails() {
        cout << "Recipient: " << recipient->getName() << endl;
        cout << "Content: " << content << endl;
        cout << "Date: " << date << endl;
    }
};

// class: Feedback
class Feedback { //12
private:
    string sender;
    string content;
    string date;

public:
    Feedback(string sender, string& content, string& date)
        : sender(sender), content(content), date(date) {}

    void displayDetails() {
        cout << "Sender: " << sender << endl;
        cout << "Content: " << content << endl;
        cout << "Date: " << date << endl;
    }
};

// class: Admin
class Admin { //13
private:
    int adminID;
    string name;

public:
    Admin(int adminID, string& name)
        : adminID(adminID), name(name) {}

    void displayDetails() {
        cout << "Admin Name: " << name << endl;
        cout << "Admin ID: " << adminID << endl;
    }
};

class PlacementSystem { //14
private:
    vector<Student> students;
    vector<Company> companies;
    vector<PlacementCoordinator> coordinators;
    vector<Interview> interviews;
    vector<Resume> resumes;
    vector<Event> events;
    vector<Notification> notifications;
    vector<Feedback> feedbacks;
    vector<Admin> admins;
    vector<PlacementRecord*> placements;

    string adminUsername;
    string adminPassword;

public:
    PlacementSystem(string username, string password)
        : adminUsername(username), adminPassword(password) {}

    bool login(string username, string password) {
        if (username == adminUsername && password == adminPassword) {
            cout << "Login successful!" << endl;
            return true;
        } else {
            cout << "Invalid username or password. Login failed!" << endl;
            return false;
        }
    }

    void registerStudent(Student& student) {
        students.push_back(student);
        cout << "Student Registered Successfully!" << endl;
    }

    void registerCompany(Company& company) {
        companies.push_back(company);
        cout << "Company Registered Successfully!" << endl;
    }

    void createInternshipRecord(InternshipRecord& internship) {
        placements.push_back(new InternshipRecord(internship));
        cout << "Internship Record Created Successfully!" << endl;
    }

    void createJobOffer(JobOffer& jobOffer) {
        placements.push_back(new JobOffer(jobOffer));
        cout << "Job Offer Created Successfully!" << endl;
    }

    void notify(Notification& notify) {
        notifications.push_back(notify);
        cout << "Notified Successfully!" << endl;
    }

    void addPlacementRecord(PlacementRecord* record) {
        placements.push_back(record);
    }

    vector<PlacementRecord*> getPlacementRecords() {
        return placements;
    }

    // Function to add a student to the placement system
    void addStudent(Student student) {
        students.push_back(student);
    }

    // Function to add a company to the placement system
    void addCompany(Company company) {
        companies.push_back(company);
    }
     void display(Student s)
     {
         s.displayDetails();
     }

    // Function to display all registered students
    void displayAllStudents() {
        cout<<"size is"<<students.size()<<endl;
        cout << "===== All Students =====" << endl;
        for (int i=0;i<students.size();i++) {
        display(students[i]);
        }
        cout << "========================" << endl;
    }

    // Function to display all registered companies
    void displayAllCompanies() {
        cout << "===== All Companies =====" << endl;
        for (auto& company : companies) {
            company.displayDetails();
        }
        cout << "========================" << endl;
    }

 void searchStudentByID(int studentID) {
    for (auto& student : students) {
        if (student.getstudentID() == studentID) {
            student.displayDetails();
            return;
        }
    }
    cout << "Student with ID " << studentID << " not found." << endl;
}

// Function to search for a company by ID and display their details
void searchCompanyByID(int companyID) {
    for (auto& company : companies) {
        if (company.getID() == companyID) {
            company.displayDetails();
            return;
        }
    }
    cout << "Company with ID " << companyID << " not found." << endl;
}

    // Destructor to clean up dynamically allocated memory for PlacementRecords
    ~PlacementSystem() {
        for (auto placement : placements) {
            delete placement;
        }
    }
    vector<Student>& getStudents() {
        return students;
    }

    // Function to get a reference to the companies vector
    vector<Company>& getCompanies() {
        return companies;
    }

    // Function to add an interview to the placement system
    void addInterview(Interview interview) {
        interviews.push_back(interview);
    }

    // Function to add feedback to the placement system
    void addFeedback(Feedback feedback) {
        feedbacks.push_back(feedback);
    }

    // Function to add a resume to the placement system
    void addResume(Resume resume) {
        resumes.push_back(resume);
    }

    // Function to add an event to the placement system
    void addEvent(Event event) {
        events.push_back(event);
    }

    // Function to display all interviews
    void displayAllInterviews() {
        cout << "===== All Interviews =====" << endl;
        for (auto& interview : interviews) {

            interview.displayDetails();
        }
        cout << "========================" << endl;
    }

    // Function to display all feedbacks
    void displayAllFeedbacks() {
        cout << "===== All Feedbacks =====" << endl;
        for (auto& feedback : feedbacks) {
            // Call appropriate displayDetails() function for Feedback class
             feedback.displayDetails();
        }
        cout << "========================" << endl;
    }

    // Function to display all resumes
    void displayAllResumes() {
        cout << "===== All Resumes =====" << endl;
        for (auto& resume : resumes) {

            resume.displayDetails();
        }
        cout << "========================" << endl;
    }

    // Function to display all events
    void displayAllEvents() {
        cout << "===== All Events =====" << endl;
        for (auto& event : events) {
            // Call appropriate displayDetails() function for Event class
             event.displayDetails();
        }
        cout << "========================" << endl;
    }
    // Function to display events of a particular date
    void displayEventsByDate(  string& eventDate) {
        cout << "===== Events on " << eventDate << " =====" << endl;
        bool found = false;
        for (  auto& event : events) {
            if (event.getdate() == eventDate) {
                // Call appropriate displayDetails() function for Event class
                event.displayDetails();
               // cout << "Event: " <<event.displayDetails() << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No events found on " << eventDate << endl;
        }
        cout << "========================" << endl;
    }
};

class PersonFactory {
public:
    // Factory method to create a Student
    static Student createStudent(string name, int age, string number, string location, string dob, int studentID, float GPA) {
        return Student(name, age, number, location, dob, studentID, GPA);
    }

    // Factory method to create a PlacementCoordinator
    static PlacementCoordinator createPlacementCoordinator(string name, int age, string number, string location, string dob, int coordinatorID) {
        return PlacementCoordinator(name, age, number, location, dob, coordinatorID);
    }
};

// Function to display the main menu options
void displayMainMenu() {
    cout << "===== Main Menu =====" << endl;
    cout << "1. Register Student" << endl;
    cout << "2. Register Company" << endl;
    cout << "3. Create Internship Record" << endl;
    cout << "4. Create Job Offer" << endl;
    cout << "5. Display All Students" << endl;
    cout << "6. Display All Companies" << endl;
    cout << "7. Search Student by ID" << endl;
    cout << "8. Search Company by ID" << endl;
    cout << "9. Send Notification" << endl;
    cout << "10. Display Placement Records" << endl;
    cout << "11. Add an event"<<endl;
    cout<<"12.Add Feedback"<<endl;
    cout<<"13.Schedule an Interview"<<endl;
    cout<<"14.Display all the events on a particular date"<<endl;
    cout<<"15.Display Feedback\n";
    cout<<"16.Display interview details"<<endl;


    cout << "0. Exit" << endl;
    cout << "=====================" << endl;
    cout << "Enter your choice: ";
}

int main() {
    PlacementSystem placementSystem("admin", "admin123"); // Sample admin credentials

    // Perform user authentication before accessing the system
    string username, password;
    cout << "===== Placement System Login =====" << endl;
    cout << "Username: ";
    cin >> username;
    cout << "Password: ";
    cin >> password;

    if (!placementSystem.login(username, password)) {
        return 0;
    }
//vector<Student> students;
   // vector<Company> companies;
    vector<PlacementRecord*> placements;
        int choice;
    do {
        displayMainMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, dob, location;
                int age,id;
                string number;
                float GPA;

                cout<<"Enter student id: "<<endl;
                cin>>id;
                cout << "Enter Student Name: ";
                cin.ignore(); // Ignore any newline characters from previous inputs
                getline(cin, name);


                cout << "Enter Date Of Birth (dd-mm-yyyy): ";
                cin >> dob;

                cout << "Enter Age: ";
                cin >> age;

                cout << "Enter Phone Number: ";
                cin >> number;

                cout << "Enter Location: ";
                cin.ignore();
                getline(cin, location);

                try{
                    cout << "Enter GPA: ";
                cin >> GPA;
                }
                catch(cgpa_invalid& c)
                {
                    c.display_error();
                }
              //Student newStudent(name,age,number,location,dob,id,GPA);
              Student newStudent = PersonFactory::createStudent(name, age, number, location, dob, id , GPA);
              cout<<"How Many Skills do you want to enter?\n";
              int n;
              cin>>n;
              for(int i=0;i<n;i++)
              {
                  string skill;
                  cout<<"Enter skill "<<i+1<<endl;
                  cin.ignore();
                  cin>>skill;
                  newStudent.addSkill(skill);
              }
                // Use the factory method to create a Student object

                placementSystem.addStudent(newStudent);
             // placementSystem.addStudent(newStudent);

              cout << "Student Registered Successfully!" << endl;
                break;
            }
            case 2: {
                string name, city;
                int companyID, jobOpenings;

                cout << "Enter Company ID: ";
                cin >> companyID;

                cout << "Enter Company Name: ";
                cin.ignore();
                getline(cin, name);

                cout << "Enter Company Location: ";
                getline(cin, city);

                cout << "Enter Number of Job Openings: ";
                cin >> jobOpenings;

                Company newCompany(companyID, name, city, jobOpenings);
                placementSystem.registerCompany(newCompany);
                cout << "Company Registered Successfully!" << endl;
                break;
            }

    case 3: {
    // Display list of students and companies for selection
    cout << "===== Students =====" << endl;
    for (auto& student : placementSystem.getStudents()) {
        cout << student.getName() << " (ID: " << student.getstudentID() << ")" << endl;
    }
    cout << "===== Companies =====" << endl;
    for (auto& company : placementSystem.getCompanies()) {
        cout << company.getName() << " (ID: " << company.getID() << ")" << endl;
    }
    cout << "Enter Student ID and Company ID (separated by space): ";
    int studentID, companyID;
    cin >> studentID >> companyID;

    // Find student and company based on IDs
    Student* selectedStudent = nullptr;
    for (auto& student : placementSystem.getStudents()) {
        if (student.getstudentID() == studentID) {
            selectedStudent = &student;
            break;
        }
    }
    Company* selectedCompany = nullptr;
    for (auto& company : placementSystem.getCompanies()) {
        if (company.getID() == companyID) {
            selectedCompany = &company;
            break;
        }
    }

    if (selectedStudent && selectedCompany) {
        string status, position;
        int duration;

        cout << "Enter Placement Status: ";
        cin.ignore();
        getline(cin, status);

        cout << "Enter Internship Position: ";
        getline(cin, position);

        cout << "Enter Internship Duration (in months): ";
        cin >> duration;

        InternshipRecord internship(selectedStudent,selectedCompany, status, position, duration);
        placementSystem.createInternshipRecord(internship);
    } else {
        cout << "Invalid Student ID or Company ID. Please try again." << endl;
    }
    break;
}


case 4: {
    // Display list of students and companies for selection
    cout << "===== Students =====" << endl;
    for (auto& student : placementSystem.getStudents()) {
        cout << student.getName() << " (ID: " << student.getstudentID() << ")" << endl;
    }
    cout << "===== Companies =====" << endl;
    for ( auto& company : placementSystem.getCompanies()) {
        cout << company.getName() << " (ID: " << company.getID() << ")" << endl;
    }
    cout << "Enter Student ID and Company ID (separated by space): ";
    int studentID, companyID;
    cin >> studentID >> companyID;

    // Find student and company based on IDs
    Student* selectedStudent = nullptr;
    for (auto& student : placementSystem.getStudents()) {
        if (student.getstudentID() == studentID) {
            selectedStudent = &student;
            break;
        }
    }
    Company* selectedCompany = nullptr;
    for (auto& company : placementSystem.getCompanies()) {
        if (company.getID() == companyID) {
            selectedCompany = &company;
            break;
        }
    }

    if (selectedStudent && selectedCompany) {
        string status, position;
        float salary;

        cout << "Enter Placement Status: ";
        cin.ignore();
        getline(cin, status);

        cout << "Enter Job Position: ";
        getline(cin, position);

        cout << "Enter Job Salary: ";
        cin >> salary;

        JobOffer jobOffer(selectedStudent,selectedCompany, status, position, salary);
        placementSystem.createJobOffer(jobOffer);
    } else {
        cout << "Invalid Student ID or Company ID. Please try again." << endl;
    }

    break;
}


            case 5: {
                placementSystem.displayAllStudents();
                break;
            }
            case 6: {
                placementSystem.displayAllCompanies();
                break;
            }
            case 7: {
    // Code for searching student by ID
    int studentID;
    cout << "Enter Student ID: ";
    cin >> studentID;
    placementSystem.searchStudentByID(studentID);
    break;
}
case 8: {
    // Code for searching company by ID
    int companyID;
    cout << "Enter Company ID: ";
    cin >> companyID;
    placementSystem.searchCompanyByID(companyID);
    break;
}
            case 10: {
                cout << "Placement Records Details:" << endl;
                // Loop through the placement records and display their details
                for (  auto& placement : placementSystem.getPlacementRecords()) {
                    placement->displayDetails();
                    cout << endl;
                }
                break;
            }
            case 9: {
    // Code to send notification
    string recipientName, content, date;
    cout << "Enter Recipient Name: ";
    cin.ignore();
    getline(cin, recipientName);

    Person* recipient = nullptr;
    for (auto& student : placementSystem.getStudents()) {
        if (student.getName() == recipientName) {
            recipient = &student;
            break;
        }
    }

    if (recipient) {
        cout << "Enter Content: ";
        getline(cin, content);

        cout << "Enter Date: ";
        cin >> date;

        Notification notification(recipient, content, date);
        placementSystem.notify(notification);
    } else {
        cout << "Recipient not found. Please enter a valid recipient name." << endl;
    }
    break;
}
            case 11:
                {
                int eventID;
                string name;
                string date;
                cout<<"Enter event Id"<<endl;
                cin>>eventID;
                cout<<"Enter event name"<<endl;
                cin>>name;
                cout<<"Enter event date(dd-mm-yyyy)"<<endl;
                cin>>date;
                Event newevent(eventID,name,date);
                placementSystem.addEvent(newevent);
                break;
                }
                case 12:
                {
                string sender;
                string content;
                string date;
                cout<<"Enter Sender's name"<<endl;
                cin>>sender;
                cout<<"Enter feedback"<<endl;
                cin>>content;
                cout<<"Enter event date(dd-mm-yyyy)"<<endl;
                cin>>date;
                Feedback newfeed(sender,content,date);
                placementSystem.addFeedback(newfeed);
                break;
                }
                case 13:
                {
                string interviewer;
                string date;
                string result;
                cout<<"Enter interviewer's name"<<endl;
                cin>>interviewer;
                cout<<"Enter result"<<endl;
                cin>>result;
                cout<<"Enter interview date(dd-mm-yyyy)"<<endl;
                cin>>date;
                Interview newint(interviewer,date,result);
                placementSystem.addInterview(newint);
                break;
                }
                case 14:
                {

                string date;
                cout<<"Enter the date\n";
                cin>>date;
                placementSystem.displayEventsByDate(date);

                break;
                }
                 case 15:
                {


                placementSystem.displayAllFeedbacks();

                break;
                }
                case 16:
                {
                 placementSystem.displayAllInterviews();

                break;
                }




            case 0:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }

        cout << endl;
    } while (choice != 0);

    // Clean up dynamically allocated placement records
    for (auto placement : placementSystem.getPlacementRecords()) {
        delete placement;
    }

    return 0;
}
