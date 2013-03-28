/*
	image.c

	General image handling

	Copyright (C) 2003 Harry Roberts

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

	See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to:

		Free Software Foundation, Inc.
		59 Temple Place - Suite 330
		Boston, MA  02111-1307, USA

*/
#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef HAVE_STRING_H
# include <string.h>
#endif
#ifdef HAVE_STRINGS_H
# include <strings.h>
#endif

#include "QF/dstring.h"
#include "QF/image.h"
#include "QF/pcx.h"
#include "QF/png.h"
#include "QF/quakefs.h"
#include "QF/tga.h"

VISIBLE tex_t *
LoadImage (const char *imageFile)
{
	int         tmp;
	dstring_t  *tmpFile;
	char       *ext;
	tex_t      *tex = NULL;
	QFile      *fp;

	// Get the file name without extension
	tmpFile = dstring_new ();
	dstring_copystr (tmpFile, imageFile);
	ext = strrchr (tmpFile->str, '.');
	if (ext)
		tmp = ext - tmpFile->str;
	else
		tmp = tmpFile->size - 1;

	// Check for a .png
	dstring_replace (tmpFile, tmp, tmpFile->size, ".png", 5);
	QFS_FOpenFile (tmpFile->str, &fp);
	if (fp) {
		tex = LoadPNG (fp);
		Qclose (fp);
		dstring_delete (tmpFile);
		return (tex);
	}

	// Check for a .tga
	dstring_replace (tmpFile, tmp, tmpFile->size, ".tga", 5);
	QFS_FOpenFile (tmpFile->str, &fp);
	if (fp) {
		tex = LoadTGA (fp);
		Qclose (fp);
		dstring_delete (tmpFile);
		return (tex);
	}

/*
	// Check for a .jpg
	dstring_replace (tmpFile, tmp, tmpFile->size, ".jpg", 5);
	QFS_FOpenFile (tmpFile->str, &fp);
	if (fp) {
		tex = LoadJPG (fp);
		Qclose (fp);
		dstring_delete (tmpFile);
		return (tex);
	}
*/

	// Check for a .pcx
	dstring_replace (tmpFile, tmp, tmpFile->size, ".pcx", 5);
	QFS_FOpenFile (tmpFile->str, &fp);
	if (fp) {
		tex = LoadPCX (fp, 1, NULL); // Convert, some users don't grok paletted
		Qclose (fp);
		dstring_delete (tmpFile);
		return (tex);
	}

	dstring_delete (tmpFile);
	return (tex);
}
