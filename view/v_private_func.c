#include <stdio.h>
#include <assert.h>
#include "v_private_func.h"


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
