//
// Created by Misha on 07.04.2024.
//
#include <stdio.h>
#include <stdlib.h>

// Assuming the IS_PRINTED status is defined as follows:
#define IS_PRINTED 1

// Minimal Document structure for testing purposes
typedef struct Document {
    int document_printing_status;
    struct Document *next;
} Document;

// Function to be tested
int get_nr_of_printed_docs(Document *head_doc);

// Helper function to create a new Document
Document* create_document(int status) {
    Document* newDoc = (Document*)malloc(sizeof(Document));
    if (newDoc) {
        newDoc->document_printing_status = status;
        newDoc->next = NULL;
    }
    return newDoc;
}

// Helper function to append a document to the list
void append_document(Document** head, int status) {
    Document* newDoc = create_document(status);
    if (!(*head)) {
        *head = newDoc;
    } else {
        Document* temp = *head;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newDoc;
    }
}

// Test function
void test_get_nr_of_printed_docs() {
    Document* head = NULL;
    append_document(&head, IS_PRINTED);
    append_document(&head, 0); // Not printed
    append_document(&head, IS_PRINTED);
    append_document(&head, IS_PRINTED);

    int printedDocs = get_nr_of_printed_docs(head);
    if (printedDocs == 3) {
        printf("Test passed: Correct number of printed documents.\n");
    } else {
        printf("Test failed: Incorrect number of printed documents. Expected 3, got %d.\n", printedDocs);
    }

    // Free allocated memory
    Document* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    test_get_nr_of_printed_docs();
    return 0;
}