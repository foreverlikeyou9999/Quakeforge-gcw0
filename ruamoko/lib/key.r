#include "key.h"

string (string imt, int keynum, string binding) Key_SetBinding = #0;
int (string imt, int bindnum, string binding) Key_LookupBinding = #0;
int (string imt, string binding) Key_CountBinding = #0;
string (int keynum) Key_KeynumToString = #0;
