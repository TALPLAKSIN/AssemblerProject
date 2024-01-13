struct nodeMcr{
    char *name;/* name of the node */
    int start;/* start index of the macro */
    int end; /* length of the macro */
    McrList next;  /* Next link */
};
