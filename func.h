#ifndef _FUNC_H_
#define _FUNC_H_
#include <stdbool.h>
#include "struct.h"

/**
 * Generates a random number within a specified range.
 *
 * @param min The minimum value in the range.
 * @param max The maximum value in the range.
 * @return An integer representing the generated random number.
 */
int generate_rand_nr(int min, int max);

/**
 * Initializes a list of printers.
 *
 * @param nr_of_printers The number of printers to initialize.
 * @return A pointer to the first printer in the list.
 */
Printer *init_printers_list(int nr_of_printers);

/**
 * Initializes a list of documents from a specified file path.
 *
 * @param file_path The path to the file containing document information.
 * @return A pointer to the first document in the list.
 */
Document *init_docs_list_from_file_path(char *file_path);

/**
 * Frees the memory allocated for the printers list.
 *
 * @param head A pointer to the first printer in the list.
 */
void free_printers(Printer *head);

/**
 * Prints the documents in the list.
 *
 * @param head_doc A pointer to the first document in the list.
 */
void print_docs(Document *head_doc);

/**
 * Frees the memory allocated for the documents list.
 *
 * @param head_doc A pointer to the first document in the list.
 */
void free_docs(Document *head_doc);

/**
 * Displays the documents currently being printed.
 *
 * @param head_printer A pointer to the first printer in the list.
 */
void show_printing_docs(Printer *head_printer);

/**
 * Simulates the printing process for documents.
 *
 * @param head_printer A pointer to the first printer in the list.
 */
void simulate_printing_docs(Printer *head_printer);

/**
 * Checks if all printers have finished printing.
 *
 * @param head_printer A pointer to the first printer in the list.
 * @return True if all printers have finished printing, false otherwise.
 */
bool are_printers_finished_to_print(Printer *head_printer);

/**
 * Assigns documents to printers for printing.
 *
 * @param head_printer A pointer to the first printer in the list.
 * @param head_doc A pointer to the first document in the list.
 */
void give_docs_to_printers(Printer *head_printer, Document *head_doc);

/**
 * Displays the status of adding a new printer.
 *
 * @param printer A pointer to the printer being added.
 */
void show_adding_printer_status(Printer *printer);

/**
 * Disconnects a printer by its ID.
 *
 * @param head_printer A pointer to the first printer in the list.
 * @param printer_id The ID of the printer to disconnect.
 * @return A pointer to the updated list of printers.
 */
Printer *disconnect_printer_by_id(Printer *head_printer, int printer_id);

/**
 * Adds a new printer to the list.
 *
 * @param head_printer A pointer to the first printer in the list.
 * @param nr_of_printers A pointer to the total number of printers, which will be updated.
 * @return A pointer to the updated list of printers.
 */
Printer *add_new_printer(Printer *head_printer, int *nr_of_printers);

/**
 * Gives documents to printers if necessary, based on certain conditions.
 *
 * @param head_printer A pointer to the first printer in the list.
 * @param head_doc A pointer to the first document in the list.
 */
void give_docs_to_printers_if_necessary(Printer *head_printer, Document *head_doc);

/**
 * Retrieves the number of documents in the list.
 *
 * @param head_doc A pointer to the first document in the list.
 * @return The number of documents.
 */
int get_nr_of_docs(Document *head_doc);

/**
 * Checks if all documents have been printed.
 *
 * @param head_doc A pointer to the first document in the list.
 * @return True if all documents have been printed, false otherwise.
 */
bool are_printed_all_docs(Document *head_doc);

/**
 * Checks if all printers are broken.
 *
 * @param head_printer A pointer to the first printer in the list.
 * @return True if all printers are broken, false otherwise.
 */
bool are_all_printers_broken(Printer *head_printer);

/**
 * Checks if all documents have been cancelled.
 *
 * @param head_doc A pointer to the first document in the list.
 * @return True if all documents have been cancelled, false otherwise.
 */
bool are_cancelled_all_docs(Document *head_doc);

/**
 * Retrieves the number of printed documents.
 *
 * @param head_doc A pointer to the first document in the list.
 * @return The number of printed documents.
 */
int get_nr_of_printed_docs(Document *head_doc);

/**
 * Prints the result of the program based on the exit status.
 *
 * @param exit_status The exit status of the program.
 */
void print_result_of_program(enum Exit_Status exit_status);

/**
 * Changes the status of documents if they have been printed.
 *
 * @param head_printer A pointer to the first printer in the list.
 */
void change_docs_status_if_are_printed(Printer *head_printer);

/**
 * Shows only the documents that have been printed at the moment.
 *
 * @param head_printer A pointer to the first printer in the list.
 */
void show_only_what_printed_docs(Printer *head_printer);

/**
 * Displays the status of a broken printer.
 *
 * @param printer A pointer to the broken printer.
 */
void show_broken_printer_status(Printer *printer);

/**
 * Cancels a document from the queue.
 *
 * @param head_doc A pointer to the first document in the list.
 * @return A pointer to the updated list of documents.
 */
Document *cancel_doc_from_queue(Document *head_doc);

/**
 * Cancels a document from a printer.
 *
 * @param head_printer A pointer to the first printer in the list.
 * @return A pointer to the document that was cancelled.
 */
Document *cancel_doc_from_printer(Printer *head_printer);

/**
 * Shows the status of cancelling a document from the queue.
 *
 * @param document A pointer to the document being cancelled.
 */
void show_cancelling_doc_from_queue_status(Document *document);

/**
 * Shows the status of cancelling a document from a printer.
 *
 * @param document A pointer to the document being cancelled.
 */
void show_cancelling_doc_from_printer_status(Document *document);

#endif //_FUNC_H_
