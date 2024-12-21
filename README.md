# Blockchain-Based-Property-Ownership-and-Transfer-System

This project is a blockchain-based application designed to manage property ownership and secure property transfer. It ensures transparency, immutability, and robust security for transactions using blockchain technology.

## Features

- **Transaction Verification**: Verifies the authenticity of transactions using a custom SHA-256 hashing mechanism.
- **Secure Transactions**: Implements Zero-Knowledge Proofs to validate property ownership without revealing sensitive details.
- **Blockchain Mining**: Mines blocks with a specified difficulty level, ensuring transaction immutability.
- **User-Friendly Interface**: Allows users to add transactions and view property ownership details via a menu-driven CLI.

## Technologies Used

- **Programming Language**: C++
- **Cryptographic Algorithms**: Custom implementation of SHA-256 for hashing and modular exponentiation for secure calculations.

## How It Works

1. **Property Registration**:
   - Users can register property details, which are securely stored as transactions in the blockchain.

2. **Transaction Verification**:
   - A Zero-Knowledge Proof mechanism ensures the validity of each transaction.

3. **Mining**:
   - The system mines blocks by finding a valid nonce that meets the difficulty criteria.

4. **Viewing Transactions**:
   - Users can query the blockchain to view all transactions related to a specific property or owner.

## Getting Started

### Prerequisites

- A C++ compiler (e.g., GCC, Clang)
- Basic understanding of blockchain concepts

### Compilation and Execution

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/blockchain-property-system.git
   ```

2. Navigate to the project directory:
   ```bash 
   cd blockchain-property-system
   ```
3. Compile the project:
   ```bash 
   g++ -o blockchain main.cpp
   ```
3. Run the application:
   ```bash 
   ./blockchain
   ```
# Usage
## Create and Verify Transaction:

Enter a username and a private key value to create a transaction.
The system verifies the transaction and mines a block if valid.

# View Transactions:
Input a username to view all transactions associated with that user.

# Exit:
Exit the application.

# Future Improvements
Integration with a web-based front-end for enhanced accessibility.
Support for more complex property-related transactions.
Improved performance for large-scale property registries.
