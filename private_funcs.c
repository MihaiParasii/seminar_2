#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "private_funcs.h"

int _generate_rand_nr(int min, int max) {
	return (rand() % (max - min + 1)) + min;
}

float _generate_rand_float(float min, float max) {
	return (rand() % (int) (max - min + 1)) + min;
}

Printer *_init_printer(int id) {
	assert(id);

	Printer *printer = calloc(1, sizeof(Printer));

	printer->id = id;
	printer->printing_time = _generate_rand_nr(MIN_PRINTING_TIME, MAX_PRINTING_TIME);
	printer->printing_doc = NULL;
	printer->next = NULL;
	printer->is_working = true;

	if (printer->printing_time <= MAX_PRINTING_TIME / 3) {
		printer->type_of_printer = FAST_PRINTER;
	} else if ((printer->printing_time > MAX_PRINTING_TIME / 3)
	           && (printer->printing_time < 2 * MAX_PRINTING_TIME / 3)) {
		printer->type_of_printer = MEDIUM_PRINTER;
	} else {
		printer->type_of_printer = SLOW_PRINTER;
	}

	return printer;
}

Document *_find_biggest_unprinted_doc(Document *head_doc) {
	assert(head_doc);

	Document *biggest_unprinted_doc = NULL;

	for (Document *current_doc = head_doc; current_doc; current_doc = current_doc->next) {
		if (current_doc->document_printing_status != IS_IN_QUEUE_TO_PRINT) {
			continue;
		}
		if (!biggest_unprinted_doc) {
			biggest_unprinted_doc = current_doc;
		}

		if (current_doc->unprinted_rows > biggest_unprinted_doc->unprinted_rows) {
			biggest_unprinted_doc = current_doc;
		}
	}

	return biggest_unprinted_doc;
}

Document *_find_lowest_unprinted_doc(Document *head_doc) {
	assert(head_doc);

	Document *lowest_unprinted_doc = NULL;
	for (Document *current_doc = head_doc; current_doc; current_doc = current_doc->next) {
		if (current_doc->document_printing_status != IS_IN_QUEUE_TO_PRINT) {
			continue;
		}
		if (!lowest_unprinted_doc) {
			lowest_unprinted_doc = current_doc;
		}

		if (current_doc->unprinted_rows < lowest_unprinted_doc->unprinted_rows) {
			lowest_unprinted_doc = current_doc;
		}
	}

	return lowest_unprinted_doc;
}

Document *find_middle_unprinted_doc(Document *head_doc) {
	assert(head_doc);

	Document *lowest_unprinted_doc = _find_lowest_unprinted_doc(head_doc);
	Document *biggest_unprinted_doc = _find_biggest_unprinted_doc(head_doc);
	Document *middle_unprinted_docs = NULL;

	if (!lowest_unprinted_doc) {
		return NULL;
	}
	if (!biggest_unprinted_doc) {
		return NULL;
	}

	int count_unprinted_rows_for_middle_doc =
		(lowest_unprinted_doc->unprinted_rows + biggest_unprinted_doc->unprinted_rows) / 2;

	for (Document *current_doc = head_doc; current_doc; current_doc = current_doc->next) {
		if (current_doc->document_printing_status != IS_IN_QUEUE_TO_PRINT) {
			continue;
		}
		if (!middle_unprinted_docs) {
			middle_unprinted_docs = current_doc;
		}

		if (current_doc->unprinted_rows > count_unprinted_rows_for_middle_doc - count_unprinted_rows_for_middle_doc / 3
		    || current_doc->unprinted_rows

		       > count_unprinted_rows_for_middle_doc + count_unprinted_rows_for_middle_doc / 3) {
			middle_unprinted_docs = current_doc;
			break;
		}
	}

	return middle_unprinted_docs;
}

void _give_target_doc_to_target_printer(Document *head_doc, Printer *head_printer, int doc_id, int printer_id) {
	assert(head_doc);
	assert(head_printer);

	for (Document *current_doc = head_doc; current_doc; current_doc = current_doc->next) {
		if (current_doc->id == doc_id) {
			for (Printer *printer = head_printer; printer; printer = printer->next) {
				if (printer->id == printer_id) {
					printer->printing_doc = current_doc;
					current_doc->document_printing_status = IS_PRINTING;
					return;
				}
			}
		}
	}
}

void _give_special_doc_to_printer_by_printer_type(Printer *head_printer, Printer *target_printer, Document *head_doc) {
	assert(head_printer);
	assert(target_printer);
	assert(head_doc);

	Document *document = NULL;

	if (target_printer->type_of_printer == FAST_PRINTER) {
		document = _find_biggest_unprinted_doc(head_doc);
	} else if (target_printer->type_of_printer == SLOW_PRINTER) {
		document = _find_lowest_unprinted_doc(head_doc);
	} else {
		document = find_middle_unprinted_doc(head_doc);
		if (!document) {
			document = _find_biggest_unprinted_doc(head_doc);
		}
	}

	if (!document) {
		return;
	}

	_give_target_doc_to_target_printer(head_doc, head_printer, document->id, target_printer->id);
}

Document *_init_document() {
	Document *document = calloc(1, sizeof(Document));
	return document;
}

Document *_init_doc_from_file(FILE *file) {
	assert(file);

	Document *document = _init_document();
	char temp_name[100];

	fscanf(file, "%d,%[^,],%d,%d", &document->id, temp_name, &document->rows_count, &document->unprinted_rows);
	document->name = strdup(temp_name);
	document->emergency_printing_status = false;
	document->document_printing_status = IS_IN_QUEUE_TO_PRINT;

	return document;
}

void _print_doc(Document *document) {
	assert(document);

	printf("%d %s %d %d\n", document->id, document->name, document->rows_count, document->unprinted_rows);
}
void _show_printing_status(Printer *printer) {
	assert(printer);

	printf("Printing document %10s row %3d, remaining rows: %2d, by printerID %2d...\n", printer->printing_doc->name,
	       printer->printing_doc->rows_count - printer->printing_doc->unprinted_rows,
	       printer->printing_doc->unprinted_rows, printer->id);
}

void _free_printer(Printer *printer) {
	assert(printer);

	free(printer);
}

void _free_doc(Document *document) {
	assert(document);

	free(document->name);
	free(document);
}

void _disconnect_printer(Printer *printer) {
	assert(printer);

	printer->is_working = false;
	if (printer->printing_doc) {
		printer->printing_doc->document_printing_status = IS_IN_QUEUE_TO_PRINT;
		printer->printing_doc->emergency_printing_status = true;
		printer->printing_doc = NULL;
	}
}