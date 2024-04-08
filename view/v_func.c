//
// Created by Misha on 08.04.2024.
//

#include <stdio.h>
#include <assert.h>
#include "v_func.h"
#include "v_private_func.h"


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

void show_adding_printer_status(Printer *printer) {
	assert(printer);
	printf("\t\tAdded new printer %d with printing time %d\n", printer->id, printer->printing_time);
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