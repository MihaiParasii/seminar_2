#ifndef _STRUCT_H_
#define _STRUCT_H_

#include <stdio.h>

typedef enum TypesOfPrinters {
	FAST_PRINTER = 0,
	MEDIUM_PRINTER = 1,
	SLOW_PRINTER = 2,
} TypeOfPrinter;

typedef enum DocumentPrintingStatus {
	IS_IN_QUEUE_TO_PRINT = 0,
	IS_PRINTED = 1,
	IS_PRINTING = 2,
	IS_CANCELED = 3,
} DocumentPrintingStatus;

typedef struct Document {
	int id;
	char *name;
	int rows_count;
	int unprinted_rows;
	struct Document *next;
	bool emergency_printing_status: 1;
	DocumentPrintingStatus document_printing_status;
} Document;

typedef struct Printer {
	int id;
	int printing_time;
	Document *printing_doc;
	struct Printer *next;
	int type_of_printer;
	bool is_working: 1;
} Printer;

enum Exit_Status {
	PRINTERS_FINISHED_TO_PRINT = 1,
	ALL_PRINTERS_ARE_BROKEN = 2,
	ALL_DOCS_ARE_CANCELLED = 3,
	ALL_DOCS_ARE_PRINTED = 4,
};

enum CancelADoc {
	FROM_PRINTER = 1,
	FROM_QUEUE = 2,
};

#endif //_STRUCT_H_
