# ATM Management System

![License](https://img.shields.io/badge/license-MIT-blue.svg)

## 📖 Overview

The **ATM Management System** is a C-based application designed to manage user accounts and transactions within an ATM environment. This project showcases the use of fundamental C programming concepts, data manipulation through file handling, memory management, and system-level features like pipes and child processes.

This repository is developed and maintained by [Maurice Ombewa](https://github.com/MauriceOmbewa) and can be found [here](https://github.com/MauriceOmbewa/atm-management-system.git).

## 📂 File Structure

```
.
├── data
│   ├── records.txt      # Stores account information
│   └── users.txt        # Stores user login details
├── src
│   ├── auth.c           # Handles authentication
│   ├── header.h         # Header file with shared definitions
│   ├── main.c           # Main program logic
│   └── system.c         # Core ATM functionalities
├── LICENSE             # License information
├── Makefile             # Build instructions
└── README.md            # Project description
```

### **Data Files**

- **`users.txt`** – Stores user details in the format:
  ```
  id name password
  0 Alice 1234password
  1 Michel password1234
  ```

- **`records.txt`** – Stores account information in the format:
  ```
  id user_id user_name account_id creation_date country phone_number balance account_type
  0 0 Alice 0 10/02/2020 german 986134231 11090830.00 current
  1 1 Michel 2 10/10/2021 portugal 914134431 1920.42 savings
  2 0 Alice 1 10/10/2000 finland 986134231 1234.21 savings
  ```

## ⚙️ Features

### ✅ **Implemented Functionalities:**

1. **User Registration**
   - Users must have unique usernames.
   - Store new users in `users.txt`.

2. **Update Account Information**
   - Update country or phone number.
   - Prompt for the account ID and field to update.
   - Save changes to `records.txt`.

3. **View Account Details**
   - View details of a specific account using its ID.
   - Interest rates based on account type:
     - **Savings**: 7%
     - **Fixed01 (1 year)**: 4%
     - **Fixed02 (2 years)**: 5%
     - **Fixed03 (3 years)**: 8%
     - **Current**: No interest

4. **Make Transactions**
   - Deposit/withdraw funds.
   - Transactions disabled for Fixed accounts.
   - Save updates to `records.txt`.

5. **Delete Accounts**
   - Users can delete their own accounts.
   - Reflect changes in the corresponding file.

6. **Transfer Account Ownership**
   - Transfer an account to another user.
   - Update `records.txt` with the new owner’s details.
7. **Login/Register**
   - Users can create new accounts and log in.
8. **List Owned Accounts**
   - View all accounts owned by a user.

## 💾 Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/MauriceOmbewa/atm-management-system.git
   cd atm-management-system
   ```

2. **Build the project:**
   ```bash
   make
   ```

3. **Run the application:**
   ```bash
   ./atm
   ```

## 🖥️ Usage

1. **Login/Register** to the system.
2. **Navigate** through options:
   - View, update, or delete accounts.
   - Perform transactions.
   - Transfer account ownership.
3. **Log out** when done.

## 📊 Learning Outcomes

By completing this project, I gained experience with:

- C Programming Language
- Data Structures and Memory Management
- File Handling in C
- System Calls (pipes, child processes)

## 📃 License

This project is licensed under the [MIT License](LICENSE).
