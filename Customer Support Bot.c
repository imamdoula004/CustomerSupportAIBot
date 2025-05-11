#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_INPUT 256

// Function prototypes
void showMenu();
bool getConsent();
void storeCustomerInput(const char* name, const char* input);
bool isEscalationRequired(const char* input);
void routeToSupervisor(const char* input);
void aiResponse(int choice);

int main() {
    char customerName[100];
    char rawInput[MAX_INPUT];
    int userChoice;
    bool consentGiven;

    printf("=== Welcome to Customer Support AI ===\n");
    printf("Enter your name: ");
    fgets(customerName, sizeof(customerName), stdin);
    customerName[strcspn(customerName, "\n")] = '\0';  // Remove newline

    printf("\nHello, %s! How can we help you today?\n", customerName);
    showMenu();
    printf("Enter your choice (1-6): ");
    scanf("%d", &userChoice);
    getchar(); // Clear input buffer

    printf("Please describe your issue briefly:\n> ");
    fgets(rawInput, sizeof(rawInput), stdin);
    rawInput[strcspn(rawInput, "\n")] = '\0'; // Remove newline

    // Ask for user consent to store the input
    consentGiven = getConsent();
    if (consentGiven) {
        storeCustomerInput(customerName, rawInput);  // Simulate unsupervised learning
    } else {
        printf("Understood. Your input will not be stored for training.\n");
    }

    aiResponse(userChoice);

    // Check for escalation
    if (isEscalationRequired(rawInput)) {
        printf("\n[AI Supervisor Routing Activated]\n");
        routeToSupervisor(rawInput);
    }

    printf("\nThank you, %s. ", customerName);
    if (consentGiven) {
        printf("Your input has been saved to help improve our AI.\n");
    } else {
        printf("We respect your choice to not store your data.\n");
    }

    return 0;
}

// Show support options
void showMenu() {
    printf("\nChoose your issue type:\n");
    printf("1. Check Order Status\n");
    printf("2. Request Refund\n");
    printf("3. Technical Support\n");
    printf("4. Change Personal Information\n");
    printf("5. Feedback/Complaint\n");
    printf("6. Other\n");
}

// Ask for consent from the user
bool getConsent() {
    char response[10];
    printf("\nWould you like to allow us to store your input to improve our AI model? (yes/no): ");
    fgets(response, sizeof(response), stdin);
    response[strcspn(response, "\n")] = '\0';

    return (strcmp(response, "yes") == 0 || strcmp(response, "Yes") == 0);
}

// Store customer input to a file if consented
void storeCustomerInput(const char* name, const char* input) {
    FILE* file = fopen("ml_raw_data.txt", "a");
    if (file != NULL) {
        fprintf(file, "Customer: %s\nQuery: %s\n---\n", name, input);
        fclose(file);
    } else {
        printf("Error: Could not store input for ML analysis.\n");
    }
}

// Detect if escalation is required
bool isEscalationRequired(const char* input) {
    return strstr(input, "angry") || strstr(input, "escalate") ||
           strstr(input, "manager") || strstr(input, "not happy") ||
           strstr(input, "sue") || strstr(input, "legal");
}

// Route to appropriate supervisor
void routeToSupervisor(const char* input) {
    if (strstr(input, "refund") || strstr(input, "money")) {
        printf("Routing to Finance Supervisor...\n");
    } else if (strstr(input, "technical") || strstr(input, "bug") || strstr(input, "crash")) {
        printf("Routing to Technical Supervisor...\n");
    } else {
        printf("Routing to General Supervisor...\n");
    }
}

// Respond to the customer based on their selection
void aiResponse(int choice) {
    printf("\n[AI Response]\n");
    switch (choice) {
        case 1:
            printf("Your order is being processed. Expected delivery is 3-5 business days.\n");
            break;
        case 2:
            printf("Your refund request has been submitted. It will be processed in 5-7 business days.\n");
            break;
        case 3:
            printf("Please restart your device. If the issue persists, we will escalate it.\n");
            break;
        case 4:
            printf("Please visit your account settings to update your personal information.\n");
            break;
        case 5:
            printf("Thank you for your feedback. We value your opinion and will investigate the matter.\n");
            break;
        case 6:
            printf("Thank you for your query. A representative will follow up shortly if needed.\n");
            break;
        default:
            printf("Invalid selection. Please try again.\n");
            break;
    }
}
