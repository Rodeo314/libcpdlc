/*
 * Copyright 2019 Saso Kiselkov
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <math.h>

#include "../src/cpdlc_assert.h"
#include "../src/cpdlc_string.h"

#include "fmsbox_impl.h"

void
fmsbox_verify_msg(fmsbox_t *box, cpdlc_msg_t *msg, const char *title,
    int ret_page)
{
	ASSERT(box != NULL);
	ASSERT(msg != NULL);
	ASSERT(title != NULL);

	cpdlc_strlcpy(box->verify.title, title, sizeof (box->verify.title));
	box->verify.ret_page = ret_page;
	if (box->verify.msg != NULL)
		cpdlc_msg_free(box->verify.msg);
	box->verify.msg = msg;
	fmsbox_set_page(box, FMS_PAGE_VRFY);
}

void
fmsbox_vrfy_draw_cb(fmsbox_t *box)
{
	enum { MAX_LINES = 8 };
	char **lines = NULL;
	unsigned n_lines = 0;

	ASSERT(box != NULL);
	ASSERT(box->verify.msg != NULL);

	fmsbox_msg2lines(box->verify.msg, &lines, &n_lines);
	ASSERT(n_lines != 0);
	fmsbox_set_num_subpages(box, ceil(n_lines / (double)MAX_LINES));

	fmsbox_put_page_ind(box, FMS_COLOR_WHITE);

	for (int i = 0; i < MAX_LINES; i++) {
		int line = i + box->subpage * MAX_LINES;

		if (line >= (int)n_lines)
			break;
		fmsbox_put_str(box, LSK1_ROW + i, 0, false, FMS_COLOR_GREEN,
		    FMS_FONT_SMALL, "%s", lines[line]);
	}

	fmsbox_put_lsk_action(box, FMS_KEY_LSK_R5, FMS_COLOR_CYAN, "SEND*");
	fmsbox_put_lsk_action(box, FMS_KEY_LSK_L6, FMS_COLOR_WHITE, "<RETURN");

	fmsbox_free_lines(lines, n_lines);
}

bool
fmsbox_vrfy_key_cb(fmsbox_t *box, fms_key_t key)
{
	ASSERT(box != NULL);

	if (key == FMS_KEY_LSK_R5) {
		ASSERT(box->verify.msg != NULL);
		cpdlc_msglist_send(box->msglist, box->verify.msg,
		    CPDLC_NO_MSG_THR_ID);
		box->verify.msg = NULL;
		fmsbox_set_page(box, FMS_PAGE_MAIN_MENU);
	} else if (key == FMS_KEY_LSK_L6 && box->verify.ret_page >= 0 &&
	    box->verify.ret_page < FMS_NUM_PAGES) {
		fmsbox_set_page(box, box->verify.ret_page);
	} else {
		return (false);
	}

	return (true);
}
