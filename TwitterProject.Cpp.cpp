#include <iostream>
#include <vector>
#include <string>

struct User {
    std::string username;
    std::string password;  
};

struct Post {
    std::string author;
    std::string content;
};

std::vector<User> users;
std::vector<Post> posts;
User* currentUser = nullptr;

void createUser(const std::string& username, const std::string& password) {
    users.push_back({username, password});
}

User* findUser(const std::string& username) {
    for (auto& user : users) {
        if (user.username == username) {
            return &user;
        }
    }
    return nullptr;
}

bool loginUser(const std::string& username, const std::string& password) {
    User* user = findUser(username);
    if (user && user->password == password) {
        currentUser = user;
        return true;
    }
    return false;
}

void createPost(const std::string& content) {
    posts.push_back({currentUser->username, content});
}

void viewPosts() {
    std::cout << "\n--- View Posts ---\n";

    // Ask for the username whose posts the user wants to see
    std::string targetUsername;
    std::cout << "Enter the username to view their posts: ";
    std::cin >> targetUsername;

    // Find the user with the entered username
    User* targetUser = findUser(targetUsername);
    if (!targetUser) {
        std::cout << "User not found.\n";
        return;
    }

    std::cout << "\nOptions:\n1. View All Posts\n2. View Individual Posts\nEnter your choice: ";
    char viewChoice;
    std::cin >> viewChoice;

    switch (viewChoice) {
        case '1':
            // View all posts from the target user
            std::cout << "\n--- All Posts by " << targetUser->username << " ---\n";
            for (const auto& post : posts) {
                if (post.author == targetUser->username) {
                    std::cout << post.content << "\n";
                }
            }
            std::cout << "-------------------------\n";
            break;

        case '2':
            // View individual posts
            int postIndex;
            std::cout << "Enter the index of the post to view: ";
            std::cin >> postIndex;

            if (postIndex >= 0 && postIndex < posts.size() && posts[postIndex].author == targetUser->username) {
                std::cout << posts[postIndex].content << "\n";
            } else {
                std::cout << "Invalid post index or not authored by the selected user.\n";
            }
            break;

        default:
            std::cout << "Invalid choice.\n";
    }
}

int main() {
    char choice;
    do {
        // Display menu options
        std::cout << "\nMenu:\n1. Sign Up\n2. Log In\n3. Create Post\n4. View Posts\n5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                // Sign Up
                {
                    std::string username, password;
                    std::cout << "Enter your desired username: ";
                    std::cin >> username;

                    // Check if the username already exists
                    if (findUser(username)) {
                        std::cout << "Username already exists. Choose a different one.\n";
                        break;
                    }

                    std::cout << "Enter your password: ";
                    std::cin >> password;

                    createUser(username, password);
                    std::cout << "Account created successfully!\n";
                }
                break;

            case '2':
                // Log In
                {
                    std::string username, password;
                    std::cout << "Enter your username: ";
                    std::cin >> username;
                    std::cout << "Enter your password: ";
                    std::cin >> password;

                    if (loginUser(username, password)) {
                        std::cout << "Login successful!\n";
                    } else {
                        std::cout << "Invalid username or password. Please try again.\n";
                    }
                }
                break;

            case '3':
                // Create a post
                if (currentUser) {
                    std::string content;
                    std::cout << "Enter your post: ";
                    std::cin.ignore(); // Clear newline from the buffer
                    std::getline(std::cin, content);
                    createPost(content);
                    std::cout << "Post created!\n";
                } else {
                    std::cout << "You need to log in first.\n";
                }
                break;

            case '4':
                // View all posts
                if (currentUser) {
                    viewPosts();
                } else {
                    std::cout << "You need to log in first.\n";
                }
                break;

            case '5':
                std::cout << "Exiting...\n";
                break;

            default:
                std::cout << "Invalid choice. Try again.\n";
        }

    } while (choice != '5');

    return 0;
}
