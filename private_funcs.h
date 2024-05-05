#ifndef _PRIVATE_FUNCS_H_
#define _PRIVATE_FUNCS_H_
#include "struct.h"

#define MAX_PRINTING_TIME 10
#define MIN_PRINTING_TIME 1

/**
 * Generates a random floating-point number within a specified range.
 *
 * @param min The minimum value in the range.
 * @param max The maximum value in the range.
 * @return A random floating-point number between min and max.
 */
float _generate_rand_float(float min, float max);

/**
 * Initializes a printer with a given ID.
 *
 * @param id The unique identifier for the printer.
 * @return A pointer to the initialized Printer structure.
 */
Printer *_init_printer(int id);

/**
 * Initializes a new document with default values.
 *
 * @return A pointer to the initialized Document structure.
 */
Document *_init_document();

/**
 * Initializes a document from a given file.
 *
 * @param file A pointer to a FILE structure from which the document will be initialized.
 * @return A pointer to the initialized Document structure.
 */
Document *_init_doc_from_file(FILE *file);

/**
 * Distributes a special document to a target printer based on the printer's type.
 * This function iterates through the list of documents starting from `head_doc` and selects a special document
 * based on criteria defined by the printer's type. It then assigns this document to the `target_printer`.
 *
 * @param head_printer Pointer to the first printer in the list of printers. This list is used to identify the type of the target printer.
 * @param target_printer Pointer to the printer to which the special document will be given.
 * @param head_doc Pointer to the first document in the list of documents from which the special document will be selected.
 */
void _give_special_doc_to_printer_by_printer_type(Printer *head_printer, Printer *target_printer, Document *head_doc);

/**
 * Assigns a specific document to a specific printer based on their IDs.
 * This function iterates through the list of documents starting from `head_doc` to find the document with the specified `doc_id`.
 * Similarly, it iterates through the list of printers starting from `head_printer` to find the printer with the specified `printer_id`.
 * Once both the target document and printer are found, the document is assigned to the printer for printing.
 *
 * @param head_doc Pointer to the first document in the list of documents. This list is searched to find the target document.
 * @param head_printer Pointer to the first printer in the list of printers. This list is searched to find the target printer.
 * @param doc_id The ID of the document to be assigned to the printer.
 * @param printer_id The ID of the printer to which the document will be assigned.
 */
void _give_target_doc_to_target_printer(Document *head_doc, Printer *head_printer, int doc_id, int printer_id);

/**
 * Finds the middle unprinted document in a list of documents.
 * This function iterates through the list of documents starting from `head_doc` to find the middle document that has not been printed yet.
 * The selection of the middle document is based on the total count of unprinted documents.
 *
 * @param head_doc Pointer to the first document in the list of documents. This list is searched to find the middle unprinted document.
 * @return A pointer to the middle unprinted document if found; otherwise, NULL.
 */
Document *find_middle_unprinted_doc(Document *head_doc);

/**
 * Finds the document with the lowest ID among all unprinted documents.
 * This function iterates through the list of documents starting from `head_doc` to find the unprinted document with the lowest ID.
 *
 * @param head_doc Pointer to the first document in the list of documents. This list is searched to find the lowest unprinted document based on its ID.
 * @return A pointer to the lowest unprinted document based on ID if found; otherwise, NULL.
 */
Document *_find_lowest_unprinted_doc(Document *head_doc);

/**
 * Finds the document with the largest size among all unprinted documents.
 * This function iterates through the list of documents starting from `head_doc` to find the unprinted document with the largest size.
 *
 * @param head_doc Pointer to the first document in the list of documents. This list is searched to find the biggest unprinted document based on its size.
 * @return A pointer to the biggest unprinted document based on size if found; otherwise, NULL.
 */
Document *_find_biggest_unprinted_doc(Document *head_doc);

/**
 * Prints the specified document.
 *
 * @param document Pointer to the Document structure to be printed.
 */
void _print_doc(Document *document);

/**
 * Displays the current printing status of the specified printer.
 *
 * @param printer Pointer to the Printer structure whose printing status is to be displayed.
 */
void _show_printing_status(Printer *printer);

/**
 * Frees the memory allocated for the specified printer.
 *
 * @param printer Pointer to the Printer structure to be freed.
 */
void _free_printer(Printer *printer);

/**
 * Frees the memory allocated for the specified document.
 *
 * @param document Pointer to the Document structure to be freed.
 */
void _free_doc(Document *document);

/**
 * Disconnects the specified printer, performing any necessary cleanup.
 *
 * @param printer Pointer to the Printer structure to be disconnected.
 */
void _disconnect_printer(Printer *printer);

#endif //_PRIVATE_FUNCS_H_
