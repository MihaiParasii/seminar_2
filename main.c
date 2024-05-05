#include <stdlib.h>
#include <time.h>
#include "func.h"

int main() {
	int exit_status = 0;
	int nr_of_printers = 3;
	int nr_of_docs;
	int nr_of_printed_docs;
	bool execution = true;

	Printer *head_printer = init_printers_list(nr_of_printers);
	Document *doc_queue = init_docs_list_from_file_path("/Users/admin/Downloads/UTM/SDA/Seminar/Sem2/data.txt");

	give_docs_to_printers(head_printer, doc_queue);
	show_printing_docs(head_printer);

	srand(time(NULL));

	while (execution) {
		simulate_printing_docs(head_printer);
		show_printing_docs(head_printer);
		show_only_what_printed_docs(head_printer);
		change_docs_status_if_are_printed(head_printer);

		// If printer end to print a doc, give it next doc or NULL
		give_docs_to_printers_if_necessary(head_printer, doc_queue);

		if (are_printers_finished_to_print(head_printer)) {
			exit_status = PRINTERS_FINISHED_TO_PRINT;
			execution = false;
		}

		if (are_printed_all_docs(doc_queue)) {
			exit_status = ALL_DOCS_ARE_PRINTED;
			execution = false;
		}


		//Simulate breaking printer
		if (generate_rand_nr(0, 10) == 0) {
			int random_printer_id = generate_rand_nr(1, nr_of_printers);
			Printer *disconnected_printer = disconnect_printer_by_id(head_printer, random_printer_id);
			show_broken_printer_status(disconnected_printer);
		}

		// All printers are broken
		if (are_all_printers_broken(head_printer)) {
			exit_status = ALL_PRINTERS_ARE_BROKEN;
			execution = false;
		}

		// Simulate adding new printer
		if (generate_rand_nr(0, 10) == 0) {
			Printer *new_printer = add_new_printer(head_printer, &nr_of_printers);
			show_adding_printer_status(new_printer);
			give_docs_to_printers_if_necessary(new_printer, doc_queue);
		}

		// Simulate cancelling a document
		if (generate_rand_nr(0, 10) == 0) {
			int cancelling_status = generate_rand_nr(1, 2);

			switch (cancelling_status) {
				case FROM_QUEUE: {
					Document *cancelled_doc = cancel_doc_from_queue(doc_queue);
					show_cancelling_doc_from_queue_status(cancelled_doc);
					break;
				}
				case FROM_PRINTER: {
					Document *cancelled_doc = cancel_doc_from_printer(head_printer);
					show_cancelling_doc_from_printer_status(cancelled_doc);
					break;
				}
				default: {
					break;
				}
			}
		}

		if (are_cancelled_all_docs(doc_queue)) {
			exit_status = ALL_DOCS_ARE_CANCELLED;
			execution = false;
		}
	}

	nr_of_docs = get_nr_of_docs(doc_queue);
	nr_of_printed_docs = get_nr_of_printed_docs(doc_queue);

	printf("Nr of docs: %d\n", nr_of_docs);
	printf("Nr of printed docs: %d\n", nr_of_printed_docs);

	print_result_of_program(exit_status);

	free_printers(head_printer);
	free_docs(doc_queue);

	return 0;
}