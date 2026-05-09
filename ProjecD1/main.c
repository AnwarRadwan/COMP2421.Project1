#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Define structures for Polynomial and Stack
typedef struct polynomial* Polynomial;
typedef struct stack* Stack;

struct polynomial {
    int coefficients;  // Coefficient of the term
    int exponent;      // Exponent of the term
    Polynomial Next;   // Pointer to the next term in the polynomial
};

struct stack {
    int numberOfPoly;  // Number of polynomials in the stack
    Polynomial element; // Pointer to a polynomial
    Stack Next;         // Pointer to the next stack element
};

// Function declarations
void loadOfFile(Stack);
Polynomial createPolynomial();
Polynomial lastPolynomial(Polynomial);
void insertPolynomial(Polynomial, int, int);
void printMenu();
void print(Stack);
void printP(Polynomial);
int isEmpty(Polynomial);
int isEmptyS(Stack);
Stack createStack();
void Push(Polynomial, int, Stack);
Polynomial Pop(Stack);
Polynomial top(Stack);
Stack add(Stack);
Stack sub(Stack);
Stack multiply(Stack);
Stack stackCpy(Stack);
Polynomial sumOfDuplicatOfExponent(Polynomial);
void saveToFile(Stack, Stack, Stack);
void DeleteList(Polynomial);
void makeEmptyP(Polynomial);
void makeEmptyS(Stack);
void Exist(Stack, Stack, Stack, Stack);

// Main function: the entry point of the program
int main(void) {
    int stop = 1;  // Flag to stop the loop
    int choose;    // Variable to store user input for menu choices
    Stack head = createStack();   // Stack to store the polynomials
    Stack Add = createStack();    // Stack for addition results
    Stack Sub = createStack();    // Stack for subtraction results
    Stack Multiply = createStack(); // Stack for multiplication results

    while(stop) {
        printMenu();  // Print the menu for the user
        scanf("%d", &choose);  // Get the user's choice
        switch(choose) {
            case 1:
                loadOfFile(head);  // Load polynomials from a file
                break;
            case 2:
                print(head);  // Print all polynomials in the stack
                break;
            case 3:
                Add = stackCpy(head);  // Copy the stack for addition
                Add = stackCpy(Add);   // Make another copy
                add(Add);  // Perform addition
                print(Add);  // Print the result
                break;
            case 4:
                Sub = stackCpy(head);  // Copy the stack for subtraction
                Sub = stackCpy(Sub);   // Make another copy
                sub(Sub);  // Perform subtraction
                print(Sub);  // Print the result
                break;
            case 5:
                Multiply = stackCpy(head);  // Copy the stack for multiplication
                Multiply = stackCpy(Multiply);  // Make another copy
                multiply(Multiply);  // Perform multiplication
                print(Multiply);  // Print the result
                break;
            case 6:
                // Print the results of addition, subtraction, and multiplication
                printf("ADD : ");
                print(Add);
                printf("SUB : ");
                print(Sub);
                printf("MULTIPLY : ");
                print(Multiply);
                break;
            case 7:
                saveToFile(Add, Sub, Multiply);  // Save results to a file
                break;
            case 8:
                Exist(head, Add, Sub, Multiply);  // Clear all stacks and free memory
                printf("Good Bye Friend....\n");
                stop = 0;  // Stop the program
                break;
            default:
                printf("Enter a valid Number From The choices\n\n");
                continue;  // Continue if the input is invalid
        }
    }

    return 0;  // Exit the program
}

// Function to load polynomials from a file
void loadOfFile(Stack S) {
    FILE* input = fopen("input.txt", "r");  // Open the file for reading
    if(!input) {
        printf("Error opening file.\n");
        return;
    }
    char polyData[50];  // String to hold the polynomial data
    char temp[10];  // Temporary string for processing coefficients
    int sign[10];  // Array to hold the signs of the terms
    int coo, ex, j;
    Polynomial P;
    int numberOfP = 0;  // Counter for the number of polynomials

    // Read each polynomial line by line from the file
    while(fgets(polyData, sizeof(polyData), input)) {
        P = createPolynomial();  // Create a new polynomial
        j = 0;
        if(polyData[0] != '-')
            sign[j++] = 1;
        for(int i = 0; i < strlen(polyData); i++) {
            if(polyData[i] == '+')
                sign[j++] = 1;  // Assign + sign
            if(polyData[i] == '-')
                sign[j++] = -1;  // Assign - sign
        }

        // Tokenize the string based on + and -
        char *token = strtok(polyData, "+-");
        j = 0;
        while (token != NULL) {
            strcpy(temp, token);  // Copy token to temp string
            if(temp != NULL)
                coo = atoi(temp);  // Convert string to integer coefficient
            if(coo == 0) coo = 1;  // If coefficient is 0, set it to 1
            coo = sign[j++] * coo;  // Multiply by sign
            char tempExp[5] = "";  // To hold the exponent part
            char *exp1 = strchr(temp, '^');  // Find the exponent part
            if(exp1 != NULL)
                for(int i = 0; i < strlen(exp1); i++) {
                    if(i != strlen(exp1)-1)
                        tempExp[i] = exp1[i + 1];
                }
            ex = atoi(tempExp);  // Convert exponent to integer
            insertPolynomial(P, coo, ex);  // Insert the term into the polynomial
            token = strtok(NULL, "+-");  // Get the next token
        }
        Push(P, ++numberOfP, S);  // Push the polynomial to the stack
    }
}

// Function to print the menu
void printMenu() {
    printf("1. Load the polynomials' file \n"
           "2. Print the polynomials\n"
           "3. Add the polynomials \n"
           "4. Subtract the polynomials \n"
           "5. Multiply the polynomials\n"
           "6. Print the results to the screen \n"
           "7. Print the results to file \n"
           "8. Exit\n"
           "Select one of the options : ");
}

// Function to create a new polynomial (linked list)
Polynomial createPolynomial() {
    Polynomial P = (Polynomial)malloc(sizeof(struct polynomial));  // Allocate memory
    if(P == NULL) {
        printf("Polynomial List can not be defined");
        return NULL;
    } else {
        P->Next = NULL;  // Initialize the next pointer to NULL
        return P;
    }
}

// Function to find the last polynomial node
Polynomial lastPolynomial(Polynomial P) {
    while(!isEmpty(P)) {
        P = P->Next;  // Traverse to the last polynomial node
    }
    return P;
}

// Function to insert a polynomial term (coefficient and exponent) into the list
void insertPolynomial(Polynomial P, int coo, int ex) {
    while(!isEmpty(P)) {
        if(P->exponent == ex){
            P->coefficients+=coo;
            return;
        }
            P = P->Next;  // Traverse to the last polynomial node
    }
    Polynomial element = createPolynomial();  // Create a new term
    element->exponent = ex;  // Set the exponent
    element->coefficients = coo;  // Set the coefficient
    element->Next = P->Next;  // Insert the new term at the end
    P->Next = element;  // Update the last node's Next pointer
}

// Function to print a stack of polynomials
void print(Stack S) {
    Stack ptrS = S;  // Pointer to the stack
    Polynomial ptrP;  // Pointer to the polynomial
    if(isEmptyS(S)) {
        printf("Stack is empty\n");
    } else {
        while(!isEmptyS(ptrS)) {
            ptrS = ptrS->Next;  // Traverse through the stack
            ptrP = ptrS->element;  // Get the polynomial from the stack
            printf("Polynomial %d : ", ptrS->numberOfPoly);  // Print polynomial number
            printP(ptrP);  // Print the polynomial itself
        }
        printf("\n");
    }
}

// Function to print a single polynomial
void printP(Polynomial P) {
    Polynomial ptr = P;  // Pointer to the polynomial
    while(!isEmpty(ptr)) {
        ptr = ptr->Next;  // Traverse the polynomial terms
        if(isEmpty(ptr)) {
            if(ptr->exponent == 0)
                printf("%d", ptr->coefficients, ptr->exponent);  // Print constant term
            else
                printf("%dx^%d", ptr->coefficients, ptr->exponent);  // Print terms with exponents
            break;
        }
        printf("%dx^%d+", ptr->coefficients, ptr->exponent);  // Print the term with +
    }
    printf("\n");
}

// Check if a polynomial list is empty
int isEmpty(Polynomial P) {
    return P->Next == NULL;  // Return true if the list is empty
}

// Check if a stack is empty
int isEmptyS(Stack S) {
    return S->Next == NULL;  // Return true if the stack is empty
}

// Create a new stack
Stack createStack() {
    Stack newStack = (Stack)malloc(sizeof(struct stack));  // Allocate memory for stack
    if(newStack == NULL) {
        printf("Stack cannot be defined\n");
        return NULL;
    } else {
        newStack->Next = NULL;  // Initialize the stack's top pointer to NULL
        return newStack;
    }
}

// Push a polynomial onto the stack
void Push(Polynomial P, int number, Stack S) {
    Stack temp = (Stack)malloc(sizeof(struct stack));
    if (temp == NULL)
        printf("Out of space!");  // Handle memory allocation failure
    else {
        temp->element = P;            // Store polynomial P in stack element
        temp->numberOfPoly = number;  // Store the polynomial number in the stack
        temp->Next = S->Next;         // Link the next pointer to the current top of the stack
        S->Next = temp;               // Update stack's top pointer to the new node
    }
}

// Pop a polynomial from the stack
Polynomial Pop(Stack S) {
    Stack firstCell;
    Polynomial ptrP = createPolynomial();
    ptrP = S->element;
    if (isEmptyS(S))
        printf("Empty stack\n");  // Handle empty stack
    else {
        firstCell = S->Next;             // Get the top stack element
        ptrP = S->Next->element;         // Get the polynomial from the top element
        S->Next = S->Next->Next;         // Update stack to point to the next element
        free(firstCell);                 // Free the memory of the popped element
    }
    return ptrP;
}

// Get the top polynomial of the stack without removing it
Polynomial top(Stack S) {
    if (!isEmptyS(S)) {
        Polynomial ptr = S->Next->element;
        return ptr;  // Return the top polynomial
    }
}

// Perform addition of polynomials in the stack
Stack add(Stack S) {
    Stack ptrS = S;
    Polynomial q, r, deleteQ, deleteR;
    int coo;
    Polynomial newLinke;
    while (!isEmptyS(ptrS->Next)){
        q = Pop(ptrS);  // Pop two polynomials
        r = Pop(ptrS);
        deleteQ = q;
        deleteR = r;
        r = r->Next;  // Move to the next term in both polynomials
        q = q->Next;
        newLinke = createPolynomial();  // Create a new polynomial for the result
        while (r != NULL || q != NULL) {  // Traverse both polynomials
            if (r != NULL && q != NULL) {  // Both polynomials still have terms
                if (r->exponent == q->exponent) {  // If exponents match, add coefficients
                    coo = r->coefficients + q->coefficients;
                    insertPolynomial(newLinke, coo, q->exponent);  // Insert term in result
                    r = r->Next;
                    q = q->Next;
                } else if (r->exponent > q->exponent) {  // If r's exponent is greater
                    insertPolynomial(newLinke, r->coefficients, r->exponent);
                    r = r->Next;
                } else {  // If q's exponent is greater
                    insertPolynomial(newLinke, q->coefficients, q->exponent);
                    q = q->Next;
                }
            } else if (r != NULL) {  // If only r has terms left
                insertPolynomial(newLinke, r->coefficients, r->exponent);
                r = r->Next;
            } else {  // If only q has terms left
                insertPolynomial(newLinke, q->coefficients, q->exponent);
                q = q->Next;
            }
        }
        Push(newLinke, 1, ptrS);  // Push the resulting polynomial back to the stack
        makeEmptyP(deleteQ);  // Clear the memory of the popped polynomials
        makeEmptyP(deleteR);
    }
    free(q);
    free(r);
    return ptrS;  // Return the updated stack
}

// Perform subtraction of polynomials in the stack
Stack sub(Stack S) {
    Stack ptrS = S;
    Polynomial q, r, deleteQ, deleteR;
    int coo, sign;
    Polynomial newLinke;
    while (!isEmptyS(ptrS->Next)) {
        q = Pop(ptrS);  // Pop two polynomials
        r = Pop(ptrS);
        deleteR = r;
        deleteQ = q;
        r = r->Next;  // Move to the next term in both polynomials
        q = q->Next;
        newLinke = createPolynomial();  // Create a new polynomial for the result
        while (r != NULL || q != NULL) {  // Traverse both polynomials
            if (r != NULL && q != NULL) {  // Both polynomials still have terms
                if (r->exponent == q->exponent) {  // If exponents match, subtract coefficients
                    coo = q->coefficients - r->coefficients;
                    insertPolynomial(newLinke, coo, q->exponent);
                    r = r->Next;
                    q = q->Next;
                } else if (r->exponent > q->exponent) {  // If r's exponent is greater
                    sign = -1 * r->coefficients;  // Negate r's coefficient
                    insertPolynomial(newLinke, sign, r->exponent);
                    r = r->Next;
                } else {  // If q's exponent is greater
                    insertPolynomial(newLinke, q->coefficients, q->exponent);
                    q = q->Next;
                }
            } else if (r != NULL) {  // If only r has terms left
                sign = -1 * r->coefficients;
                insertPolynomial(newLinke, sign, r->exponent);
                r = r->Next;
            } else {  // If only q has terms left
                insertPolynomial(newLinke, q->coefficients, q->exponent);
                q = q->Next;
            }
        }
        Push(newLinke, 1, ptrS);  // Push the resulting polynomial back to the stack
        makeEmptyP(deleteQ);  // Clear the memory of the popped polynomials
        makeEmptyP(deleteR);
    }
    free(q);
    free(r);
    return ptrS;  // Return the updated stack
}

// Perform multiplication of polynomials in the stack
Stack multiply(Stack S) {
    Stack ptrS = S;
    Polynomial q, r, deleteQ, deleteR;
    int coo1, ex1;
    Polynomial newLinke;
    while (!isEmptyS(ptrS->Next)) {
        q = Pop(ptrS);  // Pop two polynomials
        r = Pop(ptrS);
        deleteR = r;
        deleteQ = q;
        r = r->Next;  // Move to the next term in both polynomials
        q = q->Next;
        newLinke = createPolynomial();  // Create a new polynomial for the result
        while (r != NULL) {  // Traverse the terms of the second polynomial
            Polynomial ptr = q;
            while (ptr != NULL) {  // Traverse the terms of the first polynomial
                ex1 = r->exponent + ptr->exponent;  // Add the exponents
                coo1 = r->coefficients * ptr->coefficients;  // Multiply the coefficients
                insertPolynomial(newLinke, coo1, ex1);  // Insert the new term in the result
                ptr = ptr->Next;
            }
            r = r->Next;
        }
        Push(newLinke, 1, ptrS);  // Push the resulting polynomial back to the stack
        makeEmptyP(deleteQ);  // Clear the memory of the popped polynomials
        makeEmptyP(deleteR);
    }
    return ptrS;  // Return the updated stack
}
Polynomial sumOfDuplicatOfExponent(Polynomial P){
    Polynomial r = P;  // Move to the next term in both polynomials
    Polynomial q = P;
    r = r->Next;  // Move to the next term in both polynomials
    q = q->Next;
    int coo,ex;
    Polynomial newLinke = createPolynomial();  // Create a new polynomial for the result
    while (r != NULL || q != NULL) {  // Traverse both polynomials
        if (r != NULL && q != NULL) {  // Both polynomials still have terms
            if (r->exponent == q->exponent) {  // If exponents match, add coefficients
                coo = r->coefficients + q->coefficients;
                insertPolynomial(newLinke, coo/2, q->exponent);  // Insert term in result
                r = r->Next;
                q = q->Next;
            } else if (r->exponent > q->exponent) {  // If r's exponent is greater
                insertPolynomial(newLinke, r->coefficients/2, r->exponent);
                r = r->Next;
            } else {  // If q's exponent is greater
                insertPolynomial(newLinke, q->coefficients /2, q->exponent);
                q = q->Next;
            }
        } else if (r != NULL) {  // If only r has terms left
            insertPolynomial(newLinke, r->coefficients/2, r->exponent);
            r = r->Next;
        } else {  // If only q has terms left
            insertPolynomial(newLinke, q->coefficients/2, q->exponent);
            q = q->Next;
        }
    }
    return newLinke;
}
// Create a copy of the stack
Stack stackCpy(Stack S) {
    Stack ptrS = S;
    Stack newStack = createStack();  // Create a new stack
    Polynomial ptrP;
    Polynomial newLinke;
    int numberOfP = 0;
    int coo, ex;
    while (!isEmptyS(ptrS)) {
        ptrS = ptrS->Next;
        ptrP = ptrS->element;
        newLinke = createPolynomial();
        while (!isEmpty(ptrP)) {
            ptrP = ptrP->Next;
            coo = ptrP->coefficients;
            ex = ptrP->exponent;
            insertPolynomial(newLinke, coo, ex);  // Copy terms from the original polynomial
        }
        Push(newLinke, ++numberOfP, newStack);  // Push the copied polynomial to the new stack
    }
    return newStack;  // Return the copied stack
}

// Save the polynomials to an output file
void saveToFile(Stack Add, Stack Sub, Stack Multiply) {
    Stack temp[3];
    temp[0] = Add;
    temp[1] = Sub;
    temp[2] = Multiply;

    if (isEmptyS(temp[0]) && isEmptyS(temp[1]) && isEmptyS(temp[2])) {
        printf("Can't save to output file since all operation lists are empty!\n\n");
        return;  // Exit if all stacks are empty
    }
    FILE* output1 = fopen("output.txt", "w");
    if (output1 == NULL) {
        printf("Error opening output.txt file\n");
        return;
    }
    // Write the results of each operation to the output file
    for (int i = 0; i < 3; i++) {
        while (!isEmptyS(temp[i])) {
            if (i == 0)
                fprintf(output1, "ADD :");
            else if (i == 1)
                fprintf(output1, "SUB :");
            else
                fprintf(output1, "MULTIPLY :");
            temp[i] = temp[i]->Next;
            Polynomial ptr = temp[i]->element;
            while (!isEmpty(ptr)) {
                ptr = ptr->Next;
                if (isEmpty(ptr)) {
                    if (ptr->exponent == 0)
                        fprintf(output1, "%d", ptr->coefficients, ptr->exponent);
                    else
                        fprintf(output1, "%dx^%d", ptr->coefficients, ptr->exponent);
                    break;
                }
                fprintf(output1, "%dx^%d+", ptr->coefficients, ptr->exponent);
            }
            fprintf(output1, "\n");
        }
    }
    printf("Data saved to file successfully..\n");
    fclose(output1);  // Close the file
}

// Delete the entire polynomial list
void DeleteList(Polynomial P) {
    Polynomial ptr, temp;
    ptr = P->Next;
    P->Next = NULL;
    while (ptr != NULL) {
        temp = ptr->Next;
        free(ptr);  // Free the node memory
        ptr = temp;
    }
}

// Empty a polynomial list
void makeEmptyP(Polynomial P) {
    if (P != NULL)
        DeleteList(P);  // Delete the existing list
    P = createPolynomial();  // Create a new empty polynomial
    if (P == NULL)
        printf("Out of memory!\n");
    P->Next = NULL;
}

// Empty the entire stack
void makeEmptyS(Stack S) {
    Polynomial temp;
    if (isEmptyS(S)) {
        printf("The stack does not exist to be cleared..\n");
        return;  // Exit if the stack is already empty
    } else {
        while (!isEmptyS(S)) {
            temp = Pop(S);  // Pop each polynomial from the stack
            makeEmptyP(temp);  // Clear each polynomial
            free(temp);  // Free memory
        }
    }
}

// Clear all stacks and free memory
void Exist(Stack head, Stack add, Stack sub, Stack mul) {
    Stack temp[4];
    temp[0] = head;
    temp[1] = add;
    temp[2] = sub;
    temp[3] = mul;
    for (int i = 0; i < 4; i++) {
        makeEmptyS(temp[i]);  // Empty each stack
        free(temp[i]);  // Free memory of each stack
    }
}