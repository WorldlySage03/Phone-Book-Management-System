#include <bits/stdc++.h>
using namespace std;

#define sp " "
#define el '\n'

struct Node
{
	string name, phone, tag;
	Node *next;

	Node(string n, string p, string t)
	{
		name = n;
		phone = p;
		tag = t;
		next = nullptr;
	}
};

Node *head = nullptr;
int contactCount = 0;
string defaultFileName = "phonebook.dat";

void addContact();
void searchContact();
void editContact();
void deleteContact();
void displayAllContacts();
void displayAlphabetical();
void displayByTags();
void showTotalContactNumber();
void importExportContacts();
void importFromCSV(string &filename);
void exportToCSV(string &filename);
void saveLoadFromFile();
void saveToFile(string &filename);
void loadFromFile(string &filename);
void clearScreen();
void pressEnterToContinue();
void showMenu();

int main()
{
	int choice;
	do
	{
		showMenu();
		cin >> choice;
		switch (choice)
		{
			case 1:
				addContact();
				break;
			case 2:
				searchContact();
				break;
			case 3:
				editContact();
				break;
			case 4:
				deleteContact();
				break;
			case 5:
				displayAllContacts();
				break;
			case 6:
				showTotalContactNumber();
				break;
			case 7:
				importExportContacts();
				break;
			case 8:
				saveLoadFromFile();
				break;
			case 0:
				cout << "Exiting program." << el;
				break;
			default:
				cout << "Invalid choice. Please try again!" << el;
				pressEnterToContinue();
				break;
		}
	} while (choice != 0);

	return 0;
}

void addContact()
{
	clearScreen();
	string name, phone, tag;
	cin.ignore();
	cout << "Enter Name: ";
	getline(cin, name);
	cout << "Enter Phone Number: ";
	getline(cin, phone);
	cout << "Enter Tag (e.g., Family, Friend, Work): ";
	getline(cin, tag);

	Node *newNode = new Node(name, phone, tag);
	if (head == nullptr || head->name >= newNode->name)
	{
		newNode->next = head;
		head = newNode;
	}
	else
	{
		Node *current = head;
		while (current->next != nullptr && current->next->name < newNode->name)
		{
			current = current->next;
		}
		newNode->next = current->next;
		current->next = newNode;
	}
	contactCount++;
	cout << el << "Contact added successfully!" << el;
	pressEnterToContinue();
}

void searchContact()
{
	clearScreen();
	cout << "Search by:" << el;
	cout << "1. Name" << el;
	cout << "2. Phone Number" << el;
	cout << "Enter your choice: ";
	int choice;
	cin >> choice;
	cin.ignore();

	string query;
	bool found = false;
	if (choice == 1)
	{
		cout << "Enter Name to search: ";
		getline(cin, query);
	}
	else if (choice == 2)
	{
		cout << "Enter Phone Number to search: ";
		getline(cin, query);
	}
	else
	{
		cout << "Invalid choice." << el;
		pressEnterToContinue();
		return;
	}

	Node *current = head;
	cout << el << "Search Results:" << el;
	while (current != nullptr)
	{
		if ((choice == 1 && current->name == query) || (choice == 2 && current->phone == query))
		{
			cout << "--------------------------------" << el;
			cout << "Name: " << current->name << el;
			cout << "Phone: " << current->phone << el;
			cout << "Tag: " << current->tag << el;
			cout << "--------------------------------" << el;
			found = true;
		}
		current = current->next;
	}

	if (!found)
	{
		cout << "--------------------------------------------" << el;
		cout << "No contact found with the given details." << el;
		cout << "--------------------------------------------" << el;
	}
	pressEnterToContinue();
}

void editContact()
{
	clearScreen();
	string searchQuery;
	cin.ignore();
	cout << "Enter the name of the contact to edit: ";
	getline(cin, searchQuery);

	Node *current = head;
	while (current != nullptr && current->name != searchQuery)
	{
		current = current->next;
	}

	if (current == nullptr)
	{
		cout << "Contact not found." << el;
	}
	else
	{
		cout << el << "Editing Contact: " << current->name << el;
		cout << "Enter new Name (or press Enter to keep '" << current->name << "'): ";
		string newName;
		getline(cin, newName);

		cout << "Enter new Phone Number (or press Enter to keep '" << current->phone << "'): ";
		string newPhone;
		getline(cin, newPhone);

		cout << "Enter new Tag (or press Enter to keep '" << current->tag << "'): ";
		string newTag;
		getline(cin, newTag);

		if (!newName.empty()) current->name = newName;
		if (!newPhone.empty()) current->phone = newPhone;
		if (!newTag.empty()) current->tag = newTag;

		cout << el << "Contact updated successfully!" << el;
	}
	pressEnterToContinue();
}

void deleteContact()
{
	clearScreen();
	cout << "Delete by:" << el;
	cout << "1. Name" << el;
	cout << "2. Phone Number" << el;
	cout << "Enter your choice: ";
	int choice;
	cin >> choice;
	cin.ignore();
    cout << el;

	string query;
	if (choice == 1)
	{
		cout << "Enter name to delete: ";
		getline(cin, query);
	}
	else if (choice == 2)
	{
		cout << "Enter phone number to delete: ";
		getline(cin, query);
	}
	else
	{
		cout << "Invalid choice." << el;
		pressEnterToContinue();
		return;
	}

	vector<Node*> matches;
	Node *current = head;
	while (current != nullptr)
	{
		if ((choice == 1 && current->name == query) || (choice == 2 && current->phone == query))
		{
			matches.push_back(current);
		}
		current = current->next;
	}

	if (matches.empty())
	{
		cout << "Contact not found." << el;
	}
	else if (matches.size() == 1)
	{
		Node *toDelete = matches[0];
		if (head == toDelete)
		{
			head = toDelete->next;
		}
		else
		{
			Node *temp = head;
			while (temp->next != toDelete)
			{
				temp = temp->next;
			}
			temp->next = toDelete->next;
		}
		contactCount--;
		cout << "Contact deleted successfully." << el;
	}
	else
	{
		cout << "Multiple contacts found. Please choose which one to delete:" << el;
		for (int i = 0; i < matches.size(); ++i)
		{
			cout << i + 1 << ". Name: " << matches[i]->name << ", Phone: " << matches[i]->phone << ", Tag: " << matches[i]->tag << el;
		}
		cout << "Enter your choice (or 0 to cancel): ";
		int deleteChoice;
		cin >> deleteChoice;
		cin.ignore();

		if (deleteChoice > 0 && deleteChoice <= matches.size())
		{
			Node *toDelete = matches[deleteChoice - 1];
			if (head == toDelete)
			{
				head = toDelete->next;
			}
			else
			{
				Node *temp = head;
				while (temp != nullptr && temp->next != toDelete)
				{
					temp = temp->next;
				}
				if (temp != nullptr)
				{
					temp->next = toDelete->next;
				}
			}
			contactCount--;
			cout << "Contact deleted successfully." << el;
		}
		else
		{
			cout << "Deletion cancelled." << el;
		}
	}
	pressEnterToContinue();
}

void displayAllContacts()
{
	clearScreen();
	cout << "Display Options:" << el;
	cout << "1. List All Contacts (Alphabetical)" << el;
	cout << "2. Group by Tags" << el;
	cout << "Enter your choice: ";
	int choice;
	cin >> choice;

	if (choice == 1)
	{
		displayAlphabetical();
	}
	else if (choice == 2)
	{
		displayByTags();
	}
	else
	{
		cout << "Invalid choice." << el;
	}
	pressEnterToContinue();
}

void displayAlphabetical()
{
	clearScreen();
	cout << "All Contacts (Alphabetical Order):" << el;
	cout << "===================================" << el;
	if (head == nullptr)
	{
		cout << "Phone book is empty." << el;
	}
	else
	{
		Node *current = head;
		while (current != nullptr)
		{
			cout << "Name:  " << current->name << el;
			cout << "Phone: " << current->phone << el;
			cout << "Tag:   " << current->tag << el;
			cout << "--------------------------------" << el;
			current = current->next;
		}
	}
}

void displayByTags()
{
	clearScreen();
	cout << "All Contacts (Grouped by Tag):" << el;
	cout << "===================================" << el;
	if (head == nullptr)
	{
		cout << "Phone book is empty." << el;
		return;
	}

	set<string> tags;
	Node *current = head;
	while (current != nullptr)
	{
		tags.insert(current->tag);
		current = current->next;
	}

	for (const auto &tag : tags)
	{
		cout << "------ Tag: " << tag << " ------" << el;
		current = head;
		while (current != nullptr)
		{
			if (current->tag == tag)
			{
				cout << "  Name:  " << current->name << el;
				cout << "  Phone: " << current->phone << el;
				cout << "--------------------------------" << el;
			}
			current = current->next;
		}
		cout << el;
	}
}

void showTotalContactNumber()
{
	clearScreen();
	cout << "Total number of contacts: " << contactCount << el;
	pressEnterToContinue();
}

void importExportContacts()
{
	clearScreen();
	cout << "Import/Export Contacts:" << el;
	cout << "1. Import from CSV" << el;
	cout << "2. Export to CSV" << el;
	cout << "Enter choice: ";
	int choice;
	cin >> choice;
	cin.ignore();

	string filename;
	cout << "Enter CSV filename (e.g., contacts.csv): ";
	getline(cin, filename);

	if (choice == 1)
	{
		importFromCSV(filename);
	}
	else if (choice == 2)
	{
		exportToCSV(filename);
	}
	else
	{
		cout << "Invalid choice." << el;
	}
	pressEnterToContinue();
}

void importFromCSV(string &filename)
{
	ifstream file(filename);
	if (!file.is_open())
	{
		cout << "Error: Could not open file " << filename << el;
		return;
	}

	string line, name, phone, tag;
	int importedCount = 0;
	getline(file, line);

	while (getline(file, line))
	{
		stringstream ss(line);
		getline(ss, name, ',');
		getline(ss, phone, ',');
		getline(ss, tag, ',');

		Node *newNode = new Node(name, phone, tag);
		if (head == nullptr || head->name >= newNode->name)
		{
			newNode->next = head;
			head = newNode;
		}
		else
		{
			Node *current = head;
			while (current->next != nullptr && current->next->name < newNode->name)
			{
				current = current->next;
			}
			newNode->next = current->next;
			current->next = newNode;
		}
		contactCount++;
		importedCount++;
	}
	file.close();
	cout << importedCount << " contacts imported successfully." << el;
}

void exportToCSV(string &filename)
{
	ofstream file(filename);
	if (!file.is_open())
	{
		cout << "Error: Could not create file " << filename << el;
		return;
	}

	file << "Name,Phone,Tag" << el;
	Node *current = head;
	while (current != nullptr)
	{
		file << current->name << "," << current->phone << "," << current->tag << el;
		current = current->next;
	}
	file.close();
	cout << "Contacts exported successfully to " << filename << el;
}

void saveLoadFromFile()
{
	clearScreen();
	cout << "Save/Load Options:" << el;
	cout << "1. Save contacts to file" << el;
	cout << "2. Load contacts from file" << el;
	cout << "Enter choice: ";
	int choice;
	cin >> choice;

	if (choice == 1)
	{
		saveToFile(defaultFileName);
	}
	else if (choice == 2)
	{
		loadFromFile(defaultFileName);
	}
	else
	{
		cout << "Invalid choice." << el;
	}
	pressEnterToContinue();
}

void saveToFile(string &filename)
{
	ofstream file(filename, ios::out | ios::binary);
	if (!file.is_open())
	{
		cout << "Error saving contacts." << el;
		return;
	}
	Node *current = head;
	while (current != nullptr)
	{
		int nameLen = current->name.length();
		int phoneLen = current->phone.length();
		int tagLen = current->tag.length();
		file.write(reinterpret_cast<const char *>(&nameLen), sizeof(nameLen));
		file.write(current->name.c_str(), nameLen);
		file.write(reinterpret_cast<const char *>(&phoneLen), sizeof(phoneLen));
		file.write(current->phone.c_str(), phoneLen);
		file.write(reinterpret_cast<const char *>(&tagLen), sizeof(tagLen));
		file.write(current->tag.c_str(), tagLen);
		current = current->next;
	}
	file.close();
	cout << "Contacts saved successfully to " << filename << el;
}

void loadFromFile(string &filename)
{
	ifstream file(filename, ios::in | ios::binary);
	if (!file.is_open())
	{
		cout << "No saved data found or could not open file." << el;
		return;
	}

	while (head != nullptr)
	{
		Node *temp = head;
		head = head->next;
		delete temp;
	}
	contactCount = 0;

	while (file.peek() != EOF)
	{
		int nameLen, phoneLen, tagLen;
		file.read(reinterpret_cast<char *>(&nameLen), sizeof(nameLen));
		char *nameBuf = new char[nameLen + 1];
		file.read(nameBuf, nameLen);
		nameBuf[nameLen] = '\0';
		string name(nameBuf);
		delete[] nameBuf;

		file.read(reinterpret_cast<char *>(&phoneLen), sizeof(phoneLen));
		char *phoneBuf = new char[phoneLen + 1];
		file.read(phoneBuf, phoneLen);
		phoneBuf[phoneLen] = '\0';
		string phone(phoneBuf);
		delete[] phoneBuf;

		file.read(reinterpret_cast<char *>(&tagLen), sizeof(tagLen));
		char *tagBuf = new char[tagLen + 1];
		file.read(tagBuf, tagLen);
		tagBuf[tagLen] = '\0';
		string tag(tagBuf);
		delete[] tagBuf;

		Node *newNode = new Node(name, phone, tag);
		if (head == nullptr || head->name >= newNode->name)
		{
			newNode->next = head;
			head = newNode;
		}
		else
		{
			Node *current = head;
			while (current->next != nullptr && current->next->name < newNode->name)
			{
				current = current->next;
			}
			newNode->next = current->next;
			current->next = newNode;
		}
		contactCount++;
	}
	file.close();
	cout << "Contacts loaded successfully from " << filename << el;
}

void showMenu()
{
	clearScreen();
	cout << "========= Phone Book Menu =========" << el;
	cout << "1. Add Contact" << el;
	cout << "2. Search Contact" << el;
	cout << "3. Edit Contact" << el;
	cout << "4. Delete Contact" << el;
	cout << "5. Display All Contacts" << el;
	cout << "6. Show Total Contact Number" << el;
	cout << "7. Import/Export Contacts (CSV)" << el;
	cout << "8. Save/Load from File" << el;
	cout << "0. Exit" << el;
	cout << "===================================" << el;
	cout << "Enter your choice: ";
}

void clearScreen()
{
	system("cls");
}

void pressEnterToContinue()
{
	cout << el << "Press Enter to continue...";
	cin.ignore();
	getchar();
}
