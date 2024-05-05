#ifndef _V_FUNC_H_
#define _V_FUNC_H_

#include "../model/struct.h"

/**
 * Shows only the documents that have been printed at the moment.
 *
 * @param head_printer A pointer to the first printer in the list.
 */
void show_only_what_printed_docs(Printer *head_printer);

/**
 * Displays the status of adding a new printer.
 *
 * @param printer A pointer to the printer being added.
 */
void show_adding_printer_status(Printer *printer);

/**
 * Prints the documents in the list.
 *
 * @param head_doc A pointer to the first document in the list.
 */
void print_docs(Document *head_doc);

/**
 * Displays the documents currently being printed.
 *
 * @param head_printer A pointer to the first printer in the list.
 */
void show_printing_docs(Printer *head_printer);

/**
 * Prints the result of the program based on the exit status.
 *
 * @param exit_status The exit status of the program.
 */
void print_result_of_program(enum Exit_Status exit_status);

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

/**
 * Displays the status of a broken printer.
 *
 * @param printer A pointer to the broken printer.
 */
void show_broken_printer_status(Printer *printer);

#endif //_V_FUNC_H_
