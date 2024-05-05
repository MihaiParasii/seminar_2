#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "private_funcs.h"
#include "func.h"

int generate_rand_nr(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}

Printer *init_printers_list(int nr_of_printers) {
	assert(nr_of_printers);

	srand(time(NULL));
	Printer *printer = _init_printer(1);
	Printer *head_printer = printer;

	for (int i = 2; i <= nr_of_printers; ++i) {
		printer->next = _init_printer(i);
		printer = printer->next;
	}

	return head_printer;
}

int get_rows_count_from_file(const FILE *file) {
	assert(file);

	const int buffer_size = 500;
	char buffer[buffer_size];
	int lines = 0;
	while (fgets(buffer, buffer_size, file)) {
		++lines;
	}
	rewind(file);
	return lines ? lines : 0;
}

Document *init_docs_list_from_file_path(char *file_path) {
	assert(file_path);

	FILE *file = fopen(file_path, "r");

	int file_rows_count = get_rows_count_from_file(file);
	Document *head = _init_doc_from_file(file);
	Document *prev = head;

	for (int i = 0; i < file_rows_count - 1; ++i) {
		Document *doc_queue = _init_doc_from_file(file);
		prev->next = doc_queue;
		doc_queue->next = NULL;
		prev = doc_queue;
	}

	return head;
}

void print_docs(Document *head_doc) {
	assert(head_doc);

	for (Document *current_doc = head_doc; current_doc; current_doc = current_doc->next) {
		_print_doc(current_doc);
	}
}

void show_printing_docs(Printer *head_printer) {
	assert(head_printer);

	for (Printer *current_printer = head_printer; current_printer; current_printer = current_printer->next) {
		if (!current_printer->is_working) {
			continue;
		}
		if (!current_printer->printing_doc) {
			continue;
		}
		_show_printing_status(current_printer);
	}
}

void simulate_printing_docs(Printer *head_printer) {
	assert(head_printer);

	for (Printer *current_printer = head_printer; current_printer; current_printer = current_printer->next) {
		if (!current_printer->is_working) {
			continue;
		}
		if (!current_printer->printing_doc) {
			continue;
		}
		--current_printer->printing_doc->unprinted_rows;
	}
}

void show_only_what_printed_docs(Printer *head_printer) {
	assert(head_printer);

	for (Printer *current_printer = head_printer; current_printer; current_printer = current_printer->next) {
		if (!current_printer->is_working) {
			continue;
		}
		if (!current_printer->printing_doc) {
			continue;
		}
		if (current_printer->printing_doc->unprinted_rows == 0) {
			printf("Document %10s is printed by printerID %d.\n", current_printer->printing_doc->name, current_printer->id);
		}
	}
}

void change_docs_status_if_are_printed(Printer *head_printer) {
	assert(head_printer);

	for (Printer *current_printer = head_printer; current_printer; current_printer = current_printer->next) {
		if (!current_printer->is_working) {
			continue;
		}
		if (!current_printer->printing_doc) {
			continue;
		}
		if (current_printer->printing_doc->unprinted_rows == 0) {
			current_printer->printing_doc->document_printing_status = IS_PRINTED;
			current_printer->printing_doc = NULL;
		}
	}
}

void show_adding_printer_status(Printer *printer) {
	assert(printer);
	printf("\t\tAdded new printer %d with printing time %d\n", printer->id, printer->printing_time);
}

void give_docs_to_printers(Printer *head_printer, Document *head_doc) {
	assert(head_printer);
	assert(head_doc);

	for (Printer *current_printer = head_printer; current_printer; current_printer = current_printer->next) {
		if (current_printer->is_working) {
			_give_special_doc_to_printer_by_printer_type(head_printer, current_printer, head_doc);
		}
	}
}

bool are_printers_finished_to_print(Printer *head_printer) {
	assert(head_printer);

	for (Printer *current_printer = head_printer; current_printer; current_printer = current_printer->next) {
		if (!current_printer->is_working) {
			continue;
		}
		if (current_printer->printing_doc) {
			return false;
		}
	}
	return true;
}

Printer *disconnect_printer_by_id(Printer *head_printer, int printer_id) {
	assert(head_printer);
	assert(printer_id);

	for (Printer *current_printer = head_printer; current_printer; current_printer = current_printer->next) {
		if (current_printer->id == printer_id) {
			_disconnect_printer(current_printer);
			return current_printer;
		}
	}

	return NULL;
}

void free_printers(Printer *head) {
	assert(head);

	Printer *temp_printer;
	while (head) {
		temp_printer = head;
		head = temp_printer->next;
		_free_printer(temp_printer);
	}
}

void free_docs(Document *head_doc) {
	assert(head_doc);

	Document *temp_doc;
	while (head_doc) {
		temp_doc = head_doc;
		head_doc = temp_doc->next;
		_free_doc(temp_doc);
	}
}

Printer *add_new_printer(Printer *head_printer, int *nr_of_printers) {
	assert(head_printer);
	assert(nr_of_printers);

	for (Printer *current_printer = head_printer; current_printer; current_printer = current_printer->next) {
		if (!current_printer->next) {
			current_printer->next = _init_printer(++(*nr_of_printers));
			return current_printer->next;
		}
	}
	return NULL;
}

void give_docs_to_printers_if_necessary(Printer *head_printer, Document *head_doc) {
	assert(head_printer);
	assert(head_doc);

	for (Printer *current_printer = head_printer; current_printer; current_printer = current_printer->next) {
		if (!current_printer->is_working) {
			continue;
		}

		if (current_printer->printing_doc) {
			continue;
		}


		// Check if are docs that have emergency printing status
		for (Document *current_doc = head_doc; current_doc; current_doc = current_doc->next) {
			if (current_doc->document_printing_status != IS_IN_QUEUE_TO_PRINT) {
				continue;
			}

			if (!current_doc->emergency_printing_status) {
				continue;
			}

			current_printer->printing_doc = current_doc;
			current_doc->emergency_printing_status = false;
			current_doc->document_printing_status = IS_PRINTING;
			break;
		}

		// Go to next printer if this printer received a doc with emergency_printing_status
		if (current_printer->printing_doc) {
			continue;
		}

		_give_special_doc_to_printer_by_printer_type(head_printer, current_printer, head_doc);
	}
}

int get_nr_of_docs(Document *head_doc) {
	assert(head_doc);

	int counter = 0;
	for (Document *current_doc = head_doc; current_doc; current_doc = current_doc->next) {
		++counter;
	}
	return counter;
}

bool are_printed_all_docs(Document *head_doc) {
	assert(head_doc);

	for (Document *current_doc = head_doc; current_doc; current_doc = current_doc->next) {
		if (current_doc->document_printing_status != IS_PRINTED) {
			return false;
		}
	}
	return true;
}

bool are_cancelled_all_docs(Document *head_doc) {
	assert(head_doc);

	for (Document *current_doc = head_doc; current_doc; current_doc = current_doc->next) {
		if (current_doc->document_printing_status != IS_CANCELED) {
			return false;
		}
	}
	return true;
}

bool are_all_printers_broken(Printer *head_printer) {
	assert(head_printer);

	for (Printer *current_printer = head_printer; current_printer; current_printer = current_printer->next) {
		if (current_printer->is_working) {
			return false;
		}
	}
	return true;
}

int get_nr_of_printed_docs(Document *head_doc) {
	assert(head_doc);

	int counter = 0;
	for (Document *current_doc = head_doc; current_doc; current_doc = current_doc->next) {
		if (current_doc->document_printing_status == IS_PRINTED) {
			++counter;
		}
	}
	return counter;
}

void print_result_of_program(enum Exit_Status exit_status) {
	assert(exit_status);

	switch (exit_status) {
		case ALL_DOCS_ARE_PRINTED: {
			printf("\nAll documents are printed with success!\n");
			return;
		}
		case ALL_PRINTERS_ARE_BROKEN: {
			printf("\nAll printers are broken and printing is stopped!\n");
			return;
		}
		case PRINTERS_FINISHED_TO_PRINT: {
			printf("Printers finished to print documents, with some cancelled docs\n");
			return;
		}
		case ALL_DOCS_ARE_CANCELLED: {
			printf("\nAll documents are cancelled!\n");
			return;
		}
	}
}

void show_broken_printer_status(Printer *printer) {
	assert(printer);

	printf("\tThe printer %d broke down\n", printer->id);
	if (printer->printing_doc) {
		printf("\tDocument %s is added first in queue to print\n", printer->printing_doc->name);
	} else {
		printf("\tThis printer doesn't have document to print\n");
	}
}

void show_cancelling_doc_from_queue_status(Document *document) {
	printf("\tCancelling doc from queue...\n");
	if (document) {
		printf("\tDoc %s from queue is cancelled\n", document->name);
		return;
	}
	printf("\tIn queue are no docs.\n");
}

void show_cancelling_doc_from_printer_status(Document *document) {
	printf("\tCancelling doc which is printing...\n");
	if (document) {
		printf("\tDoc %s which is printing is cancelled\n", document->name);
		return;
	}
	printf("\tPrinters does not have any docs.\n");
}

Document *cancel_doc_from_printer(Printer *head_printer) {
	assert(head_printer);

	for (Printer *current_printer = head_printer; current_printer; current_printer = current_printer->next) {
		if (!current_printer->is_working) {
			continue;
		}
		if (current_printer->printing_doc) {
			Document *doc_to_return = current_printer->printing_doc;
			current_printer->printing_doc->document_printing_status = IS_CANCELED;
			current_printer->printing_doc = NULL;
			return doc_to_return;
		}
	}
	return NULL;
}

Document *cancel_doc_from_queue(Document *head_doc) {
	assert(head_doc);

	for (Document *current_doc = head_doc; current_doc; current_doc = current_doc->next) {
		if (current_doc->document_printing_status == IS_IN_QUEUE_TO_PRINT) {
			current_doc->document_printing_status = IS_CANCELED;
			return current_doc;
		}
	}

	return NULL;
}