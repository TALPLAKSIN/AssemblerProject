#include "HandelLable.h"
int HandelTagName(char *name) {
    int i;
    if (name != NULL && isalpha(name[0]) && strlen(name) <= MAX_LABEL_LENGTH) {
        for (i = 0; i < strlen(name) ;i++) {
            if (!isalnum(name[i]))
                return FALSE;
        }
        return TRUE;
    }
    return FALSE;
}
int handel_label(TagList *HeadTagList, char *labelName, int IC, int countLine, TagList *TagTemp) {

}