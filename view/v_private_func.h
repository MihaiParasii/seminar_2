#ifndef _V_PRIVATE_FUNC_H_
#define _V_PRIVATE_FUNC_H_

#include "../model/struct.h"

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


#endif //_V_PRIVATE_FUNC_H_
